#include "Class_internal_function_node.h"


void Internal_function_node::accept(Visitor& v) {
    v.visit(*this);
}

std::string Internal_function_node::evaluate() {
    return value;
}