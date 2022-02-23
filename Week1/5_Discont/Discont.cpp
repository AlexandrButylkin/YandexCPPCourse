#include <iostream>

int main(){
	double N = 0.0, A = 0.0, B = 0.0, X = 0.0, Y = 0.0;
	std::cin >> N >> A >> B >> X >> Y;
	if(N > B){
		std::cout << N * (1 - Y / 100) << std::endl;
		return 0;
	}
	else if(N > A){
		std::cout << N * (1 - X / 100) << std::endl;
		return 0;
	}
	std::cout << N << std::endl;
	return 0;
}

