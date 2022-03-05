#include <iostream>
#include "SumReverseSort.h"

int main() {
    std::cout << Sum(1, 2) << std::endl;
    std::string s = "String";
    std::cout << Reverse(s) << std::endl;
    std::vector<int> nums = {1, 3, 45, 2, 41, 100};
    Sort(nums);
    for(const auto& item : nums){
        std::cout << item << " ";
    }
    std::cout << std::endl;
}
