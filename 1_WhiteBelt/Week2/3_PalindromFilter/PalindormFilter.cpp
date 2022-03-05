#include <iostream>
#include <vector>
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

std::vector<std::string> PalindromFilter(std::vector<std::string> words, int minLength){
    std::vector<std::string> ans;
    for(std::string str : words){
        if(IsPalindrom(str) && str.size() >= minLength){
            ans.push_back(str);
        }
    }
    return ans;
}

int main(){
	std::vector<std::string> strs;
    std::string str;
	while(1){
        std::cin >> str;
        if(str == "1"){
            break;
        }
        strs.push_back(str);
    }
    strs = PalindromFilter(strs, 4);
    for(auto str : strs){
        std::cout << str << std::endl;
    }
	return 0;
}
