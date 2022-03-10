#include <iostream>
#include <deque>

int main(){
    int a = 0;
    std::cin >> a;
    std::deque<int> number;

    while(a != 0){
        number.push_front(a % 2);
        a /= 2;
    }

    for(int i : number) std::cout << i;
    std::cout << std::endl;

    return 0;
}
