#include "Class_numeric_literal.h"

Numeric_literal_node::Numeric_literal_node(int val) : value(val) {}

void Numeric_literal_node::accept(Visitor& v) {
    v.visit(*this);
}

int Numeric_literal_node::evaluate() const {
    return value;
}