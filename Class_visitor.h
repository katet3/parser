#pragma once

#include "Class_binary_expression.h"
#include "Class_boolean_expression.h"
#include "Class_numeric_literal.h"

class Visitor {
public:
    virtual void visit(Binary_expression_node& expr) = 0;
    virtual void visit(Numeric_literal_node& literal) = 0;
    virtual void visit(Boolean_expression_node& literal) = 0;
};