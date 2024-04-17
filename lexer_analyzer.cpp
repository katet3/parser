#include "lexer_analyzer.h"


std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (!isAtEnd()) {
        start_ = currentPos_;
        tokenizeNext(tokens);
    }
    return tokens;
}

bool Lexer::isAtEnd() {
    return currentPos_ >= source_.length();
}

void Lexer::tokenizeNext(std::vector<Token>& tokens) {
    char c = advance();
    switch (c) 
    {
        case '#':
            addToken(tokens, TokenType::COMMENT);
            while (peek() != '\n' && !isAtEnd()) advance();
            break;
        case '(': addToken(tokens, TokenType::BRACKET_L); break;
        case ')': addToken(tokens, TokenType::BRACKET_R); break;
        case '{': addToken(tokens, TokenType::CURLY_BRACKET_L); break;
        case '}': addToken(tokens, TokenType::CURLY_BRACKET_L); break;
        case '[': addToken(tokens, TokenType::SQUARE_BRACKET_L); break;
        case ']': addToken(tokens, TokenType::SQUARE_BRACKET_L); break;
        case '+': addToken(tokens, TokenType::ADD); break;
        case '-': addToken(tokens, TokenType::SUB); break;
        case '*': addToken(tokens, TokenType::MUL); break;
        case '/': addToken(tokens, TokenType::DIV); break;
        case '%': addToken(tokens, TokenType::MOD); break;
        case ' ': addToken(tokens, TokenType::SPACE); break;
        case '\n': addToken(tokens, TokenType::NEW_LINE); break;

        case '=': 
            if (next_peek() == '=')
            {
                addToken(tokens, TokenType::EQUAL); 
                advance();
            }
            else
                addToken(tokens, TokenType::ASSIGNMENT);
            break;
       
        case '<':
            if (next_peek() == '=')
            {
                addToken(tokens, TokenType::IS_LESS_OR_EQ);
                advance();
            }
            else
                addToken(tokens, TokenType::IS_LESS);
            break;
       
        case '>':
            if (next_peek() == '=')
            {
                addToken(tokens, TokenType::IS_GREATER_OR_EQ);
                advance();
            }
            else
                addToken(tokens, TokenType::IS_GREATER);
            break;
    }


    if (is_alpha(c)) {
        std::string text = "";
        text.push_back(c);

        // Начинаем с буквы, так что это или ключевое слово, или идентификатор.
        while (is_numeric(peek()) || is_alpha(peek()))
        {
            text.push_back(peek());
            advance();
        }
        TokenType type = is_keyword(text) ? keyword_type(text) : TokenType::WORDS;
        addToken(tokens, type);
    }
    else if (isdigit(c)) {
        while (isdigit(peek())) advance();
        addToken(tokens, TokenType::DIGIT);
    }

}

char Lexer::advance() {
    return source_[currentPos_++];
}

void Lexer::addToken(std::vector<Token>& tokens, TokenType type) {
    std::string text = source_.substr(start_, currentPos_ - start_);
    tokens.push_back(Token(type, text));
}

bool Lexer::match(char expected) {
    if (isAtEnd()) return false;
    if (source_[currentPos_] != expected) return false;

    currentPos_++;
    return true;
}

char Lexer::peek() {
    if (isAtEnd()) return '\0';
    return source_[currentPos_];
}

char Lexer::next_peek() {
    if (isAtEnd()) return '\0';
    return source_[currentPos_+1];
}

bool Lexer::is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Lexer::is_numeric(char c) {
    return (c >= '0' && c <= '9');
}

bool Lexer::is_keyword(const std::string& word) {
    return keywords.find(word) != keywords.end();
}

TokenType Lexer::keyword_type(const std::string& word)
{
    return keywords[word];
}