#include <iostream>
#include <vector>
#include <algorithm>

using IT = std::vector<int>::const_iterator;

void PrintVectorPart(const std::vector<int>& numbers){
    IT it_begin = numbers.begin();
    IT it_end = std::find_if(numbers.begin(), numbers.end(), [](const int& negative){return negative < 0;});
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