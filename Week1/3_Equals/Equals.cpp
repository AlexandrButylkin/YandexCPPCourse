#include <iostream>
#include <cmath>
int main(){
	double a = 0.0, b = 0.0, c = 0.0;
	std::cin >> a >> b >> c;
	double d = pow(b, 2) - 4 * a * c;
	if(a != 0 && d > 0){
		double x1 = ((-b) + sqrt(d)) / (2 * a);
		double x2 = ((-b) - sqrt(d)) / (2 * a);
		std::cout << x1 << " " << x2 << std::endl;
		return 0;
	} 
	else if(a != 0 && d == 0){
		double x = (-b) / (2 * a);
		std::cout << x << std::endl;
		return 0;
	}
	else if(a != 0 && d < 0){
		return 0;
	}
	else if(a == 0 && b != 0){
		double x = (-c) / b; 
		std::cout << x << std::endl;
		return 0;
	}
	return 0;
}
