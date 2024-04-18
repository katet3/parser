#include "Class_expression.h"

#ifndef INTERNAL_FUNCTION_NODE_H
#define INTERNAL_FUNCTION_NODE_H

class Internal_function_node : public Expression_node {
    std::string value;

public:
    Internal_function_node(std::string val) : value(val) {}

    void accept(Visitor& v) override;
    std::string evaluate();

};

#endif // !INTERNAL_FUNCTION_NODE_H