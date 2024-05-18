#pragma once
#include <iostream>
#include <string>
//===----------------------------------------------------------------------===//
// Lexer
//===----------------------------------------------------------------------===//

enum Token {
    tok_eof = -1,
    tok_number = -2,
    tok_identifier = -3,
    tok_int = -4,
    tok_double = -5,
    tok_bool = -6,
    tok_true = -7,
    tok_false = -8,
    tok_plus = '+',
    tok_minus = '-',
    tok_multiply = '*',
    tok_divide = '/',
    tok_lparen = '(',
    tok_rparen = ')',
    tok_semi = ';',
    tok_eq = -9,
    tok_ne = -10,
    tok_lt = -11,
    tok_le = -12,
    tok_gt = -13,
    tok_ge = -14,
    tok_and = -15,
    tok_or = -16,
    tok_if = -17,
    tok_else = -18,
    tok_assign = '=',
    tok_while = -19,
    tok_print = -20,
    tok_endl = -21,
    tok_string = -22,
    tok_lbrace = '{',
    tok_rbrace = '}',
    tok_lsquare = '[',
    tok_rsquare = ']',
    tok_comma = ',',
    tok_input = -23,
    tok_comment = -24
};

std::string IdentifierStr;
double NumVal;
std::string StringVal;
bool BoolVal;
std::istream* InputStream = &std::cin;

static int gettok();