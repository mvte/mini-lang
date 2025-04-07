#pragma once

#include<string>
#include<memory>

enum class TokenType {
    INT, 
    PLUS, 
    MINUS, 
    MUL, 
    DIV, 
    LPAREN, 
    RPAREN, 
    END,
    ASSIGN,
    IDENTIFIER,
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

struct UnaryOpNode : ASTNode {
    Token op;
    std::shared_ptr<ASTNode> operand;

    UnaryOpNode(Token o, std::shared_ptr<ASTNode> n) 
        : op(std::move(o)), operand(std::move(n)) {}
};

struct AssignmentNode : ASTNode {
    std::string name;
    std::shared_ptr<ASTNode> value;
    
    AssignmentNode(std::string n, std::shared_ptr<ASTNode> v)
        : name(std::move(n)), value(std::move(v)) {}
};

struct AccessNode : ASTNode {
    std::string name;

    AccessNode(std::string n)
        : name(std::move(n)) {}
};