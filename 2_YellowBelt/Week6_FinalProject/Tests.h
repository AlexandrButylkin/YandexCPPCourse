#ifndef WEEK6_TESTS_H
#define WEEK6_TESTS_H

#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "database.h"
#include "TestRunner.h"


void Tests() {
    TestRunner tr;

    //Test Date
    tr.RunTest(TestDateOutput, "TestDateOutput");
    tr.RunTest(TestParseDate, "TestParseDate");

    //Test Condition Parser
    tr.RunTest(TestParseCondition, "TestParseCondition");

    //Test Nodes
    tr.RunTest(TestDateComparisonNode, "TestDateComparisonNode");
    tr.RunTest(TestEventComparisonNode, "TestEventComparisonNode");
    tr.RunTest(TestLogicalOperationNode, "TestLogicalOperationNode");

    //Test Database
    tr.RunTest(TestDatabaseAddAndPrint, "TestDatabaseAddAndPrint");
    tr.RunTest(TestDatabaseFind, "TestDatabaseFind");
    tr.RunTest(TestDatabaseRemove, "TestDatabaseRemove");
    tr.RunTest(TestDatabaseLast, "TestDatabaseLast");
    tr.RunTest(TestDatabaseException, "TestDatabaseException", true);
}


#endif //WEEK6_TESTS_H
