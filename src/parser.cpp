#include "parser.hpp"

static size_t current;
static std::vector<Token> tkns;

std::shared_ptr<ASTNode> term();
std::shared_ptr<ASTNode> factor();
std::shared_ptr<ASTNode> expression();

// returns the current token
Token peek() {
    return tkns[current];
}

// returns the current token and advance the pointer
Token advance() {
    return tkns[current++];
}

// matches the current token to the given type, and advances on success
bool match(TokenType type) {
    if (peek().type == type) {
        advance();
        return true;
    }

    return false;
}

// parses expressions (terms bound together by addition or subtraction)
std::shared_ptr<ASTNode> expression() {
    // parse the left term
    auto left = term();
    while (peek().type == TokenType::PLUS || peek().type == TokenType::MINUS) {
        // consume the current token
        Token op = advance();
        // parse the right term 
        auto right = term();
        // construct the binary operation node (if more add/sub tokens, this acts as the new left node)
        left = std::make_shared<BinOpNode>(left, op, right);
    }

    return left;
}

// parses factors (integers and expressions inside parentheses)
std::shared_ptr<ASTNode> factor() {
    Token tkn = peek();
    if (tkn.type == TokenType::INT) {
        // consume the token and create a number node
        advance();
        return std::make_shared<NumNode>(std::stoi(tkn.value));
    } else if (tkn.type == TokenType::LPAREN) {
        // consume the token, and parse the tokens afterwards as an expression
        advance();
        auto node = expression();
        // the following token must be a right parentheses now
        if (!match(TokenType::RPAREN)) throw std::runtime_error("Expected ')'");
        return node;
    } else {
        throw std::runtime_error("Expected number or '('");
    }
}

// parses terms (factors bound together by multiplication or division)
std::shared_ptr<ASTNode> term() {
    // parse the left factor
    auto left = factor();
    while (peek().type == TokenType::MUL || peek().type == TokenType::DIV) {
        // consume the current token
        Token op = advance();
        // parse the right factor 
        auto right = factor();
        // construct the binary operation node (if more mul/div tokens, this acts as the new left node)
        left = std::make_shared<BinOpNode>(left, op, right);
    }

    return left;
}

std::shared_ptr<ASTNode> parse (const std::vector<Token>& tokens) {
    tkns = tokens;
    current = 0;
    return expression();
}