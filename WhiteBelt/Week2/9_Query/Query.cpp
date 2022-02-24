#include <iostream>
#include <vector>

void WORRY(std::vector<bool>& vec){
    if(!vec.empty()){
        int i = 0;
        std::cin >> i;
        vec[i] = true;
    }
}

void QUIET(std::vector<bool>& vec){
    if(!vec.empty()){
        int i = 0;
        std::cin >> i;
        vec[i] = false;
    }
}

void COME(std::vector<bool>& vec){
    int i = 0;
    std::cin >> i;
    while(i > 0){
        vec.push_back(false);
        i--;
    }
    while(i < 0){
        vec.pop_back();
        i++;
    }
}

int WORRY_COUNT(const std::vector<bool>& vec){
    int i = 0;
    if(!vec.empty()){
        for(bool b : vec)
            if(b) i++;
    }
    return i;
}

int main(){
    int n = 0;
    std::string str = "";
    std::vector<bool> vec;
    std::cin >> n;
    while(n > 0){
        std::cin >> str;
        if(str == "COME"){
            COME(vec);
        }
        else if(str == "WORRY"){
            WORRY(vec);
        }
        else if(str == "QUIET"){
            QUIET(vec);
        }
        else if(str == "WORRY_COUNT"){
            std::cout << WORRY_COUNT(vec) << std::endl;
        }
        n--;
    }
    return 0;
}