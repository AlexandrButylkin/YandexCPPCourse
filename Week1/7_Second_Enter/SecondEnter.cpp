#include <iostream>

int main(){
	std::string str;
	std::cin >> str;
	int count = 0;
	int i = 0;
	while(count != 2 && i < str.size()){
		if(str[i] == 'f'){
			count++;
		}
		if(count == 2){
			std::cout << i << std::endl;
			return 0;
		}
		i++;
	}
	if(count == 0)
		std::cout << -2 << std::endl;
	else if(count == 1)
		std::cout << -1 << std::endl;
	return 0;
}
