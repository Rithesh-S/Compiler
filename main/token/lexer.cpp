#include "Lexer.h"
#include <iostream>
#include <map>
using namespace std;

// Identifiers
map<string, TokenType> keywords = {
    { "v_", TokenType::V_ }
};

Lexer::Lexer(string source) : source_(move(source)) {}

// to scan all the tokens
vector<Token> Lexer::scanTokens() {
    while(!isAtEnd()) {
        start_ = current_;
        scanToken();
    }
    tokens_.emplace_back(TokenType::END_OF_FILE,"",line_);
    return tokens_;
}

//says whether this is the end of file
bool Lexer::isAtEnd() {
    return current_ >= source_.length();
}

//mover function and returns the consumed character
char Lexer::advance() {
    current_++;
    return source_[current_-1];
}

//to slice and add the token
void Lexer::addToken(TokenType type) {
    string text = source_.substr(start_,current_-start_);
    tokens_.emplace_back(type,text,line_);
}

//return whether it is digit or not
bool Lexer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

//return the current character
char Lexer::peek() {
    if(isAtEnd()) return '\0';
    return source_[current_];
}

//accepts and inserts the number
void Lexer::number() {
    while(isDigit(peek())) {
        advance();
    }
    addToken(TokenType::NUMBER);
}

bool Lexer::isAlpha(char c) {
    return (
        (c >= 'a' && c <= 'z') || 
        (c >= 'A' && c <= 'Z') ||
        (c == '_')
    );
}

bool Lexer::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

// advances as long as it is alphanumeric and checks whether it is a keyword and adds accordingly.
void Lexer::identifier() {
    while(isAlphaNumeric(peek())) advance();

    string text = source_.substr(start_,current_ - start_);

    if(keywords.count(text)) {
        addToken(keywords[text]);
    } else {
        addToken(TokenType::IDENTIFIER);
    }

}

bool Lexer::match(char expected) {
    if(isAtEnd()) return false;
    if(source_[current_] != expected) return false;
    current_++;
    return true;
}

//scans the individual characters
void Lexer::scanToken() {
    char c = advance();
    switch(c) {
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '+': addToken(TokenType::PLUS); break;
        case '-': addToken(TokenType::MINUS); break;
        case '*': addToken(TokenType::ASTERISK); break;
        case '/': addToken(TokenType::SLASH); break;
        case '>': addToken(TokenType::GREATER_THAN); break;
        case '=': addToken(TokenType::EQUAL); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '<': 
            if(match('-')) {
                a:
                while(peek() != '-'&& !isAtEnd()){
                    if(peek() == '\n') line_++;
                    advance();
                }

                if(isAtEnd()) {
                    cerr<<"Line "<<line_<<": Unterminated comment, expected '>'"<<endl;
                    break; 
                }
                advance();

                if(match('>')) {}
                else {
                    advance();
                    goto a;
                }
            } else {
                addToken(TokenType::LESSER_THAN); break;
            }

        case ' ':
        case '\r':
        case '\t':
            break;

        case '\n':
            line_++;
            break;

        default:
            if(isDigit(c)) {
                number();
            } else if(isAlpha(c)) {
                identifier();
            } else {
                cerr<<"Line"<<line_<<" : Unexpected Character '"<<c<<"'"<<endl;
            }
            break;
    }
}

