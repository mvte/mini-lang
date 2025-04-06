#pragma once

#include "ast.hpp"
#include <iostream>
#include <string>

const int INDENT_SIZE = 2;

inline std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::INT:    return "INT";
        case TokenType::PLUS:   return "PLUS";
        case TokenType::MINUS:  return "MINUS";
        case TokenType::MUL:    return "MUL";
        case TokenType::DIV:    return "DIV";
        case TokenType::LPAREN: return "LPAREN";
        case TokenType::RPAREN: return "RPAREN";
        case TokenType::END:    return "END";
        default:                return "UNKNOWN";
    }
}

inline std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "[" << tokenTypeToString(token.type) << ": \"" << token.value << "\"]";
    return os;
}

inline void printAST(const std::shared_ptr<ASTNode>& node, int indent = 0) {
    std::string pad(indent, ' ');

    if (auto num = dynamic_cast<NumNode*>(node.get())) {
        // print a number as is
        std::cout << pad << "NumNode(" << num->value << ")" << "\n";
    } else if (auto bin = dynamic_cast<BinOpNode*>(node.get())) {
        // print the binary operation
        std::cout << pad << "BinOpNode(" << tokenTypeToString(bin->op.type) << ")" << "\n";
        // print the left and right nodes, but indented
        printAST(bin->left, indent + INDENT_SIZE);
        printAST(bin->right, indent + INDENT_SIZE);
    } else {
        std::cout << pad << "Unknown AST Node" << "\n";
    }
}