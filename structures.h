#pragma once
#include <stdint.h>
#include <iostream>
#include <unordered_map>

typedef unsigned char u8;
typedef uint16_t	  u16;
typedef uint32_t      u32;
typedef uint64_t      u64;

enum class TokenType {
    INT, // int
    WHILE, // while
    IF, // if
    ELSE, // else
    ENDL, // endl
    PRINT, // print 
    INPUT, // input
    END, // end
    BEGIN, // begin
    ASSIGNMENT, // =
    ADD, // +
    SUB, // -
    DIV, // /
    MOD, // %
    MUL, // *
    EQUAL, // ==
    IS_LESS, // <
    IS_GREATER, // >
    IS_LESS_OR_EQ, // <=
    IS_GREATER_OR_EQ, // >=
    BRACKET_L, // (
    BRACKET_R, // )
    CURLY_BRACKET_L, // {
    CURLY_BRACKET_R, // }
    SQUARE_BRACKET_L, // [
    SQUARE_BRACKET_R, // ]
    END_TERM, // ;
    SPACE, // ' '
    COMMENT, // #
    NEW_LINE, // /n
    WORDS, // <w>
    DIGIT, // <d>
    CHAR // <s>
};
const std::unordered_map<TokenType, std::string> g_token_type_map = {
    {TokenType::INT, "int"},
    {TokenType::WHILE, "while"},
    {TokenType::IF, "if"},
    {TokenType::ELSE, "else"},
    {TokenType::ENDL, "endl"},
    {TokenType::PRINT, "print"},
    {TokenType::INPUT, "input"},
    {TokenType::END, "end"},
    {TokenType::BEGIN, "begin"},
    {TokenType::ASSIGNMENT, "="},
    {TokenType::ADD, "+"},
    {TokenType::SUB, "-"},
    {TokenType::DIV, "/"},
    {TokenType::MOD, "%"},
    {TokenType::MUL, "*"},
    {TokenType::EQUAL, "=="},
    {TokenType::IS_LESS, "<"},
    {TokenType::IS_GREATER, ">"},
    {TokenType::IS_LESS_OR_EQ, "<="},
    {TokenType::IS_GREATER_OR_EQ, ">="},
    {TokenType::BRACKET_L, "("},
    {TokenType::BRACKET_R, ")"},
    {TokenType::CURLY_BRACKET_L, "{"},
    {TokenType::CURLY_BRACKET_R, "}"},
    {TokenType::SQUARE_BRACKET_L, "["},
    {TokenType::SQUARE_BRACKET_R, "]"},
    {TokenType::END_TERM, ";"},
    {TokenType::SPACE, " "},
    {TokenType::COMMENT, "#"},
    {TokenType::NEW_LINE, "/n"},
    {TokenType::WORDS, "<w>"},
    {TokenType::DIGIT, "<d>"},
    {TokenType::CHAR, "<c>"}
};



struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};