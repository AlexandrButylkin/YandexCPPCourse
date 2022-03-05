#ifndef WEEK6_TOKEN_H
#define WEEK6_TOKEN_H


#include <sstream>
#include <vector>
using namespace std;

enum class TokenType {
    DATE,
    EVENT,
    COLUMN,
    LOGICAL_OP,
    COMPARE_OP,
    PAREN_LEFT,
    PAREN_RIGHT,
};

struct Token {
    const string value;
    const TokenType type;
};

vector<Token> Tokenize(istream& cl);


#endif //WEEK6_TOKEN_H
