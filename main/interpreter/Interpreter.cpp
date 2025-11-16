#include <stdexcept>
#include <string>
#include <iostream>
#include "Interpreter.h"

using namespace std;

double Interpreter::interpret(unique_ptr<Expr>& expr) {
    try {
        return evaluate(expr.get());
    } catch( runtime_error e) {
        cerr << "Runtime Error: "<<e.what()<<endl;
        return 0;
    }
}

double Interpreter::evaluate(Expr* expr) {
    return any_cast<double>(expr -> accept(*this));
}

any Interpreter::visitLiteralExpr(Literal& expr) {
    return stod(expr.value);
}

any Interpreter::visitGroupingExpr(Grouping& expr) {
    return evaluate(expr.expression.get());
}

any Interpreter::visitBinaryExpr(Binary& expr) {
    double right = evaluate(expr.right.get());
    double left = evaluate(expr.left.get());

    switch(expr.op.type) {
        case TokenType::PLUS:
            return left + right;
        case TokenType::MINUS:
            return left - right;
        case TokenType::ASTERISK:
            return left * right;
        case TokenType::SLASH:
            if(right == 0) throw runtime_error("Can't Divide by zero.");
            return left / right;
        default: 
            throw runtime_error("Unexpected operator.");
    }
}