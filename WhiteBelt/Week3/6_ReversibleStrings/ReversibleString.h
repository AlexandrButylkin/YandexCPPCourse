#ifndef REVERSIBLESTRING_H_
#define REVERSIBLESTRING_H_

#include <iostream>

class ReversibleString {
public:
    ReversibleString() : str("") {}
    ReversibleString(const std::string& str_) : str(str_) {}
    ReversibleString(const ReversibleString& str_) : str(str_.str) {}
    ReversibleString& operator=(const ReversibleString& str_){
        if(this == &str_){
            return *this;
        }
        str = str_.str;
        return *this;
    };


    void Reverse(){
        std::string::iterator beg = str.begin();
        std::string::iterator end = str.end() - 1;
        while(beg <= end){
            char c = *beg;
            *beg = *end;
            *end = c;
            ++beg;
            --end;
        }
    }

    std::string ToString() const{
        return str;
    }

private:
    std::string str;
};
#endif