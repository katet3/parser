#include "Class_binary_expression.h"

Binary_expression_node::Binary_expression_node(std::unique_ptr<Expression_node> l, char o, std::unique_ptr<Expression_node> r)
    : left(std::move(l)), op(o), right(std::move(r)) {}

Binary_expression_node::~Binary_expression_node() {}

void Binary_expression_node::accept(Visitor& v) {
    v.visit(*this);
}

int Binary_expression_node::evaluate() {
    int leftValue = left->evaluate();
    int rightValue = right->evaluate();
    switch (op) {
    case '+': return leftValue + rightValue;
    case '-': return leftValue - rightValue;
    case '*': return leftValue * rightValue;
    case '/':
        if (rightValue == 0) throw std::runtime_error("Division by zero");
        return int(leftValue / rightValue);
    default:
        throw std::runtime_error("Unsupported operator");
    }
}
