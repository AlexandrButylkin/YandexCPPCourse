#include "Common.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

class NodeNumber : public Expression{
public:

    NodeNumber(int value_) : value(value_) {}



    int Evaluate() const final{
        return value;
    }

    std::string ToString() const final{
        return std::to_string(value);
    }

private:
    int value;
};

class NodeOperation : public Expression{
public:
    NodeOperation(ExpressionPtr value_left, ExpressionPtr value_right) : left(move(value_left)), right(move(value_right)){}

    std::string ToString() const final{
        return "(" + LeftToString() + ")" + Operation() + "(" + RightToString() + ")";
    }

protected:
    std::string LeftToString() const {
        return left->ToString();
    }

    std::string RightToString() const {
        return right->ToString();
    }

    virtual char Operation() const = 0;

    ExpressionPtr left;
    ExpressionPtr right;
};

class NodeOperationSum : public NodeOperation {
public:
    explicit NodeOperationSum(ExpressionPtr value_left, ExpressionPtr value_right) :
            NodeOperation(move(value_left), move(value_right)){}

    int Evaluate() const override {
        return left->Evaluate() + right->Evaluate();
    }

    char Operation() const final {
        return '+';
    }

};

class NodeOperationProduct : public NodeOperation {
public:
    explicit NodeOperationProduct(ExpressionPtr value_left, ExpressionPtr value_right) :
            NodeOperation(move(value_left), move(value_right)){}

    int Evaluate() const override {
        return left->Evaluate() * right->Evaluate();
    }

    char Operation() const final {
        return '*';
    }


};

// Функции для формирования выражения
ExpressionPtr Value(int value){
    std::unique_ptr<NodeNumber> res = std::make_unique<NodeNumber>(value);
    return move(res);
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right){
    std::unique_ptr<NodeOperationSum> res = std::make_unique<NodeOperationSum>(move(left), move(right));
    return move(res);
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right){
    std::unique_ptr<NodeOperationProduct> res = std::make_unique<NodeOperationProduct>(move(left), move(right));
    return move(res);
}



string Print(const Expression* e) {
    if (!e) {
        return "Null expression provided";
    }
    stringstream output;
    output << e->ToString() << " = " << e->Evaluate();
    return output.str();
}

void Test() {
    ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
    ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

    ExpressionPtr e2 = Sum(move(e1), Value(5));
    ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

    ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, Test);
    return 0;
}