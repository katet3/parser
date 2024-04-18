#include "Class_expression.h"

#ifndef VARIBLE_H
#define VARIBLE_H

class Varible_node : public Expression_node {
    std::string value;

public:
    Varible_node(std::string val) : value(val) {}

    void accept(Visitor& v) override;
    std::string evaluate();

};

#endif VARIBLE_H