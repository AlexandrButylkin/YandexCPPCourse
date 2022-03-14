#ifndef WEEK6_NODE_H
#define WEEK6_NODE_H

#include <string>
#include <memory>

#include "date.h"

enum class LogicalOperation{
    And,
    Or
};

namespace Nodes {
    class Base {
    public:
        virtual bool Evaluate(const Date &date,
                              const std::string &event) const = 0;

        ~Base() = default;
    };

    class Empty : public Base {
    public:
        bool Evaluate(const Date &date,
                      const std::string &event) const override;
    };

    class LogicalOperationNode : public Base {
    public:
        LogicalOperationNode(LogicalOperation operation,
                             std::shared_ptr<Base> nodeLeft,
                             std::shared_ptr<Base> nodeRight);

        bool Evaluate(const Date &date, const std::string &event) const override;

    private:
        LogicalOperation operation_;
        std::shared_ptr<Base> nodeLeft_;
        std::shared_ptr<Base> nodeRight_;

    };


    enum class Comparison {
        Less,
        LessOrEqual,
        Greater,
        GreaterOrEqual,
        Equal,
        NotEqual
    };

    class DateComparison : public Base {
    public:
        DateComparison(Comparison cmp, Date date);

        bool Evaluate(const Date &date, const std::string &event) const override;

    private:
        Comparison cmp_;
        Date value_;
    };

    class EventComparison : public Base {
    public:
        EventComparison(Comparison cmp, std::string value);

        bool Evaluate(const Date &date, const std::string &event) const override;

    private:
        std::string value_;
        Comparison cmp_;
    };

    template <typename T>
    bool Compare(const T& lhs, const T& rhs, Comparison cmp) {
        switch (cmp) {
            case Comparison::Less:
                return lhs < rhs;
            case Comparison::LessOrEqual:
                return lhs <= rhs;
            case Comparison::Equal:
                return lhs == rhs;
            case Comparison::NotEqual:
                return lhs != rhs;
            case Comparison::Greater:
                return lhs > rhs;
            case Comparison::GreaterOrEqual:
                return lhs >= rhs;
        }
    }
}


//TESTS
void TestDateComparisonNode();
void TestEventComparisonNode();
void TestLogicalOperationNode();


#endif //WEEK6_NODE_H
