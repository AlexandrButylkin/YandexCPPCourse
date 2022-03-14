#include "condition_parser.h"
#include "TestRunner.h"


#include <sstream>
using namespace std;
using namespace Nodes;

void TestParseCondition() {
    {
        istringstream is("date != 2017-11-18");
        shared_ptr<Base> root = ParseCondition(is);
        Assert(root->Evaluate({Year(2017), Month(1), Day(1)}, ""),
               "Parse condition 1");

        Assert(!root->Evaluate({Year(2017), Month(11), Day(18)}, ""),
               "Parse condition 2");
    }

    {
        istringstream is(R"(event == "sport event")");
        shared_ptr<Base> root = ParseCondition(is);
        Assert(root->Evaluate({Year(2017), Month(1), Day(1)}, "sport event"),
               "Parse condition 3");

        Assert(!root->Evaluate({Year(2017), Month(1), Day(1)}, "holiday"),
               "Parse condition 4");
    }

    {
        istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
        shared_ptr<Base> root = ParseCondition(is);
        Assert(root->Evaluate({Year(2017), Month(1), Day(1)}, ""),
               "Parse condition 5");

        Assert(root->Evaluate({Year(2017), Month(3), Day(1)}, ""),
               "Parse condition 6");

        Assert(root->Evaluate({Year(2017), Month(6), Day(30)}, ""),
               "Parse condition 7");

        Assert(!root->Evaluate({Year(2017), Month(7), Day(1)}, ""),
               "Parse condition 8");

        Assert(!root->Evaluate({Year(2017), Month(12), Day(31)}, ""),
               "Parse condition 9");
    }

    {
        istringstream is(R"(event != "sport event" AND event != "Wednesday")");
        shared_ptr<Base> root = ParseCondition(is);
        Assert(root->Evaluate({Year(2017), Month(1), Day(1)}, "holiday"),
               "Parse condition 10");

        Assert(!root->Evaluate({Year(2017), Month(1), Day(1)}, "sport event"),
               "Parse condition 11");

        Assert(!root->Evaluate({Year(2017), Month(1), Day(1)}, "Wednesday"),
               "Parse condition 12");
    }

    {
        istringstream is(R"(event == "holiday AND date == 2017-11-18")");
        shared_ptr<Base> root = ParseCondition(is);
        Assert(!root->Evaluate({Year(2017), Month(11), Day(18)}, "holiday"),
               "Parse condition 13");

        Assert(!root->Evaluate({Year(2017), Month(11), Day(18)}, "work day"),
               "Parse condition 14");

        Assert(root->Evaluate({Year(1), Month(1), Day(1)}, "holiday AND date == 2017-11-18"),
               "Parse condition 15");
    }

    {
        istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
        shared_ptr<Base> root = ParseCondition(is);
        Assert(root->Evaluate({Year(2017), Month(1), Day(1)}, "holiday"),
               "Parse condition 16");

        Assert(!root->Evaluate({Year(2017), Month(1), Day(2)}, "holiday"),
               "Parse condition 17");
    }

    {
        istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
        shared_ptr<Base> root = ParseCondition(is);
        Assert(!root->Evaluate({Year(2016), Month(1), Day(1)}, "holiday"),
               "Parse condition 18");

        Assert(root->Evaluate({Year(2017), Month(1), Day(2)}, "holiday"),
               "Parse condition 19");

        Assert(root->Evaluate({Year(2017), Month(1), Day(2)}, "workday"),
               "Parse condition 20");

        Assert(!root->Evaluate({Year(2018), Month(1), Day(2)}, "workday"),
               "Parse condition 21");
    }

    {
        istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
        shared_ptr<Base> root = ParseCondition(is);
        Assert(root->Evaluate({Year(2016), Month(1), Day(1)}, "event"),
               "Parse condition 22");

        Assert(root->Evaluate({Year(2017), Month(1), Day(2)}, "holiday"),
               "Parse condition 23");

        Assert(root->Evaluate({Year(2017), Month(1), Day(2)}, "workday"),
               "Parse condition 24");

        Assert(!root->Evaluate({Year(2018), Month(1), Day(2)}, "workday"),
               "Parse condition 25");
    }

    {
        istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
        shared_ptr<Base> root = ParseCondition(is);
        Assert(root->Evaluate({Year(2017), Month(1), Day(1)}, "holiday"),
               "Parse condition 26");

        Assert(!root->Evaluate({Year(2017), Month(1), Day(2)}, "holiday"),
               "Parse condition 27");
    }

    {
        istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
        shared_ptr<Base> root = ParseCondition(is);
        Assert(root->Evaluate({Year(1), Month(1), Day(1)}, "2017-01-01"),
               "Parse condition 28");

        Assert(!root->Evaluate({Year(2016), Month(1), Day(1)}, "event"),
               "Parse condition 29");

        Assert(root->Evaluate({Year(2017), Month(1), Day(2)}, "event"),
               "Parse condition 30");
    }
}