#include <iostream>
#include <vector>

int month(int month){
    int mn;
    int k = month % 12;
    if(month % 12 == 1 || month % 12 == 3 || 
    month % 12 == 5 || month % 12 == 7 || 
    month % 12 == 8 || month % 12 == 10 || 
    month % 12 == 12 ||  month % 12 == 0)
        mn = 31;
    else if(month % 12 == 4 || month % 12 == 6 || 
    month % 12 == 9 || month % 12 == 11)
        mn = 30;
    else mn = 28;
    return mn;
}

void ADD(std::vector<std::vector<std::string>>& vec){
    int i = 0;
    std::string str = "";
    std::cin >> i >> str;
    vec[i - 1].push_back(str);
}

void DUMP(std::vector<std::vector<std::string>>& vec){
    int i = 0;
    std::cin >> i;
    std::cout << vec[i - 1].size() << " ";
    for(std::string q : vec[i - 1]){
        std::cout << q << " ";
    }
    std::cout << std::endl;
}

void NEXT(std::vector<std::vector<std::string>>& vec, int count){
    int mn = month(count);
    if(mn < vec.size()){
        for(size_t i = mn; i < vec.size(); i++){
            for(std::string str : vec[i]){
                vec[mn - 1].push_back(str);
            }
        }
    }
    vec.resize(mn);
}


int main(){
    int count = 1;
    int n = 0;
    std::string str = "";
    std::vector<std::vector<std::string>> vec(31);
    std::cin >> n;
    while(n > 0){
        std::cin >> str;
        if(str == "ADD"){
            ADD(vec);
        }
        else if(str == "DUMP"){
            DUMP(vec);
        }
        else if(str == "NEXT"){
            count++;
            NEXT(vec, count);
        }
        n--;
    }
    return 0;
}