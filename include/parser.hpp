#pragma once
#include "ast.hpp"
#include <vector>
#include <memory>

std::shared_ptr<ASTNode> parse(const std::vector<Token>& tokens);