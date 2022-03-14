#include "database.h"
#include "TestRunner.h"

using namespace std;

void TestDatabaseAddAndPrint() {
    {
        Database db;
        db.Add({Year(2017), Month(11), Day(15)}, "Wednesday");
        db.Add({Year(2017), Month(11), Day(16)}, "Thursday");
        db.Add({Year(2017), Month(11), Day(17)}, "Friday");

        ostringstream os;
        db.Print(os);

        const string expected = "2017-11-15 Wednesday\n"
                                "2017-11-16 Thursday\n"
                                "2017-11-17 Friday\n";
        AssertEqual(os.str(), expected, "Database print: 3 simple events");
    }
    {
        Database db;
        db.Add({Year(2017), Month(3), Day(1)}, "1st of March");
        db.Add({Year(2017), Month(2), Day(1)}, "1st of February");
        db.Add({Year(2017), Month(1), Day(1)}, "1st of January");

        ostringstream os;
        db.Print(os);

        const string expected = "2017-01-01 1st of January\n"
                                "2017-02-01 1st of February\n"
                                "2017-03-01 1st of March\n";
        AssertEqual(os.str(), expected, "Database print: events should sorted by date");
    }
    {
        Database db;
        db.Add({Year(2017), Month(3), Day(1)}, "01.03 1");
        db.Add({Year(2017), Month(3), Day(5)}, "05.03 1");
        db.Add({Year(2017), Month(3), Day(1)}, "01.03 2");
        db.Add({Year(2017), Month(3), Day(1)}, "01.03 3");
        db.Add({Year(2017), Month(3), Day(5)}, "05.03 2");

        ostringstream os;
        db.Print(os);

        const string expected = "2017-03-01 01.03 1\n"
                                "2017-03-01 01.03 2\n"
                                "2017-03-01 01.03 3\n"
                                "2017-03-05 05.03 1\n"
                                "2017-03-05 05.03 2\n";
        AssertEqual(os.str(), expected, "Database print: multiple events at single date");
    }
    {
        Database db;
        db.Add({Year(2017), Month(3), Day(1)}, "01.03 1");
        db.Add({Year(2017), Month(3), Day(1)}, "01.03 2");
        db.Add({Year(2017), Month(3), Day(1)}, "01.03 1");
        db.Add({Year(2017), Month(3), Day(1)}, "01.03 1");

        ostringstream os;
        db.Print(os);

        const string expected = "2017-03-01 01.03 1\n"
                                "2017-03-01 01.03 2\n";
        AssertEqual(os.str(), expected, "Database print: identical events at the given date must be ignored");
    }
}

void TestDatabaseFind() {
    {
        const Entries expected = {
                {{Year(2017), Month(11), Day(17)}, "Friday"},
                {{Year(2017), Month(11), Day(18)}, "Saturday"},
                {{Year(2017), Month(11), Day(19)}, "Sunday"}
        };

        Database db;
        for (const auto& e : expected) {
            db.Add(e.first, e.second);
        }

        auto alwaysTrue = [](const Date&, const string&) { return true; };
        AssertEqual(db.FindIf(alwaysTrue), expected, "Database find: All entries should be found for alwaysTrue");
    }
    {
        Database db;
        db.Add({Year(2017), Month(11), Day(17)}, "Friday");
        db.Add({Year(2016), Month(11), Day(17)}, "Thursday");
        db.Add({Year(2015), Month(11), Day(17)}, "Tuesday");
        db.Add({Year(2014), Month(11), Day(17)}, "Monday");

        auto complexCondition = [](const Date& date, const string& event) {
            return date.GetYear() == 2016 || event == "Monday";
        };
        const Entries expected = {{{Year(2014), Month(11), Day(17)}, "Monday"},
                                  {{Year(2016), Month(11), Day(17)}, "Thursday"}};
        AssertEqual(db.FindIf(complexCondition), expected, "Database find: complex condition");
    }
    {
        Database db;
        db.Add({Year(2017), Month(11), Day(17)}, "Friday");
        db.Add({Year(2016), Month(11), Day(17)}, "Thursday");
        db.Add({Year(2015), Month(11), Day(17)}, "Tuesday");
        db.Add({Year(2014), Month(11), Day(17)}, "Monday");

        auto acceptsNothing = [](const Date& date, const string& event) {
            return date.GetYear() == 2016 && event == "Monday";
        };
        AssertEqual(db.FindIf(acceptsNothing), Entries(), "Database find: accepts nothing");
    }
}

void TestDatabaseRemove() {
    {
        Database db;
        db.Add({Year(2017), Month(11), Day(17)}, "Friday");
        db.Add({Year(2016), Month(11), Day(17)}, "Thursday");
        db.Add({Year(2015), Month(11), Day(17)}, "Tuesday");
        db.Add({Year(2014), Month(11), Day(17)}, "Monday");

        auto alwaysTrue = [](const Date&, const string&) { return true; };
        AssertEqual(db.RemoveIf(alwaysTrue), 4, "Database remove: alwaysTrue removes all 1");
        AssertEqual(db.FindIf(alwaysTrue), Entries(), "Database remove: alwaysTrue removes all 2");
    }
    {
        Database db;
        db.Add({Year(2017), Month(11), Day(17)}, "Friday");
        db.Add({Year(2016), Month(11), Day(17)}, "Thursday");
        db.Add({Year(2015), Month(11), Day(17)}, "Tuesday");
        db.Add({Year(2014), Month(11), Day(17)}, "Monday");

        auto complexCondition = [](const Date& date, const string& event) {
            return date.GetYear() == 2016 || event == "Monday";
        };
        AssertEqual(db.RemoveIf(complexCondition), 2, "Database remove: complex condition 1");
        AssertEqual(db.FindIf(complexCondition), Entries(), "Database remove: complex condition 2");
    }
    {
        const Date date = {Year(2017), Month(11), Day(24)};

        Database db;
        db.Add(date, "abc");
        db.Add(date, "bca");
        db.Add(date, "abd");
        db.Add(date, "cba");

        ostringstream os;
        db.Print(os);
        const string expected_one =
                "2017-11-24 abc\n"
                "2017-11-24 bca\n"
                "2017-11-24 abd\n"
                "2017-11-24 cba\n";
        AssertEqual(os.str(), expected_one, "Database print after remove 1");

        db.RemoveIf([](const Date&, const string& event) { return event[0] == 'a'; });

        os.str("");
        db.Print(os);
        const string expected_two =
                "2017-11-24 bca\n"
                "2017-11-24 cba\n";
        AssertEqual(os.str(), expected_two, "Database print after remove 2: entries should be printed in order of addition");
    }
}

void TestDatabaseLast() {
    using Entry = std::pair<Date, std::string>;
    {
        Database db;
        db.Add({Year(2017), Month(11), Day(17)}, "Friday");
        db.Add({Year(2017), Month(11), Day(17)}, "One more event");
        db.Add({Year(2016), Month(11), Day(17)}, "Thursday");
        db.Add({Year(2015), Month(11), Day(17)}, "Tuesday");
        db.Add({Year(2014), Month(11), Day(17)}, "Monday");

        AssertEqual(db.Last({Year(2017), Month(11), Day(17)}),
                    Entry{{Year(2017), Month(11), Day(17)},"One more event"},
                    "Database last: successful 1");

        AssertEqual(db.Last({Year(2017), Month(11), Day(16)}),
                    Entry{{Year(2016), Month(11), Day(17)}, "Thursday"},
                    "Database last: successful 2");

        AssertEqual(db.Last({Year(2016), Month(11), Day(17)}),
                    Entry{{Year(2016), Month(11), Day(17)}, "Thursday"},
                    "Database last: successful 3");

        AssertEqual(db.Last({Year(2016), Month(11), Day(18)}),
                    Entry{{Year(2016), Month(11), Day(17)}, "Thursday"},
                    "Database last: successful 4");

        AssertEqual(db.Last({Year(2014), Month(11), Day(18)}),
                    Entry{{Year(2014), Month(11), Day(17)}, "Monday"},
                    "Database last: successful 5");

        AssertEqual(db.Last({Year(2014), Month(11), Day(17)}),
                    Entry{{Year(2014), Month(11), Day(17)}, "Monday"},
                    "Database last: successful 6");
    }
    {
        Database db;
        db.Add({Year(2017), Month(11), Day(17)}, "One more event");
        db.Add({Year(2017), Month(11), Day(17)}, "Friday");
        AssertEqual(db.Last({Year(2017), Month(11), Day(17)}),
                    Entry{{Year(2017), Month(11), Day(17)}, "Friday"},
                    "Database last and remove 1");
        db.RemoveIf([](const Date&, const string& event) { return event == "Friday"; });

        AssertEqual(db.Last({Year(2017), Month(11), Day(17)}),
                    Entry{{Year(2017), Month(11), Day(17)}, "One more event"},
                    "Database last and remove 2");
    }
}

void TestDatabaseException() {
    using Entry = std::pair<Date, std::string>;

    {
        Database db;
        db.Add({Year(2017), Month(11), Day(17)}, "Friday");
        db.Add({Year(2017), Month(11), Day(17)}, "One more event");
        db.Add({Year(2016), Month(11), Day(17)}, "Thursday");
        db.Add({Year(2015), Month(11), Day(17)}, "Tuesday");
        db.Add({Year(2014), Month(11), Day(17)}, "Monday");

        bool wasException = false;
        try {
            db.Last({Year(1), Month(1), Day(1)});
        } catch (invalid_argument&) {
            std::cerr << "exception caught\n";
            wasException = true;
        } catch (exception& e) {
            Assert(false, "Database last: unexpected exception " + string(e.what()));
        }
        Assert(wasException, "Database last: invalid argument wasn't thrown");
    }

    {
        Database db;
        db.Add({Year(2017), Month(11), Day(17)}, "One more event");
        db.Add({Year(2017), Month(11), Day(17)}, "Friday");
        db.Add({Year(2017), Month(11), Day(17)}, "Thursday");
        db.RemoveIf([](const Date& date, const string&) {
            return date == Date{Year(2017), Month(11), Day(17)
            };
        });
        bool wasException = false;
        try {
            AssertEqual(db.Last({Year(2017), Month(11), Day(17)}),
                        Entry{{Year(2017), Month(11), Day(17)}, "Thursday"},
                        "Database last and remove 2");
        } catch (std::invalid_argument& msg) {
            std::cerr << "exception caught\n";
            wasException = true;
        }
        Assert(wasException, "Database last: invalid argument wasn't thrown");
    }
}
