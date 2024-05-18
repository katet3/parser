#include <iostream>
#include <fstream>
#include <memory>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>

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

static std::string IdentifierStr;
static double NumVal;
static std::string StringVal;
static bool BoolVal;
static std::istream* InputStream = &std::cin;
static int CurrentLine = 1;

static int gettok() {
    static int LastChar = ' ';

    while (isspace(LastChar)) {
        if (LastChar == '\n') {
            ++CurrentLine;
        }
        LastChar = InputStream->get();
    }

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

//===----------------------------------------------------------------------===//
// Abstract Syntax Tree (AST)
//===----------------------------------------------------------------------===//

enum class VarType { INT, DOUBLE, BOOL, STRING, ARRAY };

struct Variable {
    VarType Type;
    double Value;
    std::string StrValue;
    std::vector<double> ArrayValues;
};

static std::map<std::string, Variable> NamedValues;

class ExprAST {
public:
    virtual ~ExprAST() = default;
    virtual double evaluate() const = 0;
};

class NumberExprAST : public ExprAST {
    double Val;

public:
    NumberExprAST(double val) : Val(val) {}
    double evaluate() const override {
        return Val;
    }
};

class BooleanExprAST : public ExprAST {
    bool Val;

public:
    BooleanExprAST(bool val) : Val(val) {}
    double evaluate() const override {
        return Val ? 1.0 : 0.0;
    }
};

class StringExprAST : public ExprAST {
    std::string Val;

public:
    StringExprAST(const std::string& val) : Val(val) {}
    double evaluate() const override {
        std::cout << Val;
        return 0.0;
    }
};

class VariableExprAST : public ExprAST {
    std::string Name;

public:
    VariableExprAST(const std::string& name) : Name(name) {}
    double evaluate() const override;
};

class ArrayExprAST : public ExprAST {
    std::string Name;
    std::unique_ptr<ExprAST> Index;

public:
    ArrayExprAST(const std::string& name, std::unique_ptr<ExprAST> index)
        : Name(name), Index(std::move(index)) {}
    double evaluate() const override;
};

class BinaryExprAST : public ExprAST {
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS;

public:
    BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs, std::unique_ptr<ExprAST> rhs)
        : Op(op), LHS(std::move(lhs)), RHS(std::move(rhs)) {}

    double evaluate() const override {
        double LeftVal = LHS->evaluate();
        double RightVal = RHS->evaluate();

        switch (Op) {
        case '+': return LeftVal + RightVal;
        case '-': return LeftVal - RightVal;
        case '*': return LeftVal * RightVal;
        case '/': return LeftVal / RightVal;
        case tok_eq: return LeftVal == RightVal;
        case tok_ne: return LeftVal != RightVal;
        case tok_lt: return LeftVal < RightVal;
        case tok_le: return LeftVal <= RightVal;
        case tok_gt: return LeftVal > RightVal;
        case tok_ge: return LeftVal >= RightVal;
        case tok_and: return LeftVal && RightVal;
        case tok_or: return LeftVal || RightVal;
        default: return 0;
        }
    }
};

class IfExprAST : public ExprAST {
    std::unique_ptr<ExprAST> Cond, Then, Else;

public:
    IfExprAST(std::unique_ptr<ExprAST> cond, std::unique_ptr<ExprAST> thenExpr, std::unique_ptr<ExprAST> elseExpr)
        : Cond(std::move(cond)), Then(std::move(thenExpr)), Else(std::move(elseExpr)) {}

    double evaluate() const override {
        if (Cond->evaluate()) {
            return Then->evaluate();
        }
        else if (Else) {
            return Else->evaluate();
        }
        return 0.0;
    }
};

class BlockExprAST : public ExprAST {
    std::vector<std::unique_ptr<ExprAST>> Expressions;

public:
    BlockExprAST(std::vector<std::unique_ptr<ExprAST>> expressions)
        : Expressions(std::move(expressions)) {}

    double evaluate() const override {
        double Result = 0.0;
        for (const auto& Expr : Expressions) {
            Result = Expr->evaluate();
        }
        return Result;
    }
};

class VariableAssignmentExprAST : public ExprAST {
    std::string Name;
    std::unique_ptr<ExprAST> Expr;
    std::unique_ptr<ExprAST> Index; // Added for array support

public:
    VariableAssignmentExprAST(const std::string& name, std::unique_ptr<ExprAST> expr, std::unique_ptr<ExprAST> index = nullptr)
        : Name(name), Expr(std::move(expr)), Index(std::move(index)) {}

    double evaluate() const override;
};

class VariableDeclarationExprAST : public ExprAST {
    std::string Name;
    std::unique_ptr<ExprAST> Expr;

public:
    VariableDeclarationExprAST(const std::string& name, std::unique_ptr<ExprAST> expr)
        : Name(name), Expr(std::move(expr)) {}

    double evaluate() const override;
};

class ArrayDeclarationExprAST : public ExprAST {
    std::string Name;
    int Size;

public:
    ArrayDeclarationExprAST(const std::string& name, int size)
        : Name(name), Size(size) {}

    double evaluate() const override;
};

class WhileExprAST : public ExprAST {
    std::unique_ptr<ExprAST> Cond, Body;

public:
    WhileExprAST(std::unique_ptr<ExprAST> cond, std::unique_ptr<ExprAST> body)
        : Cond(std::move(cond)), Body(std::move(body)) {}

    double evaluate() const override {
        double Result = 0.0;
        while (Cond->evaluate()) {
            Result = Body->evaluate();
        }
        return Result;
    }
};

class PrintExprAST : public ExprAST {
    std::unique_ptr<ExprAST> Expr;

public:
    PrintExprAST(std::unique_ptr<ExprAST> expr)
        : Expr(std::move(expr)) {}

    double evaluate() const override {
        double Result = Expr->evaluate();
        std::cout << Result;
        return Result;
    }
};

class EndlExprAST : public ExprAST {
public:
    EndlExprAST() {}
    double evaluate() const override {
        std::cout << std::endl;
        return 0.0;
    }
};

class InputExprAST : public ExprAST {
    std::string Name;

public:
    InputExprAST(const std::string& name) : Name(name) {}
    double evaluate() const override;
};

//===----------------------------------------------------------------------===//
// Variable Evaluation
//===----------------------------------------------------------------------===//

double VariableExprAST::evaluate() const {
    if (NamedValues.find(Name) != NamedValues.end()) {
        if (NamedValues[Name].Type == VarType::STRING) {
            std::cout << NamedValues[Name].StrValue;
            return 0.0;
        }
        return NamedValues[Name].Value;
    }
    std::cerr << "Unknown variable name: " << Name << std::endl;
    exit(1);  // Terminate execution on error
    return 0.0;
}

double ArrayExprAST::evaluate() const {
    if (NamedValues.find(Name) != NamedValues.end()) {
        if (NamedValues[Name].Type == VarType::ARRAY) {
            int index = static_cast<int>(Index->evaluate());
            if (index < 0 || index >= static_cast<int>(NamedValues[Name].ArrayValues.size())) {
                std::cerr << "Array index out of bounds: " << index << std::endl;
                exit(1);  // Terminate execution on error
                return 0.0;
            }
            return NamedValues[Name].ArrayValues[index];
        }
    }
    std::cerr << "Unknown array name: " << Name << std::endl;
    exit(1);  // Terminate execution on error
    return 0.0;
}

double VariableAssignmentExprAST::evaluate() const {
    double Val = Expr->evaluate();
    if (Index) { // Check for index (i.e., it's an array)
        if (NamedValues.find(Name) != NamedValues.end() && NamedValues[Name].Type == VarType::ARRAY) {
            int index = static_cast<int>(Index->evaluate());
            if (index < 0 || index >= static_cast<int>(NamedValues[Name].ArrayValues.size())) {
                std::cerr << "Array index out of bounds: " << index << std::endl;
                exit(1);  // Terminate execution on error
                return 0.0;
            }
            NamedValues[Name].ArrayValues[index] = Val;
        }
        else {
            std::cerr << "Unknown array name: " << Name << std::endl;
            exit(1);  // Terminate execution on error
        }
    }
    else {
        if (NamedValues.find(Name) != NamedValues.end()) {
            NamedValues[Name].Value = Val;
        }
        else {
            std::cerr << "Unknown variable name: " << Name << std::endl;
            exit(1);  // Terminate execution on error
        }
    }
    return Val;
}

double VariableDeclarationExprAST::evaluate() const {
    double Val = Expr->evaluate();
    VarType type = VarType::DOUBLE; // Default to double for now
    if (NamedValues.find(Name) != NamedValues.end()) {
        type = NamedValues[Name].Type;
    } else if (IdentifierStr == "bool") {
        type = VarType::BOOL;
    }
    NamedValues[Name] = { type, Val, "" };
    return Val;
}

double ArrayDeclarationExprAST::evaluate() const {
    NamedValues[Name] = { VarType::ARRAY, 0.0, "", std::vector<double>(Size) };
    return 0.0;
}

double InputExprAST::evaluate() const {
    if (NamedValues.find(Name) != NamedValues.end()) {
        double Val;
        std::cin >> Val;
        NamedValues[Name].Value = Val;
        return Val;
    }
    std::cerr << "Unknown variable name: " << Name << std::endl;
    exit(1);  // Terminate execution on error
    return 0.0;
}

//===----------------------------------------------------------------------===//
// Parser
//===----------------------------------------------------------------------===//

static int CurTok;

static int getNextToken() {
    CurTok = gettok();
    return CurTok;
}

static std::unique_ptr<ExprAST> ParseExpression();

static std::unique_ptr<ExprAST> ParseNumberExpr() {
    auto Result = std::make_unique<NumberExprAST>(NumVal);
    getNextToken();
    return std::move(Result);
}

static std::unique_ptr<ExprAST> ParseBooleanExpr() {
    auto Result = std::make_unique<BooleanExprAST>(BoolVal);
    getNextToken();
    return std::move(Result);
}

static std::unique_ptr<ExprAST> ParseStringExpr() {
    auto Result = std::make_unique<StringExprAST>(StringVal);
    getNextToken();
    return std::move(Result);
}

static std::unique_ptr<ExprAST> ParseParenExpr() {
    getNextToken();
    auto V = ParseExpression();
    if (!V)
        return nullptr;

    if (CurTok != tok_rparen)
        return nullptr;
    getNextToken();
    return V;
}

static std::unique_ptr<ExprAST> ParseIdentifierExpr() {
    std::string IdName = IdentifierStr;

    getNextToken();  // eat identifier

    if (CurTok == tok_lsquare) {
        getNextToken(); // eat '['
        auto Index = ParseExpression();
        if (!Index)
            return nullptr;

        if (CurTok != tok_rsquare) {
            std::cerr << "Expected ']' after index" << std::endl;
            return nullptr;
        }
        getNextToken(); // eat ']'

        if (CurTok == tok_assign) {
            getNextToken(); // eat '='
            auto Expr = ParseExpression();
            if (!Expr)
                return nullptr;
            return std::make_unique<VariableAssignmentExprAST>(IdName, std::move(Expr), std::move(Index));
        }

        return std::make_unique<ArrayExprAST>(IdName, std::move(Index));
    }

    if (CurTok == tok_assign) {
        getNextToken(); // eat '='

        auto Expr = ParseExpression();
        if (!Expr)
            return nullptr;

        return std::make_unique<VariableAssignmentExprAST>(IdName, std::move(Expr));
    }

    return std::make_unique<VariableExprAST>(IdName);
}

static std::unique_ptr<ExprAST> ParseWhileExpr();
static std::unique_ptr<ExprAST> ParsePrintExpr();
static std::unique_ptr<ExprAST> ParseInputExpr();
static std::unique_ptr<ExprAST> ParseIfExpr();
static std::unique_ptr<ExprAST> ParseEndlExpr();

static std::unique_ptr<ExprAST> ParsePrimary() {
    switch (CurTok) {
    default:
        return nullptr;
    case tok_identifier:
        return ParseIdentifierExpr();
    case tok_number:
        return ParseNumberExpr();
    case tok_true:
    case tok_false:
        return ParseBooleanExpr();
    case tok_string:
        return ParseStringExpr();
    case tok_lparen:
        return ParseParenExpr();
    case tok_if:
        return ParseIfExpr();
    case tok_while:
        return ParseWhileExpr();
    case tok_print:
        return ParsePrintExpr();
    case tok_endl:
        return ParseEndlExpr();
    case tok_input:
        return ParseInputExpr();
    }
}

static int GetTokPrecedence() {
    switch (CurTok) {
    case tok_plus:
    case tok_minus:
        return 10;
    case tok_multiply:
    case tok_divide:
        return 20;
    case tok_eq:
    case tok_ne:
        return 5;
    case tok_lt:
    case tok_le:
    case tok_gt:
    case tok_ge:
        return 15;
    case tok_and:
        return 3;
    case tok_or:
        return 1;
    default:
        return -1;
    }
}

static std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS) {
    while (true) {
        int TokPrec = GetTokPrecedence();

        if (TokPrec < ExprPrec)
            return LHS;

        int BinOp = CurTok;
        getNextToken();

        auto RHS = ParsePrimary();
        if (!RHS)
            return nullptr;

        int NextPrec = GetTokPrecedence();
        if (TokPrec < NextPrec) {
            RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
            if (!RHS)
                return nullptr;
        }

        LHS = std::make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
    }
}

static std::unique_ptr<ExprAST> ParseExpression() {
    auto LHS = ParsePrimary();
    if (!LHS)
        return nullptr;

    return ParseBinOpRHS(0, std::move(LHS));
}

static std::unique_ptr<ExprAST> ParseBlock() {
    getNextToken(); // eat '{'
    std::vector<std::unique_ptr<ExprAST>> expressions;

    while (CurTok != tok_rbrace && CurTok != tok_eof) {
        if (CurTok == tok_semi) {
            getNextToken(); // skip ';'
            continue;
        }
        auto Expr = ParseExpression();
        if (!Expr) {
            return nullptr;
        }
        expressions.push_back(std::move(Expr));
        if (CurTok != tok_semi) {
            std::cerr << "Expected ';' at the end of expression" << std::endl;
            return nullptr;
        }
        getNextToken(); // eat ';'
    }

    if (CurTok != tok_rbrace) {
        std::cerr << "Expected '}' at the end of block" << std::endl;
        return nullptr;
    }

    getNextToken(); // eat '}'

    if (expressions.size() == 1) {
        return std::move(expressions[0]);
    }

    return std::make_unique<BlockExprAST>(std::move(expressions));
}

static std::unique_ptr<ExprAST> ParseIfExpr() {
    getNextToken(); // eat 'if'

    if (CurTok != tok_lparen) {
        std::cerr << "Expected '(' after 'if'" << std::endl;
        return nullptr;
    }
    getNextToken(); // eat '('

    auto Cond = ParseExpression();
    if (!Cond) {
        return nullptr;
    }

    if (CurTok != tok_rparen) {
        std::cerr << "Expected ')' after condition" << std::endl;
        return nullptr;
    }
    getNextToken(); // eat ')'

    if (CurTok != tok_lbrace) {
        std::cerr << "Expected '{' after 'if'" << std::endl;
        return nullptr;
    }

    auto Then = ParseBlock();
    if (!Then) {
        return nullptr;
    }

    std::unique_ptr<ExprAST> Else = nullptr;
    if (CurTok == tok_else) {
        getNextToken(); // eat 'else'
        if (CurTok != tok_lbrace) {
            std::cerr << "Expected '{' after 'else'" << std::endl;
            return nullptr;
        }
        Else = ParseBlock();
        if (!Else) {
            return nullptr;
        }
    }

    return std::make_unique<IfExprAST>(std::move(Cond), std::move(Then), std::move(Else));
}

static std::unique_ptr<ExprAST> ParseWhileExpr() {
    getNextToken(); // eat 'while'

    if (CurTok != tok_lparen) {
        std::cerr << "Expected '(' after 'while'" << std::endl;
        return nullptr;
    }
    getNextToken(); // eat '('

    auto Cond = ParseExpression();
    if (!Cond) {
        return nullptr;
    }

    if (CurTok != tok_rparen) {
        std::cerr << "Expected ')' after condition" << std::endl;
        return nullptr;
    }
    getNextToken(); // eat ')'

    if (CurTok != tok_lbrace) {
        std::cerr << "Expected '{' after 'while'" << std::endl;
        return nullptr;
    }

    auto Body = ParseBlock();
    if (!Body) {
        return nullptr;
    }

    return std::make_unique<WhileExprAST>(std::move(Cond), std::move(Body));
}

static std::unique_ptr<ExprAST> ParsePrintExpr() {
    getNextToken(); // eat 'print'

    auto Expr = ParseExpression();
    if (!Expr)
        return nullptr;

    return std::make_unique<PrintExprAST>(std::move(Expr));
}

static std::unique_ptr<ExprAST> ParseEndlExpr() {
    getNextToken(); // eat 'endl'
    return std::make_unique<EndlExprAST>();
}

static std::unique_ptr<ExprAST> ParseInputExpr() {
    getNextToken(); // eat 'input'

    if (CurTok != tok_identifier) {
        std::cerr << "Expected identifier after 'input'" << std::endl;
        return nullptr;
    }

    std::string IdName = IdentifierStr;
    getNextToken(); // eat identifier

    return std::make_unique<InputExprAST>(IdName);
}

static std::unique_ptr<ExprAST> ParseIntDecl() {
    getNextToken(); // eat 'int'

    if (CurTok != tok_identifier) {
        std::cerr << "Expected identifier after 'int'" << std::endl;
        return nullptr;
    }

    std::string IdName = IdentifierStr;
    getNextToken(); // eat identifier

    if (CurTok == tok_lsquare) {
        getNextToken(); // eat '['

        if (CurTok != tok_number) {
            std::cerr << "Expected number in array declaration" << std::endl;
            return nullptr;
        }

        int ArraySize = static_cast<int>(NumVal);
        getNextToken(); // eat number

        if (CurTok != tok_rsquare) {
            std::cerr << "Expected ']' after array size" << std::endl;
            return nullptr;
        }
        getNextToken(); // eat ']'

        return std::make_unique<ArrayDeclarationExprAST>(IdName, ArraySize);
    }

    if (CurTok != tok_assign) {
        std::cerr << "Expected '=' after identifier" << std::endl;
        return nullptr;
    }
    getNextToken(); // eat '='

    auto Expr = ParseExpression();
    if (!Expr)
        return nullptr;

    return std::make_unique<VariableDeclarationExprAST>(IdName, std::move(Expr));
}

static std::unique_ptr<ExprAST> ParseBoolDecl() {
    getNextToken(); // eat 'bool'

    if (CurTok != tok_identifier) {
        std::cerr << "Expected identifier after 'bool'" << std::endl;
        return nullptr;
    }

    std::string IdName = IdentifierStr;
    getNextToken(); // eat identifier

    if (CurTok != tok_assign) {
        std::cerr << "Expected '=' after identifier" << std::endl;
        return nullptr;
    }
    getNextToken(); // eat '='

    auto Expr = ParseExpression();
    if (!Expr)
        return nullptr;

    return std::make_unique<VariableDeclarationExprAST>(IdName, std::move(Expr));
}

//===----------------------------------------------------------------------===//
// Main function
//===----------------------------------------------------------------------===//

void handleFile(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }
    InputStream = &file;

    while (true) {
        getNextToken();

        if (CurTok == tok_eof) {
            break;
        }
        else if (CurTok == tok_semi) {
            continue;
        }

        std::unique_ptr<ExprAST> AST;
        if (CurTok == tok_int) {
            AST = ParseIntDecl();
        }
        else if (CurTok == tok_bool) {
            AST = ParseBoolDecl();
        }
        else {
            AST = ParseExpression();
        }

        if (AST) {
            AST->evaluate();
        }
        else {
            std::cerr << "Error at line " << CurrentLine << ": Error parsing expression." << std::endl;
            return;  // Terminate execution on error
        }

        if (CurTok != tok_semi) {
            std::cerr << "Error at line " << CurrentLine << ": Expected ';' at the end of the expression." << std::endl;
            return;  // Terminate execution on error
        }
    }
}

void handleInteractive() {
    while (true) {
        std::cout << "Enter an expression: ";
        getNextToken();

        if (CurTok == tok_eof) {
            break;
        }
        else if (CurTok == tok_semi) {
            continue;
        }

        std::unique_ptr<ExprAST> AST;
        if (CurTok == tok_int) {
            AST = ParseIntDecl();
        }
        else if (CurTok == tok_bool) {
            AST = ParseBoolDecl();
        }
        else {
            AST = ParseExpression();
        }

        if (AST) {
            std::cout << "Result: " << AST->evaluate() << std::endl;
        }
        else {
            std::cerr << "Error parsing expression." << std::endl;
            return;  // Terminate execution on error
        }

        if (CurTok != tok_semi) {
            std::cerr << "Expected ';' at the end of the expression." << std::endl;
            return;  // Terminate execution on error
        }
    }
}

int main(int argc, char** argv) {
    if (argc > 2 && std::string(argv[1]) == "-f") {
        handleFile(argv[2]);
    }
    else {
        handleInteractive();
    }

    return 0;
}
