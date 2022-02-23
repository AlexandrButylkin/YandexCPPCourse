#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <iostream>
#include <vector>
#include <algorithm>

class FunctionPart{
private:
    char operation;
    double value;
public:
    FunctionPart(const char& operation_, const double& value_) : operation(operation_), value(value_) {}
    double Apply(double new_value) const{
      if(operation == '+'){
        return value + new_value;
      }
      else if(operation == '-'){
        return new_value - value;
      }
      else if(operation == '*'){
        return new_value * value;
      }
      else if(operation == '/'){
        return  new_value / value;
      }
    };
    void Invert(){
      if(operation == '+'){
        operation = '-';
      }
      else if(operation == '-'){
        operation  = '+';
      }
      else if(operation == '*'){
        operation = '/';
      }
      else if(operation == '/'){
        operation = '*';
      }
    };

};

class Function{
private:
    std::vector<FunctionPart> v;
public:
    
    void AddPart(char operation, double num){
      v.push_back({operation, num});
    };

    double Apply(double num) const{
      for(const FunctionPart& part : v){
        num = part.Apply(num);
      }
      return num;
    };
    
    void Invert(){
      for(FunctionPart& part : v){
        part.Invert();
      }
      reverse(v.begin(), v.end());
    };
};

#endif