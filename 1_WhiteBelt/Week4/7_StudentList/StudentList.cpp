#include <iostream>
#include <vector>

struct Student {
    std::string first_name;
    std::string last_name;
    int day = 0;
    int month = 0;
    int year = 0;
};

Student parse(){
    Student student;
    getline(std::cin, student.first_name, ' ');
    getline(std::cin, student.last_name, ' ');
    std::cin >> student.day >> student.month >> student.year;
    getchar();
    return student;
}


int main(){
    int n = 0;
    std::cin >> n;
    std::cin.ignore(1);

    std::vector<Student> vec;
    vec.reserve(n);

    for(auto i = 0; i < n; ++i){
        vec.push_back(parse());
    }

    std::cin >> n;
    std::cin.ignore(1);

    while(n > 0){
        std::string request;
        getline(std::cin, request, ' ');

        int i = 0;
        std::cin >> i;
        std::cin.ignore(1);

        if(request == "name" && (i - 1 >= 0 && i - 1 < vec.size()))
            std::cout << vec[i].first_name << " " << vec[i].last_name << std::endl;
        else if(request == "date" && (i - 1 >= 0 && i - 1 < vec.size()))
            std::cout << vec[i - 1].day << "." << vec[i - 1].month << "." << vec[i - 1].year << std::endl;
        else std::cout << "bad request\n";
        --n;
    }
    return 0;
}