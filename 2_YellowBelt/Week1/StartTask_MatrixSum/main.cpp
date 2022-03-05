#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
    while(true){
        try{
            Matrix a(2, 2);
            Matrix b(2, 2);
            std::cin >> a >> b;
            cout << (a == b) << std::endl;
            cout << a + b;
            cout << a.GetNumCols() << " " << a.GetNumRows() << " | " << b.GetNumCols() << " " << b.GetNumRows() << std::endl;
            std::cout << a.At(0, 1) << " " << a.At(1, 0) << std::endl;
            a.Reset(1, 2);
            b.Reset(0, 0);
            b.Reset(1, 0);
            b.Reset(0, 1);
            b.Reset(1, 1);
            if(a.GetNumRows() == 1){
                a.At(-1, -1);
            }
            std::cout << "END" << std::endl;
            return 0;
        }catch(invalid_argument& msg){
            std::cout << msg.what() << std::endl;
        }
        catch (out_of_range& msg){
            std::cout << msg.what() << std::endl;
        }
    }
}
