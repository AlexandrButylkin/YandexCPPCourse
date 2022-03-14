#ifndef WEEK6_CONDITION_PARSER_H
#define WEEK6_CONDITION_PARSER_H

#include "node.h"

#include <memory>
#include <iostream>

std::shared_ptr<Nodes::Base> ParseCondition(std::istream& is);

//TESTS
void TestParseCondition();


#endif //WEEK6_CONDITION_PARSER_H
