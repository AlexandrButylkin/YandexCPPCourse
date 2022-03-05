#include <iostream>
#include <sstream>
#include <deque>


bool AddStaples(const std::string& prev_operation, const std::string& curr_operation){
    return (curr_operation == "*" || curr_operation == "/") &&
    (prev_operation == "+" || prev_operation == "-");
}


int main() {
    std::string number;
    int count = 0;
    std::cin >> number >> count;
    std::deque<std::string> res = {number};
    std::string pred_operation = " ";

    while(count > 0){
        std::string curr_operation = " ";
        std::string curr_number;

        std::cin >> curr_operation >> curr_number;

        if(AddStaples(pred_operation, curr_operation)){

            res.emplace_front("(");
            res.emplace_back(") " + curr_operation + " ");
            res.emplace_back(std::move(curr_number));

        } else {

            res.emplace_back(" " + curr_operation + " ");
            res.emplace_back(std::move(curr_number));

        }

        pred_operation = std::move(curr_operation);
        --count;
    }

    for(const auto& item : res){
        std::cout << item;
    }

    return 0;
}
