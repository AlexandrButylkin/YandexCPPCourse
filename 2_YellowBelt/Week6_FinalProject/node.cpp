#include "node.h"
#include <iostream>

namespace Nodes {

    bool Empty::Evaluate(const Date &date,
                         const std::string &event) const {
        return true;
    }


    LogicalOperationNode::LogicalOperationNode(LogicalOperation operation,
                                               std::shared_ptr<Base> nodeLeft,
                                               std::shared_ptr<Base> nodeRight) :
            operation_(operation),
            nodeLeft_(std::move(nodeLeft)),
            nodeRight_(std::move(nodeRight)) {}

    bool LogicalOperationNode::Evaluate(const Date &date,
                                        const std::string &event) const {
        switch (operation_) {
            case LogicalOperation::And:
                return nodeLeft_->Evaluate(date, event) && nodeRight_->Evaluate(date, event);
            case LogicalOperation::Or:
                return nodeLeft_->Evaluate(date, event) || nodeRight_->Evaluate(date, event);
            default:
                return false;
        }
    }


    DateComparison::DateComparison(Comparison cmp,
                                   Date date) :
            cmp_(cmp),
            value_(date) {}

    bool DateComparison::Evaluate(const Date &date, const std::string &event) const {
        return Compare(date, value_, cmp_);
    }


    EventComparison::EventComparison(Comparison cmp, std::string value) :
            value_(std::move(value)),
            cmp_(cmp) {}

    bool EventComparison::Evaluate(const Date &date, const std::string &event) const {
        return Compare(event, value_, cmp_);
    }

}
