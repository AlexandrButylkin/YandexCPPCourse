#ifndef TASK_3_LERNER_H
#define TASK_3_LERNER_H

#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Learner {
private:
    set<string> dict;

public:
    int Learn(const vector<string>& words) {
        int newWords = 0;
        for (const auto& word : words) {
            if(dict.emplace(word).second){
                ++newWords;
            }
        }
        return newWords;
    }

    [[nodiscard]] vector<string> KnownWords() const{
        return {dict.begin(), dict.end()};
    }
};

#endif //TASK_3_LERNER_H
