#pragma once
#include "ast.hpp"
#include <unordered_map>

int evaluate(std::shared_ptr<ASTNode> node, std::unordered_map<std::string, int>& env);