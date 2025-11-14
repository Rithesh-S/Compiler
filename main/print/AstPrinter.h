#pragma once

#include <string>
#include <memory>
#include "../parser/expr/Expr.h"
#include <any>

class AstPrinter : public ExprVisitor {
public:
    std::string print(std::unique_ptr<Expr>& expr);

    std::any visitedBinaryExpr(Binary& expr) override;
    std::any visitedGroupingExpr(Grouping& expr) override;
    std::any visitedLiteralExpr(Literal& expr) override;

private:
    std::string parenthesize(const std::string& name, const std::vector<Expr*>& exprs);

};