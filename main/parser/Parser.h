#pragma once

#include <vector>
#include <memory>
#include "expr/Expr.h"
#include "stmt/Stmt.h"
#include "../token/type/Token.h"
#include "../token/type/TokenType.h"

// abstract class of the parser class
class Parser {
public:
    Parser(std::vector<Token> tokens);
    std::vector<std::unique_ptr<Stmt>> parse();

private:
    std::vector<Token> tokens_;
    int current_ = 0;

    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> term();
    std::unique_ptr<Expr> factor();
    std::unique_ptr<Expr> primary();

    std::unique_ptr<Stmt> declaration();
    std::unique_ptr<Stmt> varDeclaration();
    std::unique_ptr<Stmt> statement();
    std::unique_ptr<Stmt> expressionStatment();

    bool isAtEnd();
    Token advance();
    Token peek();
    Token previous();
    Token consume(TokenType type, std::string msg);
    bool match(std::vector<TokenType> types);
    bool check(TokenType token);

};