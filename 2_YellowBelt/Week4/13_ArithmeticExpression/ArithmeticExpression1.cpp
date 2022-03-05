#include <iostream>
#include <deque>



int main() {
    std::string number;
    int count = 0;
    std::cin >> number >> count;

    std::deque<std::string> res = {number};

    while(count > 0){
        std::string operation;
        std::string curr_number;

        std::cin >> operation >> curr_number;

        res.emplace_front("(");
        res.emplace_back(") " + operation + " ");
        res.emplace_back(curr_number);

        --count;
    }

    for(const auto& item : res){
        std::cout << item;
    }

    return 0;
}
