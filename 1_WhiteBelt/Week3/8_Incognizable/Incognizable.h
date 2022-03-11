#ifndef INCOGNIZABLE_H_
#define INCOGNIZABLE_H_

#include <vector>

class Incognizable {
private:
    std::vector<int> vec;
public:
    Incognizable(){};
    Incognizable(const std::initializer_list<int>& list) : vec(list) {}
    Incognizable(const Incognizable& inc) : vec(inc.vec) {}
    Incognizable operator=(const Incognizable& inc){
        vec = inc.vec;
        return *this;
    }
    Incognizable operator=(const std::initializer_list<int>& inc){
        vec = inc;
        return *this;
    }
};

#endif