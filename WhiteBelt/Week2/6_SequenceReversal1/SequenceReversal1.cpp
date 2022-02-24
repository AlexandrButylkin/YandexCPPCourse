#include <iostream>
#include <vector>

void Reverse(std::vector<int>& vec){
    if(!vec.empty()){
        std::vector<int>::iterator beg = vec.begin();
        std::vector<int>::iterator end = vec.end() - 1;
        while(beg <= end){
            int i = *beg;
            *beg = *end;
            *end = i;
            beg++;
            end--;
        }
    }
}

int main(){
    std::vector<int> vec = {};
    Reverse(vec);
    for(auto i : vec){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}