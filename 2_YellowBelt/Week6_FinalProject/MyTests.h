#ifndef WEEK6_MYTESTS_H
#define WEEK6_MYTESTS_H

#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

void TEST_DATE_CONSTRUCTOR(){
    {
        Date first(Year(2020), Month(1), Day(10));
        MyAssert(first.getYear(), 2020, "first date Year");
        MyAssert(first.getMonth(), 1, "first date Month");
        MyAssert(first.getDay(), 10, "first date Day");
    }

    {
        Date second(Year(2022), Month(2), Day(3));
        MyAssert(second.getYear(), 2022, "second date Year");
        MyAssert(second.getMonth(), 2, "second date Month");
        MyAssert(second.getDay(), 3, "second date Day");
    }

    {
        Date third(Year(122), Month(4), Day(5));
        MyAssert(third.getYear(), 122, "third date Year");
        MyAssert(third.getMonth(), 4, "third date Month");
        MyAssert(third.getDay(), 5, "third date Day");
    }
}

void TEST_DATE_OPERATORS(){
    {
        Date lhs(Year(2020), Month(1), Day(10));
        Date rhs(Year(2020), Month(1), Day(10));
        MyAssert(lhs == rhs, true, "operator ==");

        Date nlhs(Year(2020), Month(1), Day(10));
        Date nrhs(Year(2021), Month(11), Day(11));
        MyAssert(nlhs == nrhs, false, "operator ==");
    }

    {
        Date lhs(Year(2020), Month(1), Day(10));
        Date rhs(Year(2021), Month(11), Day(11));
        MyAssert(lhs != rhs, true, "operator !=");

        Date nlhs(Year(2020), Month(1), Day(10));
        Date nrhs(Year(2020), Month(1), Day(10));
        MyAssert(nlhs != nrhs, false, "operator !=");
    }

    {
        Date lhs(Year(2020), Month(1), Day(10));
        Date rhs(Year(2021), Month(11), Day(11));
        MyAssert(lhs < rhs, true, "operator <");

        Date nlhs(Year(2021), Month(11), Day(11));
        Date nrhs(Year(2020), Month(1), Day(10));
        MyAssert(nlhs < nrhs, false, "operator <");
    }

    {
        Date lhs(Year(2020), Month(1), Day(10));
        Date rhs(Year(2021), Month(11), Day(11));
        MyAssert(rhs > lhs, true, "operator >");

        Date nlhs(Year(2021), Month(11), Day(11));
        Date nrhs(Year(2020), Month(1), Day(10));
        MyAssert(nrhs > nlhs, false, "operator >");
    }

    {
        Date lhs(Year(2020), Month(1), Day(10));
        Date rhs(Year(2021), Month(11), Day(11));
        MyAssert(lhs <= rhs, true, "operator <=");

        Date lhs1(Year(2020), Month(1), Day(10));
        Date rhs1(Year(2020), Month(1), Day(10));
        MyAssert(lhs1 <= rhs1, true, "operator <=");

        Date nlhs(Year(2021), Month(11), Day(11));
        Date nrhs(Year(2020), Month(1), Day(10));
        MyAssert(nlhs <= nrhs, false, "operator <=");
    }

    {
        Date lhs(Year(2020), Month(1), Day(10));
        Date rhs(Year(2021), Month(11), Day(11));
        MyAssert(rhs >= lhs, true, "operator >=");

        Date lhs1(Year(2020), Month(1), Day(10));
        Date rhs1(Year(2020), Month(1), Day(10));
        MyAssert(rhs >= lhs, true, "operator >=");

        Date nlhs(Year(2021), Month(11), Day(11));
        Date nrhs(Year(2020), Month(1), Day(10));
        MyAssert(nrhs >= nlhs, false, "operator >=");
    }
}

void TEST_PARSE_DATE(){
    {
        std::istringstream is("2017-08-12");
        Date date = ParseDate(is);
        MyAssert(date.getYear(), 2017, "date Year");
        MyAssert(date.getMonth(), 8, "date Month");
        MyAssert(date.getDay(), 12, "date Day");
    }

    {
        std::istringstream is("1-1-1");
        Date date = ParseDate(is);
        MyAssert(date.getYear(), 1, "date Year");
        MyAssert(date.getMonth(), 1, "date Month");
        MyAssert(date.getDay(), 1, "date Day");
    }

    {
        std::istringstream is("2017-10-32");
        try {
            Date date = ParseDate(is);
        } catch (std::runtime_error& msg) {
            std::cerr << "TEST_PARSE_DATE: " << msg.what() << std::endl;
        }
    }

    {
        std::istringstream is("1-0-3");
        try {
            Date date = ParseDate(is);
        } catch (std::runtime_error& msg){
            std::cerr << "TEST_PARSE_DATE: " << msg.what() << std::endl;
        }
    }

    {
        std::istringstream is("1--0-");
        try {
            Date date = ParseDate(is);
        } catch (std::runtime_error& msg){
            std::cerr << "TEST_PARSE_DATE: " << msg.what() << std::endl;
        }
    }

    {
        std::istringstream is("1---0-");
        try {
            Date date = ParseDate(is);
        } catch (std::runtime_error& msg){
            std::cerr << "TEST_PARSE_DATE: " << msg.what() << std::endl;
        }
    }

    {
        std::istringstream is("g-0-g");
        try {
            Date date = ParseDate(is);
        } catch (std::runtime_error& msg){
            std::cerr << "TEST_PARSE_DATE: " << msg.what() << std::endl;
        }
    }
}




void TEST_PARSE_CONDITION() {
    {
        istringstream is("date != 2017-11-18");
        shared_ptr<Node> root = ParseCondition(is);
        MyAssert(root->Evaluate(Date(Year(2017), Month(1), Day(1)), ""), true, "Parse condition 1");
        MyAssert(!root->Evaluate(Date(Year(2017), Month(11), Day(18)), ""), true, "Parse condition 2");
    }
    {
        istringstream is(R"(event == "sport event")");
        shared_ptr<Node> root = ParseCondition(is);
        MyAssert(root->Evaluate(Date(Year(2017), Month(1), Day(1)), "sport event"), true, "Parse condition 3");
        MyAssert(!root->Evaluate(Date(Year(2017), Month(1), Day(1)), "holiday"), true, "Parse condition 4");
    }
    {
        istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
        shared_ptr<Node> root = ParseCondition(is);
        MyAssert(root->Evaluate(Date(Year(2017), Month(1), Day(1)), ""), true, "Parse condition 5");
        MyAssert(root->Evaluate(Date(Year(2017), Month(3), Day(1)), ""), true, "Parse condition 6");
        MyAssert(root->Evaluate(Date(Year(2017), Month(6), Day(30)), ""), true, "Parse condition 7");
        MyAssert(!root->Evaluate(Date(Year(2017), Month(7), Day(1)), ""), true, "Parse condition 8");
        MyAssert(!root->Evaluate(Date(Year(2016), Month(12), Day(31)), ""), true, "Parse condition 9");
    }
    {
        istringstream is(R"(event != "sport event" AND event != "Wednesday")");
        shared_ptr<Node> root = ParseCondition(is);
        MyAssert(root->Evaluate(Date(Year(2017), Month(1), Day(1)), "holiday"), true, "Parse condition 10");
        MyAssert(!root->Evaluate(Date(Year(2017), Month(1), Day(1)), "sport event"), true, "Parse condition 11");
        MyAssert(!root->Evaluate(Date(Year(2017), Month(1), Day(1)), "Wednesday"), true, "Parse condition 12");
    }
    {
        istringstream is(R"(event == "holiday AND date == 2017-11-18")");
        shared_ptr<Node> root = ParseCondition(is);
        MyAssert(!root->Evaluate(Date(Year(2017), Month(11), Day(18)), "holiday"), true, "Parse condition 13");
        MyAssert(!root->Evaluate(Date(Year(2017), Month(11), Day(18)), "work day"), true, "Parse condition 14");
        MyAssert(root->Evaluate(Date(Year(1), Month(1), Day(1)), "holiday AND date == 2017-11-18"), true, "Parse condition 15");
    }
    {
        istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
        shared_ptr<Node> root = ParseCondition(is);
        MyAssert(root->Evaluate(Date(Year(2017), Month(1), Day(1)), "holiday"), true, "Parse condition 16");
        MyAssert(!root->Evaluate(Date(Year(2017), Month(1), Day(2)), "holiday"), true, "Parse condition 17");
    }
    {
        istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
        shared_ptr<Node> root = ParseCondition(is);
        MyAssert(!root->Evaluate(Date(Year(2016), Month(1), Day(1)), "holiday"), true, "Parse condition 18");
        MyAssert(root->Evaluate(Date(Year(2017), Month(1), Day(2)), "holiday"), true, "Parse condition 19");
        MyAssert(root->Evaluate(Date(Year(2017), Month(1), Day(2)), "workday"), true, "Parse condition 20");
        MyAssert(!root->Evaluate(Date(Year(2018), Month(1), Day(2)), "workday"), true, "Parse condition 21");
    }
    {
        istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
        shared_ptr<Node> root = ParseCondition(is);
        MyAssert(root->Evaluate(Date(Year(2016), Month(1), Day(1)), "event"), true, "Parse condition 22");
        MyAssert(root->Evaluate(Date(Year(2017), Month(1), Day(2)), "holiday"), true, "Parse condition 23");
        MyAssert(root->Evaluate(Date(Year(2017), Month(1), Day(2)), "workday"), true, "Parse condition 24");
        MyAssert(!root->Evaluate(Date(Year(2018), Month(1), Day(2)), "workday"), true, "Parse condition 25");
    }
    {
        istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
        shared_ptr<Node> root = ParseCondition(is);
        MyAssert(root->Evaluate(Date(Year(2017), Month(1), Day(1)), "holiday"), true, "Parse condition 26");
        MyAssert(!root->Evaluate(Date(Year(2017), Month(1), Day(2)), "holiday"), true, "Parse condition 27");
    }
    {
        istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
        shared_ptr<Node> root = ParseCondition(is);
        MyAssert(root->Evaluate(Date(Year(1), Month(1), Day(1)), "2017-01-01"), true, "Parse condition 28");
        MyAssert(!root->Evaluate(Date(Year(2016), Month(1), Day(1)), "event"), true, "Parse condition 29");
        MyAssert(root->Evaluate(Date(Year(2016), Month(1), Day(2)), "event"), true, "Parse condition 30");
    }
}

void TEST_ADD(){
    Database db;
    Date a(Year(2017), Month(6), Day(1));
    Date b(Year(2017), Month(6), Day(2));
    {
        db.Add(a, "1st of June");
        MyAssert(db.find(Date(Year(2017), Month(6), Day(1))) != db.end(), true, "first add");
        MyAssert(db.at(Date(Year(2017), Month(6), Day(1))) == "1st of June", true, "first add");
    }

    {
        db.Add(b, "2st of June");
        MyAssert(db.find(Date(Year(2017), Month(6), Day(2))) != db.end(), true, "second add");
        MyAssert(db.at(Date(Year(2017), Month(6), Day(2))) == "2st of June", true, "second add");
    }
}

void TEST_REMOVE_IF(){
    Date a(Year(2017), Month(6), Day(1));
    Date b(Year(2017), Month(6), Day(2));
    Date c(Year(2017), Month(6), Day(3));
    {
        Database db;
        db.Add(a, "1st of June");
        std::istringstream is("date == 2017-06-01");

        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
        };
        int count = db.RemoveIf(predicate);

        MyAssert(db.find(Date(Year(2017), Month(6), Day(1))) != db.end(), false, "removeIf 1");
    }

    {
        Database db;
        db.Add(a, "1st of June");
        std::istringstream is1("event == 1st of June");

        auto condition = ParseCondition(is1);
        auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
        };
        int count = db.RemoveIf(predicate);

        MyAssert(db.find(Date(Year(2017), Month(6), Day(1))) != db.end(), false, "removeIf 2");
    }

    {
        Database db;
        db.Add(a, "1st of June");
        db.Add(b, "2st of June");
        db.Add(c, "3st of June");
        std::istringstream is1("date <= 2017-06-03");

        auto condition = ParseCondition(is1);
        auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
        };
        int count = db.RemoveIf(predicate);

        MyAssert(db.empty(), true, "removeIf 3");
    }

    {
        Database db;
        db.Add(a, "1st of June");
        db.Add(b, "2st of June");
        db.Add(c, "3st of June");
        std::istringstream is1("date < 2017-06-03");

        auto condition = ParseCondition(is1);
        auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
        };
        int count = db.RemoveIf(predicate);

        MyAssert(db.size() == 1, true, "removeIf 4");
    }

    {
        Database db;
        db.Add(a, "1st of June");
        db.Add(b, "2st of June");
        db.Add(c, "3st of June");
        std::istringstream is1("date < 2017-06-03 AND date > 2017-06-01");

        auto condition = ParseCondition(is1);
        auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
        };
        int count = db.RemoveIf(predicate);

        MyAssert(db.find(a) == db.end(), true, "removeIf 5.1");
        MyAssert(db.find(b) != db.end(), true, "removeIf 5.2");
        MyAssert(db.find(c) == db.end(), true, "removeIf 5.3");
    }

    {
        Database db;
        db.Add(a, "1st of June");
        db.Add(a, "2st of June");
        db.Add(a, "3st of June");
        std::istringstream is1("event == 1st of June AND event == 2st of June");

        auto condition = ParseCondition(is1);
        auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
        };
        int count = db.RemoveIf(predicate);

        MyAssert(db.find(a)->second.size() == 1, true, "removeIf 6");
    }

    {
        Database db;
        db.Add(a, "1st of June");
        db.Add(a, "2st of June");
        db.Add(a, "3st of June");
        std::istringstream is1("event != 1st of June AND event != 2st of June");

        auto condition = ParseCondition(is1);
        auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
        };
        int count = db.RemoveIf(predicate);

        MyAssert(db.find(a)->second.size() == 2, true, "removeIf 7");
    }
}

#endif //WEEK6_MYTESTS_H
