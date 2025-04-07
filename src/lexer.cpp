#include "lexer.hpp"
#include <cctype>
#include <stdexcept>

std::vector<Token> tokenize(const std::string &input) {
    // create a token and vector and an indexing variable for the input
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < input.size()) {
        char ch = input[i];

        // skip over white space
        if (std::isspace(ch)) {
            i++;
            continue;
        }

        // beginning of a num literal
        if (std::isdigit(ch)) {
            std::string num;
            while (i < input.size() && std::isdigit(input[i])) {
                num += input[i++];
            }
            tokens.push_back({TokenType::INT, num});
            continue;
        }

        // beginning of an variable name (must start with letters only!)
        if (std::isalpha(ch)) {
            std::string ident;
            while (i < input.size() && std::isalnum(input[i])) {
                ident += input[i++];
            }
            tokens.push_back({TokenType::IDENTIFIER, ident});
            continue;
        }

        // tokenize other single character token types
        switch (ch) {
            case '+':
                tokens.push_back({TokenType::PLUS, "+"});
                break;
            case '-':
                tokens.push_back({TokenType::MINUS, "-"});
                break;
            case '*':
                tokens.push_back({TokenType::MUL, "*"});
                break;
            case '/':
                tokens.push_back({TokenType::DIV, "/"});
                break;
            case '(':
                tokens.push_back({TokenType::LPAREN, "("});
                break;
            case ')':
                tokens.push_back({TokenType::RPAREN, ")"});
                break;
            case '=':
                tokens.push_back({TokenType::ASSIGN, "="});
                break;
            default:
                throw std::runtime_error("Unknown character: " + std::string(1, ch));
        }
        
        i++;
    }
    
    tokens.push_back({TokenType::END, ""});
    return tokens;
}