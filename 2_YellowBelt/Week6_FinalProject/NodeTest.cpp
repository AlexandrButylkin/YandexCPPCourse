#include "node.h"
#include "TestRunner.h"

#include <map>
using namespace std;
using namespace  Nodes;

void TestDateComparisonNode() {
    const Date november_1{Year(2017),
                          Month(11), Day(1)};
    const Date november_2{Year(2017),
                          Month(11), Day(2)};
    const Date november_3{Year(2017),
                          Month(11), Day(3)};

    DateComparison less(Comparison::Less, november_2);
    Assert(less.Evaluate(november_1, ""),
           "DateComparison: less 1");
    Assert(!less.Evaluate(november_3, ""),
           "DateComparison: less 2");

    DateComparison not_equal(Comparison::NotEqual, november_2);
    Assert(not_equal.Evaluate(november_1, ""),
           "DateComparison: not_equal 1");
    Assert(!not_equal.Evaluate(november_2, ""),
           "DateComparison: not_equal 2");

    DateComparison greater_eq(Comparison::GreaterOrEqual, november_2);
    Assert(greater_eq.Evaluate(november_2, ""),
           "DateComparison: greater_eq 1");
    Assert(greater_eq.Evaluate(november_3, ""),
           "DateComparison: greater_eq 2");
    Assert(!greater_eq.Evaluate(november_1, ""),
           "DateComparison: greater_eq 3");
}

void TestEventComparisonNode() {
    const Date january_1{Year(1970), Month(1), Day(1)};

    EventComparison less_eq(Comparison::LessOrEqual, "b");
    Assert(less_eq.Evaluate(january_1, "a"),
           "EventComparison: less_eq 1");
    Assert(!less_eq.Evaluate(january_1, "c"),
           "EventComparison: less_eq 2");
    Assert(less_eq.Evaluate(january_1, "b"),
           "EventComparison: less_eq 3");

    EventComparison equal(Comparison::Equal, "b");
    Assert(equal.Evaluate(january_1, "b"),
           "EventComparison: equal 1");
    Assert(!equal.Evaluate(january_1, "a"),
           "EventComparison: equal 2");
    Assert(!equal.Evaluate(january_1, "c"),
           "EventComparison: equal 3");

    EventComparison greater(Comparison::Greater, "b");
    Assert(greater.Evaluate(january_1, "c"),
           "EventComparison: greater 1");
    Assert(!greater.Evaluate(january_1, "b"),
           "EventComparison: greater 2");
    Assert(!greater.Evaluate(january_1, "a"),
           "EventComparison: greater 3");
}

struct FalseNode : Base {
    bool Evaluate(const Date&, const string&) const override {
        return false;
    };
};

void TestLogicalOperationNode() {
    {
        map<bool, shared_ptr<Base>> bool_to_node = {
                {false, make_shared<FalseNode>()},
                {true, make_shared<Empty>()}
        };

        for (bool value_one : {false, true}) {
            for (bool value_two : {false, true}) {
                LogicalOperationNode or_node(
                        LogicalOperation::Or,
                        bool_to_node[value_one], bool_to_node[value_two]
                );
                LogicalOperationNode and_node(
                        LogicalOperation::And,
                        bool_to_node[value_one], bool_to_node[value_two]
                );

                AssertEqual(or_node.Evaluate({}, ""),
                            value_one || value_two, "LogicalOperationNode Or");
                AssertEqual(and_node.Evaluate({}, ""),
                            value_one && value_two, "LogicalOperationNode And");
            }
        }
    }
    {
        LogicalOperationNode root(
                LogicalOperation::And,
                make_shared<DateComparison>(Comparison::Equal,
                                            Date{Year(2017), Month(11), Day(18)}),
                make_shared<EventComparison>(Comparison::Equal,
                                             "Saturday")
        );

        Assert(root.Evaluate({Year(2017), Month(11), Day(18)},
                             "Saturday"), "LogicalOperationNode propagates arguments 1");
        Assert(!root.Evaluate({Year(2017), Month(11), Day(18)},
                              "Friday"), "LogicalOperationNode propagates arguments 2");
        Assert(!root.Evaluate({Year(2017), Month(11), Day(1)},
                              "Saturday"), "LogicalOperationNode propagates arguments 1");
    }
}