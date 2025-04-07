#include "lexer.hpp"
#include "parser.hpp"
#include "evaluator.hpp"
#include "debug.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char*argv[]) {
    // ensure that there are more than 2 arguments
    if (argc < 2) {
        std::cerr << "Usage: ./compiler <filename>" << std::endl;
        return 1;
    }

    // get filename and open the file
    const std::string filename = argv[1];
    std::ifstream file(filename);

    // check if the file was opened
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return 1;
    }

    // open a string buffer, stream the file into the buffer, and turn the buffer into a string
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string input = buffer.str();

    try {
        // turn the input into a token vector
        auto tokens = tokenize(input);
        // parse the token vector into a list of statements
        auto statements = parse(tokens);

        // create the environment
        std::unordered_map<std::string, int> env;

        // execute the statements
        int last = 0;
        for (auto& stmt : statements) {
            last = evaluate(stmt, env);
        }

        // print the latest result
        std::cout << last;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}