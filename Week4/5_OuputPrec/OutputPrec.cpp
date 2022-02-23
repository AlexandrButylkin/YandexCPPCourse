#include <iostream>
#include <fstream>
#include <iomanip>

int main(){
    std::ifstream file("input.txt");
    if(file.is_open()){
        float str = 0.0;
        while(!file.eof()){
            file >> str;
            std::cout << std::fixed << std::setprecision(3) << str << std::endl;
        }
        file.close();
    } else std::cout << "Error!!!" << std::endl;
    return 0;
}