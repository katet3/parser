#ifndef VISITOR_H
#define VISITOR_H


class Binary_expression_node;
class Numeric_node;
class Boolean_expression_node;
class Internal_function_node;
class String_node;
class Varible_node;


class Visitor {
public:
    virtual void visit(Binary_expression_node& expr) = 0;
    virtual void visit(Numeric_node& literal) = 0;
    virtual void visit(Boolean_expression_node& literal) = 0;
    virtual void visit(Internal_function_node& literal) = 0;
    virtual void visit(String_node& literal) = 0; 
    virtual void visit(Varible_node& literal) = 0;
};

#endif // !VISITOR_H