#include <iostream>
#include <vector>
#include <numeric>

using namespace std;


int main(){
    int num = 0;
    std::cin >> num;
    std::vector<int> vec(num);
    std::iota(vec.rbegin(), vec.rend(), 1);

    do {
        for (int item : vec) {
            cout << item << ' ';
        }
        cout << endl;
    } while (prev_permutation(vec.begin(), vec.end()));

    return  0;
}
