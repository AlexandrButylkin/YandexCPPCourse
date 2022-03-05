#ifndef WEEK6_CONDITION_PARSER_H
#define WEEK6_CONDITION_PARSER_H


#include <memory>
#include <iostream>

#include "node.h"

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();


#endif //WEEK6_CONDITION_PARSER_H
