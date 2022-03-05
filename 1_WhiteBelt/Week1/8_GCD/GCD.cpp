#include <iostream>

int main(){
	int a = 0, b = 0;
	std::cin >> a >> b;
	while(a > 0 && b > 0){
		if(a >= b){
			a = a % b;
		}
		else{
			b = b % a;
		}
	}
	std::cout << a + b << std::endl;
	return 0;
}
