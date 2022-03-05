#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void swap(std::vector<int>& vec, int start, int end){
    int c = vec[start];
    vec[start] = vec[end];
    vec[end] = c;
}

void PrintVec(const std::vector<int>& vec){
    for(const int& item : vec){
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void rec(std::vector<int>& vec, int start, int end){
    if(start == end){;
        PrintVec(vec);
        return;
    } else {
        for(int i = start; i <= end; i++) {
            swap(vec, i, start);
            rec(vec, start + 1, end);
            swap(vec, i, start);
        }
        return;
    }
}

void perm(std::vector<int>& vec){
    std::vector<int> vec2 = vec;
    PrintVec(vec);
    prev_permutation(vec.begin(), vec.end());
    while(vec2 != vec) {
        PrintVec(vec);
        prev_permutation(vec.begin(), vec.end());
    }
}


int main(){
    int num = 0;
    std:cin >> num;
    std::vector<int> vec;
    vec.reserve(num);
    for(int i = num; i >= 1; --i){
        vec.emplace_back(i);
    }
    perm(vec);
    //rec(vec, 0, num - 1);
}
