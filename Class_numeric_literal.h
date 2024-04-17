#pragma once
#ifndef NUMERIC_LITERAL_NODE_H
#define NUMERIC_LITERAL_NODE_H

#include "Class_expression.h"

class Numeric_literal_node : public Expression_node {
    int value;

public:
    Numeric_literal_node(int val) : value(val) {}

    void accept(Visitor& v) override;
    int evaluate() const override;

};

#endif NUMERIC_LITERAL_NODE_H