#include "lexer.h"
//===----------------------------------------------------------------------===//
// Lexer
//===----------------------------------------------------------------------===//

static int gettok() {
    static int LastChar = ' ';

    while (isspace(LastChar))
        LastChar = InputStream->get();

    if (LastChar == '#') {
        // Comment until end of line.
        do {
            LastChar = InputStream->get();
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
            return gettok();
    }

    if (isalpha(LastChar)) {
        IdentifierStr = LastChar;
        while (isalnum((LastChar = InputStream->get())) || LastChar == '_')
            IdentifierStr += LastChar;

        if (IdentifierStr == "int") return tok_int;
        if (IdentifierStr == "double") return tok_double;
        if (IdentifierStr == "bool") return tok_bool;
        if (IdentifierStr == "if") return tok_if;
        if (IdentifierStr == "else") return tok_else;
        if (IdentifierStr == "true") {
            BoolVal = true;
            return tok_true;
        }
        if (IdentifierStr == "false") {
            BoolVal = false;
            return tok_false;
        }
        if (IdentifierStr == "while") return tok_while;
        if (IdentifierStr == "print") return tok_print;
        if (IdentifierStr == "endl") return tok_endl;
        if (IdentifierStr == "input") return tok_input;
        return tok_identifier;
    }

    if (isdigit(LastChar) || LastChar == '.') {
        std::string NumStr;
        do {
            NumStr += LastChar;
            LastChar = InputStream->get();
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), nullptr);
        return tok_number;
    }

    if (LastChar == '\"') {
        LastChar = InputStream->get();
        while (LastChar != '\"' && LastChar != EOF) {
            StringVal += LastChar;
            LastChar = InputStream->get();
        }
        LastChar = InputStream->get(); // Skip the closing quote
        return tok_string;
    }

    if (LastChar == EOF)
        return tok_eof;

    if (LastChar == ';') {
        LastChar = InputStream->get();
        return tok_semi;
    }

    if (LastChar == '{') {
        LastChar = InputStream->get();
        return tok_lbrace;
    }

    if (LastChar == '}') {
        LastChar = InputStream->get();
        return tok_rbrace;
    }

    if (LastChar == '[') {
        LastChar = InputStream->get();
        return tok_lsquare;
    }

    if (LastChar == ']') {
        LastChar = InputStream->get();
        return tok_rsquare;
    }

    if (LastChar == ',') {
        LastChar = InputStream->get();
        return tok_comma;
    }

    if (LastChar == '=') {
        LastChar = InputStream->get();
        if (LastChar == '=') {
            LastChar = InputStream->get();
            return tok_eq;
        }
        return tok_assign;
    }

    if (LastChar == '!') {
        LastChar = InputStream->get();
        if (LastChar == '=') {
            LastChar = InputStream->get();
            return tok_ne;
        }
    }

    if (LastChar == '<') {
        LastChar = InputStream->get();
        if (LastChar == '=') {
            LastChar = InputStream->get();
            return tok_le;
        }
        return tok_lt;
    }

    if (LastChar == '>') {
        LastChar = InputStream->get();
        if (LastChar == '=') {
            LastChar = InputStream->get();
            return tok_ge;
        }
        return tok_gt;
    }

    if (LastChar == '&') {
        LastChar = InputStream->get();
        if (LastChar == '&') {
            LastChar = InputStream->get();
            return tok_and;
        }
    }

    if (LastChar == '|') {
        LastChar = InputStream->get();
        if (LastChar == '|') {
            LastChar = InputStream->get();
            return tok_or;
        }
    }

    int ThisChar = LastChar;
    LastChar = InputStream->get();
    return ThisChar;
}