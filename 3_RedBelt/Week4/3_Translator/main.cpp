#include <iostream>
#include "test_runner.h"
//#include "Translator.h"

#include <string>
#include <vector>
#include <map>


using namespace std;

class Translator {
public:

    Translator() {}

    void Add(string_view source, string_view target){

        auto it = forward.find(std::string(source));

        if(it != forward.end()){
            backward.erase(it->second);
        }


        forward[std::string(source)] = std::string(target);
        auto it2 = forward.find(std::string(source));
        backward[it2->second] = it2->first;

    }

    string_view TranslateForward(string_view source) const{
        auto it = forward.find(std::string(source));
        if(it != forward.end()){
            return it->second;
        } else return "";
    }

    string_view TranslateBackward(string_view target) const{
        auto it = backward.find(target);
        if(it != backward.end()){
            return it->second;
        } else return "";
    }


private:
    std::map<std::string, std::string> forward;
    std::map<std::string_view , std::string_view> backward;

};


void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);

    Translator t;
    t.Add(string("okno"), string("window"));
    t.Add(string("stol"), string("table"));
    t.Add(string("okno"), string("window1"));
    t.Add(string("stol"), string("table1"));
    t.Add(string("okno"), string("window2"));
    t.Add(string("stol"), string("table2"));
    t.Add(string("okno2"), string("window10"));
    t.Add(string("stol2"), string("table10"));


    std::cout << t.TranslateForward("okno") << "\n";
    std::cout << t.TranslateForward("okno2") << "\n";
    std::cout << t.TranslateForward("stol") << "\n";
    std::cout << t.TranslateForward("stol2") << "\n";

    std::cout << t.TranslateForward("window10") << "\n";
    std::cout << t.TranslateForward("window2") << "\n";
    std::cout << t.TranslateForward("table2") << "\n";
    std::cout << t.TranslateForward("table10") << "\n";


    return 0;
}

