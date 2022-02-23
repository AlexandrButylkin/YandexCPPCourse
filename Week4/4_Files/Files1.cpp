#include <iostream>
#include <fstream>

int main(){
    std::ifstream file("input.txt");
    if(file.is_open()){
        std::string str;
        while(getline(file, str)){
            std::cout << str << std::endl;
        }
        file.close();
    } else std::cout << "Error!!!" << std::endl;
    return 0;
}