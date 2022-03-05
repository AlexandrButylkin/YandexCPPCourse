#ifndef WEEK6_NODE_H
#define WEEK6_NODE_H

#include <string>
#include <memory>

#include "date.h"

enum class Comparison{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation{
    And,
    Or
};

class Node {
public:
    virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date& date, const std::string& event) const override {return true;}
};

class LogicalOperationNode : public Node{
public:
    LogicalOperationNode(const LogicalOperation operation_, std::shared_ptr<Node> nodeLeft_, std::shared_ptr<Node> nodeRight_) :
    operation(operation_),
    nodeLeft(std::move(nodeLeft_)),
    nodeRight(std::move(nodeRight_)){}

    bool Evaluate(const Date& date, const std::string& event) const override;
private:
    LogicalOperation operation;
    std::shared_ptr<Node> nodeLeft;
    std::shared_ptr<Node> nodeRight;

};

class DateComparisonNode : public Node{
public:
    DateComparisonNode(Comparison cmp_, Date parse_date) : cmp(cmp_), value(parse_date) {}

    bool Evaluate(const Date& date, const std::string& event) const override;
private:
    Comparison cmp;
    Date value;
};

class EventComparisonNode : public Node{
public:
    EventComparisonNode(Comparison cmp_, std::string value_) : value(std::move(value_)), cmp(cmp_) {}

    bool Evaluate(const Date& date, const std::string& event) const override;
private:
    std::string value;
    Comparison cmp;
};



#endif //WEEK6_NODE_H
