#include <iostream>
#include <fstream>
#include <iomanip>

int main(){
    std::ifstream file("input.txt");
    if(file.is_open()){
        int str = 0, n = 0, m = 0;
        file >> n >> m;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                file >> str;
                file.ignore(1);
                if(j != 0){
                    std::cout << ' ';
                }
                std::cout << std::setw(10) << str;
            }
            if(i != n - 1){
                std::cout << std::endl;
            }
        }
        file.close();
    } else std::cout << "Error!!!" << std::endl;
    return 0;
}