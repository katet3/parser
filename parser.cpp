#include <iostream>
#include "lexer_analyzer.h"
#include "syntax_analyzer.h"
#include "structures.h"



std::string token_type_to_str(TokenType type) {
    auto it = g_token_type_map.find(type);
    if (it != g_token_type_map.end()) {
        return it->second;
    }
    return "Unknown TokenType";
}


void print_tokens(std::vector<Token> tokens)
{
    // Проходим по вектору токенов и выводим их на экран
    for (Token& token : tokens) {
        std::cout << "Type: " << static_cast<int>(token.type) << " type: " << token_type_to_str(token.type) << " value: " << token.value << std::endl;
    }
}

using std::cout;
using std::cin;
using std::endl;

int main()
{
    cout << "Hello pidr!\n";
    std::string in_file = "PATH_TO_FILE";
    std::string result_file = "PATH_OUT_FILE";
    
    /* Лексаторчик */
    Lexer a("a>3");
    std::vector<Token> tokens = a.tokenize();

    print_tokens(tokens);

}
