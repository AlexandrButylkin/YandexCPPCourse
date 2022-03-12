#include <iostream>
#include <vector>

void PrintVectorPart(const std::vector<int>& numbers){
    auto it_begin = numbers.begin();
    auto it_end = std::find_if(numbers.begin(), numbers.end(), [](const int& negative){return negative < 0;});
    while(it_end != it_begin){
        --it_end;
        std::cout << *it_end << " ";
    }
}

int main(){
    std::vector<int> a ={1, 2, 3, 4, 5, 5, 6, 7};
    PrintVectorPart(a);
    return 0;
}