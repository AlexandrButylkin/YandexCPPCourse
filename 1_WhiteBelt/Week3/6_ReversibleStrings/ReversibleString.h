#ifndef INC_6_REVERSIBLESTRING_REVERSIBLESTRING_H
#define INC_6_REVERSIBLESTRING_REVERSIBLESTRING_H

#include <string>
#include <algorithm>

class ReversibleString final {
public:
    ReversibleString() : str() {}
    explicit ReversibleString(std::string str_) : str(std::move(str_)) {}
    ReversibleString(const ReversibleString& str_) = default;
    ReversibleString& operator=(const ReversibleString& str_) = default;

    void Reverse();

    std::string ToString() const{ return str; }
    std::string& ToString() { return str; }

private:
    std::string str;
};

#endif //INC_6_REVERSIBLESTRING_REVERSIBLESTRING_H
