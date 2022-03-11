#include <iostream>
#include <map>
#include <set>

using std::map;
using std::string;
using std::set;

using Dictionary = map<string, set<string>>;

void add_map(Dictionary & map, const string& word1, const string& word2){
    std::set<std::string> set;
    set.emplace(word2);
    map.emplace(word1, set);
}

void ADD(Dictionary & dict, const string& word1, const string& word2) {

    dict[word1].emplace(word2);
    dict[word2].emplace(word1);

}

void COUNT(const Dictionary& dict, const string& word){

    const auto word_iter = dict.find(word);

    if(word_iter != dict.end()){
        std::cout << word_iter->second.size() << std::endl;
    } else {
        std::cout << 0 << std::endl;
    }
}

void CHECK(const Dictionary& dict, const string& word1, const string& word2){

    const auto word_iter = dict.find(word1);
    if(word_iter != dict.end()){
        if(word_iter->second.count(word2)){
            std::cout << "YES" << std::endl;
            return;
        }
    }
    std::cout << "NO" << std::endl;
}

int main(){
    Dictionary dict;
    int n = 0;
    std::cin >> n;

    while(n > 0){
        std::string request;
        std::cin >> request;

        if(request == "ADD"){
            string word1, word2;
            std::cin >> word1 >> word2;

            ADD(dict, word1, word2);
        }
        else if(request == "COUNT"){
            string word;
            std::cin >> word;

            COUNT(dict, word);
        }
        else if(request == "CHECK"){
            string word1, word2;
            std::cin >> word1 >> word2;

            CHECK(dict, word1, word2);
        }
        n--;
    }
    return 0;
}