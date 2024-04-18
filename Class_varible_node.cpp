#include "Class_varible_node.h"

void Varible_node::accept(Visitor& v) {
    v.visit(*this);
}

std::string Varible_node::evaluate() {
    return value;
}