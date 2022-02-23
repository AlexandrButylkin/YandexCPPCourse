#include <iostream>

bool IsPalindrom(std::string str){
	std::string::iterator beg = str.begin();
	std::string::iterator end = str.end() - 1;
	while(beg <= end){
		if(*beg != *end) return false;
		end--;
		beg++;
	}
	return true;
}

int main(){
	std::string str = "";
	std::cin >> str;
	std::cout << IsPalindrom(str) << std::endl;
	return 0;
}
