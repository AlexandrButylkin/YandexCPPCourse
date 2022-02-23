#include <iostream>

int main(){
	int a = 0, b = 0;
	std::cin >> a >> b;
	if(a % 2 == 1){
		a++;
	}
	for(a; a <= b; a += 2){
		std::cout << a << " "; 
	}
	std::cout << std::endl;
	return 0;
}
