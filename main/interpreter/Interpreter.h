#pragma once

#include <memory>
#include <string>
#include <any>
#include "../parser/expr/Expr.h"

class Interpreter : public ExprVisitor {
public:
    double interpret(std::unique_ptr<Expr>& expr);

    std::any visitedLiteralExpr(Literal& expr) override;
    std::any visitedGroupingExpr(Grouping& expr) override;
    std::any visitedBinaryExpr(Binary& expr) override;

private:
    double evaluate(Expr* expr);

};