#include <iostream>

void UpdateIfGreater(int first, int& second){
    if(first >= second) second = first;
}

int main(){
    int a = 10, b = 7;
    UpdateIfGreater(a, b);
    std::cout << "a = " << a << " b = " << b << std::endl;
    return 0;
}