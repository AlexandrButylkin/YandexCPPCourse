#include "test_runner.h"
//#include "../test_runner/test_runner.h"

#include <iostream>
using namespace std;

#define PRINT_VALUES(out, x, y)             \
        out << (x) << endl << (y) << endl   \
    

int main()
{
    if(true)
        PRINT_VALUES(cout, 5, 6);
    else std::cout << 10;
    return 0;
}
