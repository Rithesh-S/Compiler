#pragma once

#include <string>
#include <vector>
#include "type/Token.h"

/* header class(abstract class), use for performance improvement by reducing the load 
cost of the entire file instead this file is loaded and when required the corresponding 
function is invoked */
class Lexer {

public:
    Lexer(string source);
    vector<Token> scanTokens();

private:
    const string source_;
    vector<Token> tokens_;

    int start_ = 0;
    int current_ = 0;
    int line_ = 1;

    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType type);

    char peek();
    bool isDigit(char c);
    void number();
    bool match(char expected);

};