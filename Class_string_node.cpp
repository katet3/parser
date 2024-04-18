#include "Class_string_node.h"


void String_node::accept(Visitor& v) {
    v.visit(*this);
}

std::string String_node::evaluate() {
    return value;
}