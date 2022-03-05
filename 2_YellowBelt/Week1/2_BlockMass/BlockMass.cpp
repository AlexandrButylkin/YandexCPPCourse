#include <iostream>
#include <vector>

int main() {
    unsigned long long n = 0, r = 0;
    std:: cin >> n >> r;

    unsigned long long a = 0, b = 0, c = 0, sum = 0;
    for(size_t i = 0; i < n; ++i){
        std::cin >> a >> b >> c;
        sum += a * b * c * r;
    }

    std::cout << sum << std::endl;
    return 0;
}