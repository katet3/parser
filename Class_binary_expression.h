#include "Class_expression.h"
#include "Class_visitor.h"


#ifndef BINARY_EXPRESSION_H
#define BINARY_EXPRESSION_H

class Binary_expression_node : public Expression_node {
private:
    std::unique_ptr<Expression_node> left;
    std::unique_ptr<Expression_node> right;
    char op;

public:
    Binary_expression_node(std::unique_ptr<Expression_node> l, char o, std::unique_ptr<Expression_node> r);
    virtual ~Binary_expression_node();

    void accept(Visitor& v) override;
    int evaluate();
};


#endif // !BINARY_EXPRESSION_H