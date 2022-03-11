#include "Function.h"

double FunctionPart::Apply(double new_value) const{

    switch (operation) {
        case '+':
            return value + new_value;
        case '-':
            return new_value - value;
        default: return 0.0;
    }
}

void FunctionPart::Invert(){

    switch (operation) {
        case '+':
            operation = '-';
            break;
        case '-':
            operation  = '+';
            break;
    }

}

void Function::AddPart(char operation, double num){
    v.emplace_back(operation, num);
}

double Function::Apply(double num) const{
    for(const FunctionPart& part : v){
        num = part.Apply(num);
    }
    return num;
}

void Function::Invert(){
    for(FunctionPart& part : v){
        part.Invert();
    }
    reverse(v.begin(), v.end());
}