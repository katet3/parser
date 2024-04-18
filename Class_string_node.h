#include "Class_expression.h"

#ifndef STRING_NODE_H
#define STRING_NODE_H


class String_node : public Expression_node {
    std::string value;

public:
    String_node(std::string val) : value(val) {}

    void accept(Visitor& v) override;
    std::string evaluate();

};

#endif // !STRING_NODE_H