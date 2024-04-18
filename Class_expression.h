#include "Class_AST.h"

#ifndef EXPRESSION_NODE_H
#define EXPRESSION_NODE_H

class Expression_node : public Ast_node {
public:
    virtual ~Expression_node() {}
    virtual void accept(class Visitor& v) = 0;
    int evaluate() { return 0; }
};

#endif // !EXPRESSION_NODE_H