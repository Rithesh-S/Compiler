#pragma once  //prevents from creating a duplicate

#include <string> 
#include "TokenType.h"
using namespace std;

struct Token {
    TokenType type;
    string lex;
    int line;

    Token(TokenType type, string lex, int line)
        : type(type), lex(move(lex)), line(line) {}
    /* move() is used to say the compiler to get the data from the old location instead of 
    creating a new expensive copy, for performance optimization. */
};
