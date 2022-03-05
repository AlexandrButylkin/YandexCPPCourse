#include <iostream>

void UpdateIfGreater(int a, int& b){
    if(a >= b) b = a;
}

int main(){
    int a = 10, b = 7;
    UpdateIfGreater(a, b);
    std::cout << "a = " << a << " b = " << b << std::endl;
    return 0;
}