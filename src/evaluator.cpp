#include "evaluator.hpp"
#include <stdexcept>

// given an ast, evaluate it and return it's value
int evaluate(std::shared_ptr<ASTNode> node, std::unordered_map<std::string, int>& env) {
    // num node
    if (auto num = dynamic_cast<NumNode*>(node.get())) {
        // dynamic cast is an attempt to cast the base class object into a specific derived class
        // if the cast fails (it is not the derived class), then we get null/false
        // here, we check if the ASTNode node is an instance of the derived class, NumNode
        return num->value;

        // note that dynamic cast expects a raw pointer, and returns that raw pointer (if the type checks out)
    }

    // unary op node
    if (auto unop = dynamic_cast<UnaryOpNode*>(node.get())) {
        // evaluate the operand to some integer
        int val = evaluate(unop->operand, env);
        // apply the sign
        switch(unop->op.type) {
            case TokenType::MINUS:
                return -val;
            case TokenType::PLUS:
                return val;
            default:
                throw std::runtime_error("Unknown unary operator");
        }
    }

    // bin op node
    if (auto binop = dynamic_cast<BinOpNode*>(node.get())) {
        // evaluate the left node
        int left = evaluate(binop->left, env);
        // evaluate the right node
        int right = evaluate(binop->right, env);

        // combine the two depending on the operation, take care of errors as well
        switch(binop->op.type) {
            case TokenType::PLUS:
                return left + right;
            case TokenType::MINUS:
                return left - right;
            case TokenType::MUL:
                return left * right;
            case TokenType::DIV:
                if (right == 0) {
                    throw std::runtime_error("Division by zero");
                }
                return left / right;
            default:
                throw std::runtime_error("Unknown binary operator");
        }
    }

    // variable assignment
    if (auto assign = dynamic_cast<AssignmentNode*>(node.get())) {
        // evaluate the value of this variable
        int val = evaluate(assign->value, env);
        // add its value to the environment lookup table
        env[assign->name] = val;
        return val;
    }

    if (auto access = dynamic_cast<AccessNode*>(node.get())) {
        // check if the variable is in the map
        if (env.find(access->name) == env.end()) {
            throw std::runtime_error("Undefined variable: " + access->name);
        }
        return env[access->name];
    }

    throw std::runtime_error("Unknown AST node type");

}