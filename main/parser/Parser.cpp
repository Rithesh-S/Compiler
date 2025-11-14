#include "Parser.h"
#include <stdexcept>

using namespace std;

Parser::Parser(vector<Token> tokens) :
    tokens_(move(tokens)) {}

/* In this file, the AST is build by setting the hierarechy. Term defines the addition and 
subtraction, Factor defines the division and multiplication, and Primary defines the numbers. 
The AST is constructed and the root pointer is returned.
*/

unique_ptr<Expr> Parser::parse() {
    return expression();
}

unique_ptr<Expr> Parser::expression() {
    return term();
}

unique_ptr<Expr> Parser::term() {
    unique_ptr<Expr> expr = factor();

    while(match({ TokenType::PLUS, TokenType::MINUS })) {
        Token op = previous();
        unique_ptr<Expr> right = factor();
        
        expr = make_unique<Binary>(move(expr),op,move(right));
    }

    return expr;
}

unique_ptr<Expr> Parser::factor() {
    unique_ptr<Expr> expr = primary();

    while(match({ TokenType::SLASH, TokenType::ASTERISK })) {
        Token op = previous();
        unique_ptr<Expr> right = primary();

        expr = make_unique<Binary>(move(expr),op,move(right));
    }

    return expr;
}

unique_ptr<Expr> Parser::primary() {

    if(match({TokenType::NUMBER})) {
        return make_unique<Literal>(previous().lex); // make_unique is the another form of unique_ptr
    }

    if(match({TokenType::LEFT_PAREN})) {
        unique_ptr<Expr> expr = expression();
        consume(TokenType::RIGHT_PAREN,"Expected ')' after expression.");
        return make_unique<Grouping>(move(expr));
    }

    throw runtime_error("Expected Expression, found " + peek().lex);
}

// ---- Helpers ----

bool Parser::isAtEnd() {
    return peek().type == TokenType::END_OF_FILE;
}

Token Parser::advance() {
    if(!isAtEnd()) current_++;
    return previous();
}

Token Parser::peek() {
    return tokens_[current_];
}

Token Parser::previous() {
    return tokens_[current_-1];
}

Token Parser::consume(TokenType type, string msg) {
    if(check(type)) return advance();
    throw runtime_error(msg);
}

bool Parser::check(TokenType type) {
    if(isAtEnd()) return false;
    return peek().type == type;
}

bool Parser::match(vector<TokenType> types) {
    for (TokenType type : types) {
        if(check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

