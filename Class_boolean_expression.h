#pragma once

#include "Class_expression.h"
#include "Class_visitor.h"
#include <memory>
#include <stdexcept>
#include <string>

class Boolean_expression_node : public Expression_node {
private:
    std::unique_ptr<Expression_node> left;
    std::unique_ptr<Expression_node> right;
    std::string op;  // Оператор (==, !=, <, >, <=, >=)

public:
    Boolean_expression_node(std::unique_ptr<Expression_node> l, std::string o, std::unique_ptr<Expression_node> r);
    ~Boolean_expression_node();

    void accept(Visitor& v) override;
    bool evaluate();
};
