#pragma once

#include <memory>
#include <string>
#include <any>
#include "../parser/expr/Expr.h"

class Interpreter : public ExprVisitor {
public:
    double interpret(std::unique_ptr<Expr>& expr);

    std::any visitLiteralExpr(Literal& expr) override;
    std::any visitGroupingExpr(Grouping& expr) override;
    std::any visitBinaryExpr(Binary& expr) override;

private:
    double evaluate(Expr* expr);

};