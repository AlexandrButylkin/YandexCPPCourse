#include <iostream>

int Factorial(int n){
    if(n == 1){
        return 1;
    }
    return n * Factorial(n - 1);
}

int main(){
    int a = 0;
    std::cin >> a;
    std::cout << Factorial(a) << std::endl;
    return 0;
}
