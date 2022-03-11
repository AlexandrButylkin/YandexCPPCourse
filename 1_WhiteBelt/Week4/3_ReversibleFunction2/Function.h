#ifndef INC_3_REVERSIBLEFUNCTION1_FUNCTION_H
#define INC_3_REVERSIBLEFUNCTION1_FUNCTION_H


#include <vector>
#include <algorithm>

class FunctionPart final {
private:
    char operation;
    double value;
public:
    FunctionPart(const char& operation_, const double& value_) : operation(operation_), value(value_) {}

    double Apply(double new_value) const;
    void Invert();

};

class Function final {
private:
    std::vector<FunctionPart> v;
public:

    void AddPart(char operation, double num);
    double Apply(double num) const;
    void Invert();
};

#endif //INC_3_REVERSIBLEFUNCTION1_FUNCTION_H
