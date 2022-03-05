#include <iostream>
#include <fstream>

int main(){
    std::ifstream file("input.txt");
    if(file.is_open()){
        std::ofstream file_out("output.txt", std::ios::trunc);
        std::string str;
        file_out.clear();
        while(getline(file, str)){
            file_out << str << std::endl;
        }
        file.close();
        file_out.close();
    } else std::cout << "Error!!!" << std::endl;
    
}