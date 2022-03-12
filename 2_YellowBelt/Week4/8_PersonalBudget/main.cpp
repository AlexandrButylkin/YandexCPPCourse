#include <iostream>
#include "Budget.h"

int main() {
    int count = 0;
    std::cin >> count;
    Budget b;

    while(count != 0) {
        std::string operation;
        Date from, to;
        std::cin >> operation >> from >> to;
        if(operation == "Earn"){
            double value;
            std::cin >> value;
            b.Earn(from, to, value);
        } else if (operation == "ComputeIncome"){
            std::cout << std::setprecision(25) << std::fixed << b.ComputeIncome(from, to) << "\n";
        } else if (operation == "PayTax") {
            double percent = 0.0;
            std::cin >> percent;
            percent = 1.0 - percent / 100;
            b.PayTax(from, to, percent);
        } else if (operation == "Spend"){
            double value;
            std::cin >> value;
            b.Spend(from, to, value);
        }
        --count;
    }
    return 0;
}