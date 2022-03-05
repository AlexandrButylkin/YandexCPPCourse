#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> SplitIntoWords(const string& s){
    if(s == "") return {};
    std::vector<string> vec;
    std::string str;
    for(auto it = s.begin(); it <= s.end(); ++it){
        if(*it == ' ' || it == s.end()){
            vec.push_back(std::move(str));
            str = "";
        } else str += *it;
    }
    return vec;
}

int main(){
    string s = "";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;
    return 0;
}