#include "Class_boolean_expression.h"

Boolean_expression_node::Boolean_expression_node(std::unique_ptr<Expression_node> l, std::string o, std::unique_ptr<Expression_node> r)
    : left(std::move(l)), op(std::move(o)), right(std::move(r)) {}

Boolean_expression_node::~Boolean_expression_node() {}

void Boolean_expression_node::accept(Visitor& v) {
    v.visit(*this);
}

bool Boolean_expression_node::evaluate() {
    bool leftValue = static_cast<bool>(left->evaluate());
    bool rightValue = static_cast<bool>(right->evaluate());

    if (op == "==") return leftValue == rightValue;
    if (op == "!=") return leftValue != rightValue;
    if (op == "<") return leftValue < rightValue;
    if (op == ">") return leftValue > rightValue;
    if (op == "<=") return leftValue <= rightValue;
    if (op == ">=") return leftValue >= rightValue;

    throw std::runtime_error("Unsupported boolean operator");
}
