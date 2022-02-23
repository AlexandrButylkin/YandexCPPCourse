#include <iostream>
#include <map>
#include <set>

std::set<std::string> BuildMapValuesSet(const std::map<int, std::string>& m) {
    std::set<std::string> ans;
    for(const std::pair<int , std::string>& item : m){
        ans.emplace(item.second);
    }
    return ans;
}

/*int main(){
    std::map<int, std::string> map = {
    {1, "odd"},
    {2, "even"},
    {3, "odd"},
    {4, "even"},
    {5, "odd"}
    };
    BuildMapValuesSet(map);
    
    return 0;
}*/