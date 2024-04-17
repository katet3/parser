#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "structures.h"

class Lexer {
private:
    std::string source_;
    size_t currentPos_;
    size_t start_;

public:
    Lexer(const std::string& source) : source_(source), currentPos_(0) {}

    std::vector<Token> tokenize();

private:
    void tokenizeNext(std::vector<Token>& tokens);
    void addToken(std::vector<Token>& tokens, TokenType type);
    char advance();
    bool match(char expected);
    char peek();
    char next_peek();

    bool isAtEnd();
    bool is_alpha(char c);
    bool is_numeric(char c);
    bool is_keyword(const std::string& word);
    TokenType keyword_type(const std::string& word);

    std::unordered_map<std::string, TokenType> keywords = {
        {"int", TokenType::INT},
        {"while", TokenType::WHILE},
        {"if", TokenType::IF},
        {"else", TokenType::ELSE},
        {"endl", TokenType::ENDL},
        {"print", TokenType::PRINT},
        {"input", TokenType::INPUT},
        {"end", TokenType::END},
        {"begin", TokenType::BEGIN}
    };
};
