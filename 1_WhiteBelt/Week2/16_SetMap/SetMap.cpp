#include <iostream>
#include <map>
#include <set>

using std::set;
using std::string;

set<string> BuildMapValuesSet(const std::map<int, string>& m) {
    set<string> ans;

    for(const auto& item : m) {
        ans.emplace(item.second);
    }

    return ans;
}

int main(){
    std::map<int, std::string> map = {
            {1, "odd"},
            {2, "even"},
            {3, "odd"},
            {4, "even"},
            {5, "odd"}
    };

    for(const auto& item : BuildMapValuesSet(map)){
        std::cout << item << " ";
    }

    return 0;
}