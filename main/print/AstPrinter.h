#pragma once

#include <string>
#include <memory>
#include "../parser/expr/Expr.h"
#include <any>

class AstPrinter : public ExprVisitor {
public:
    std::string print(std::unique_ptr<Expr>& expr);

    std::any visitBinaryExpr(Binary& expr) override;
    std::any visitGroupingExpr(Grouping& expr) override;
    std::any visitLiteralExpr(Literal& expr) override;

private:
    std::string parenthesize(const std::string& name, const std::vector<Expr*>& exprs);

};