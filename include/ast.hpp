#pragma once

#include<string>
#include<memory>

enum class TokenType {
    INT, PLUS, MINUS, MUL, DIV, 
    LPAREN, RPAREN, END
};

struct Token {
    TokenType type;
    std::string value;
};

struct ASTNode {
    virtual ~ASTNode() = default;
};

struct NumNode : ASTNode {
    int value;
    NumNode(int val) : value(val) {}
};

struct BinOpNode : ASTNode {
    std::shared_ptr<ASTNode> left;
    Token op;
    std::shared_ptr<ASTNode> right;

    BinOpNode(std::shared_ptr<ASTNode> l, Token o, std::shared_ptr<ASTNode> r) 
        : left(std::move(l)), op(std::move(o)), right(std::move(r)) {}
};