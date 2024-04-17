#pragma once
#include "Class_AST.h"

class Expression_node : public Ast_node {
public:
    virtual int evaluate() const = 0;
};
