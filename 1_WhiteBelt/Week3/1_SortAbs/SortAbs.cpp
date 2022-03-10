#include <iostream>
#include <vector>

int main(){
    int n = 0;
    std::cin >> n;

    std::vector<int> A(n);
    for(auto& i : A){
        std::cin >> i;
    }

    std::sort(A.begin(), A.end(), [](int a, int b){return abs(a) < abs(b);});

    std::cout << std::endl;
    for(const auto& i : A){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}