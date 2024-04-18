#include "Class_expression.h"

#ifndef NUMERIC_NODE_H
#define NUMERIC_NODE_H

class Numeric_node : public Expression_node {
    int value;

public:
    Numeric_node(int val) : value(val) {}

    void accept(Visitor& v) override;
    int evaluate();

};

#endif // !NUMERIC_NODE_H