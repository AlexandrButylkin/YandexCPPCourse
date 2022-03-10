#include <iostream>
#include <vector>

int month(int month){
    if(month % 12 == 1 || month % 12 == 3 ||
       month % 12 == 5 || month % 12 == 7 ||
       month % 12 == 8 || month % 12 == 10 ||
       month % 12 == 12 ||  month % 12 == 0)
        return 31;
    else if(month % 12 == 4 || month % 12 == 6 ||
            month % 12 == 9 || month % 12 == 11)
        return 30;
    else return 28;
}

void ADD(std::vector<std::vector<std::string>>& vec){
    int i = 0;
    std::string str;
    std::cin >> i >> str;
    vec[i - 1].push_back(str);
}

void DUMP(std::vector<std::vector<std::string>>& vec){
    int i = 0;
    std::cin >> i;
    std::cout << vec[i - 1].size() << " ";
    for(const std::string& q : vec[i - 1]){
        std::cout << q << " ";
    }
    std::cout << std::endl;
}

void NEXT(std::vector<std::vector<std::string>>& vec, int count){
    int mn = month(count);
    if(mn < vec.size()){
        for(size_t i = mn; i < vec.size(); i++){
            for(const std::string& str : vec[i]){
                vec[mn - 1].push_back(str);
            }
        }
    }
    vec.resize(mn);
}


int main(){
    int count = 1;
    int n = 0;
    std::cin >> n;
    std::vector<std::vector<std::string>> vec(31);
    while(n > 0){
        std::string request;
        std::cin >> request;
        if(request == "ADD"){
            ADD(vec);
        }
        else if(request == "DUMP"){
            DUMP(vec);
        }
        else if(request == "NEXT"){
            ++count;
            NEXT(vec, count);
        }
        n--;
    }
    return 0;
}