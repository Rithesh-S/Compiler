#pragma once

#include <vector>
#include <string>
#include <memory>
#include <any>
#include "../../token/type/Token.h"

// Forward Declaration: pre defining the use of class before the definition of the class is declared.
class Binary;
class Grouping;
class Literal;

/* The virtual keyword is primarily used on member functions to enable runtime polymorphism 
(dynamic binding) within a class hierarchy. This ensures that the correct function 
implementation is called based on the actual object's type, rather than the type of the 
pointer or reference used to access it */

/* 'virtual any visitedBinaryExpr(Binary& expr) = 0;' Represents that function is pure 
virtual function expecting the derieved class to write the definition */

// Visitors Implementation: 
class ExprVisitor {
public:
    virtual ~ExprVisitor() = default;
    virtual std::any visitedBinaryExpr(Binary& expr) = 0; 
    virtual std::any visitedGroupingExpr(Grouping& expr) = 0;
    virtual std::any visitedLiteralExpr(Literal& expr) = 0;
};

// Base Class
class Expr {
public:
    virtual ~Expr() = default;
    virtual std::any accept(ExprVisitor& visitor) = 0;
};

/* the accept function is overridden form the Expr class and the object of the class ExprVisitor
is used to invoke the respective function which is passed by the current reference of the Literal 
class, containing the datas of this class */

// Holds the literals of the tokens (i.e.) 123 , "hello" , it has no leaf
class Literal : public Expr {
public:
    const std::string value;
    Literal(std::string val) : value(move(val)) {}
    std::any accept(ExprVisitor& visitor) override {     //double dispatch
        return visitor.visitedLiteralExpr(*this);
    }
};

/* unique_ptr is the special type used to smartly allocate the memory and release them, 
preventing memory leak */

// Holds the operators and have two leaves
class Binary : public Expr {
public:
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

    Binary(std::unique_ptr<Expr> left, Token token, std::unique_ptr<Expr> right) :
        left(move(left)), op(move(token)), right(move(right)) {}

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitedBinaryExpr(*this);
    }
};

// Points to the single expression inside the parantheses, has no leaf
class Grouping : public Expr {
public:
    std::unique_ptr<Expr> expression;

    Grouping(std::unique_ptr<Expr> expression) : 
        expression(move(expression)) {}

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitedGroupingExpr(*this);
    }
};