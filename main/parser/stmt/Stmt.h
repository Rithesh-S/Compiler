#pragma once

#include <memory>
#include <vector>
#include <any>
#include "../expr/Expr.h"
#include "../../token/type/Token.h"

class ExpressionStmt;
class VarStmt;

class StmtVisitor {
public:
    virtual ~StmtVisitor() = default;
    virtual std::any visitExpressionStmt(ExpressionStmt& stmt) = 0;
    virtual std::any visitVarStmt(VarStmt& stmt) = 0;
};

class Stmt {
public:
    virtual ~Stmt() = default;
    virtual std::any accept(StmtVisitor& stmt) = 0;
};

class ExpressionStmt : public Stmt {
public:
    std::unique_ptr<Expr> expression;

    ExpressionStmt(std::unique_ptr<Expr> expression)  
        : expression(std::move(expression)) {}

    std::any accept(StmtVisitor& visitor) {
        return visitor.visitExpressionStmt(*this);
    }
};

class VarStmt : public Stmt {
public:
    Token name;
    std::unique_ptr<Expr> initializer;

    VarStmt(Token name, std::unique_ptr<Expr> initializer)
        : name(std::move(name)), initializer(std::move(initializer)) {}

    std::any accept(StmtVisitor& visitor) {
        return visitor.visitVarStmt(*this);
    }
};
