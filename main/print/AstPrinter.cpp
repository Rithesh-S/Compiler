#include "AstPrinter.h"
#include <vector>
#include <string>

using namespace std;

string AstPrinter::print(unique_ptr<Expr>& expr) {
    return any_cast<string>(expr -> accept(*this));
}

any AstPrinter::visitLiteralExpr(Literal& expr) {
    return expr.value;
}

any AstPrinter::visitGroupingExpr(Grouping& expr) {
    vector<Expr*> exprs = { expr.expression.get() };
    const string str = "group";
    return parenthesize(str, exprs);
}

any AstPrinter::visitBinaryExpr(Binary& expr) {
    vector<Expr*> exprs = { expr.left.get(), expr.right.get() };
    return parenthesize(expr.op.lex, exprs);
}

string AstPrinter::parenthesize(const string& name,const vector<Expr*>& exprs) {
    string builder;
    builder += "(";
    builder += name;

    for(Expr* expr: exprs) {
        builder += " ";
        builder += any_cast<string>(expr -> accept(*this));
    }

    builder += ")";
    return builder;
}