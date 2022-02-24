#include <iostream>
#include <vector>
int main(){
	
	int a = 0;
	std::cin >> a;
	std::vector<int> ans;
	while(a != 0){
		ans.emplace(ans.begin(), a % 2);
		a /= 2;
	}
	for(int i : ans){
		std::cout << i;
	}
	std::cout << std::endl;
	return 0;
}
