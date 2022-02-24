#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

struct Student{
    std::string first_name;
    std::string last_name;
    int day;
    int month;
    int year;
};

Student parse(){
    Student student;
    getchar();
    getline(std::cin, student.first_name, ' ');
    getline(std::cin, student.last_name, ' ');
    std::cin >> student.day >> student.month >> student.year;
    return student;
}


int main(){
    int n = 0;
    std::cin >> n;
    std::vector<Student> vec;
    while(n > 0){
        vec.push_back(parse());
        --n;
    }
    std::cin >> n;
    while(n > 0){
        std::string str;
        int i = 0;
        getchar();
        getline(std::cin, str, ' ');
        std::cin >> i;
        --i;
        if(str == "name" && (i >= 0 && i < vec.size())) 
            std::cout << vec[i].first_name << " " << vec[i].last_name << std::endl;
        else if(str == "date" && (i >= 0 && i < vec.size()))
            std::cout << vec[i].day << "." << vec[i].month << "." << vec[i].year << std::endl;
        else std::cout << "bad request\n";
        --n;
    }
    return 0;
}