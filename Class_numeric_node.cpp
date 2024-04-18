#include "Class_numeric_node.h"


void Numeric_node::accept(Visitor& v) {
    v.visit(*this);
}

int Numeric_node::evaluate() {
    return value;
}