#include "../../Utils/TestRunner.h"

#include <iostream>
using namespace std;

//Old Macros
#define BAD_PRINT_VALUES(out, x, y) out << (x) << endl; out << (y) << endl

//New Macros
#define PRINT_VALUES(out, x, y)             \
        out << (x) << endl << (y) << endl   \



int main() {
    TestRunner tr;
    tr.RunTest([] {
        ostringstream output;
        PRINT_VALUES(output, 5, "red belt");
        ASSERT_EQUAL(output.str(), "5\nred belt\n");
    }, "PRINT_VALUES usage example");
    return 0;
}
