#include <string>
#include <vector>
using namespace std;

#define MYCONC(x, y) x##y
#define MYLINE(x, y) MYCONC(x, y)
#define UNIQ_ID MYLINE(var, __LINE__)

int main() {
    int UNIQ_ID = 0;
    string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = {"hello", "world"};
    vector<int> UNIQ_ID = {1, 2, 3, 4};
}