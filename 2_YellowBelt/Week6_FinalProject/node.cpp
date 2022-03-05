//
// Created by cobak on 19.11.2021.
//

#include "node.h"
#include <iostream>
bool LogicalOperationNode::Evaluate(const Date &date, const std::string &event) const {
    switch (operation) {
        case LogicalOperation::And:
            return nodeLeft->Evaluate(date, event) && nodeRight->Evaluate(date, event);
        case LogicalOperation::Or:
            return nodeLeft->Evaluate(date, event) || nodeRight->Evaluate(date, event);
    }
}

bool DateComparisonNode::Evaluate(const Date &date, const std::string &event) const {

    switch (cmp) {
        case Comparison::Equal:
            return date == value;
        case Comparison::NotEqual:
            return  date != value;
        case Comparison::Less:
            return date < value;
        case Comparison::Greater:
            return date > value;
        case Comparison::LessOrEqual:
            return date <= value;
        case Comparison::GreaterOrEqual:
            return date >= value;
    }
}

bool EventComparisonNode::Evaluate(const Date &date, const std::string &event) const {
    switch (cmp) {
        case Comparison::Equal:
            return event == value;
        case Comparison::NotEqual:
            return  event != value;
        case Comparison::Less:
            return event < value;
        case Comparison::Greater:
            return event > value;
        case Comparison::LessOrEqual:
            return event <= value;
        case Comparison::GreaterOrEqual:
            return event >= value;
    }
}
