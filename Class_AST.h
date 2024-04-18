#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <string>

#include "structures.h"
#include "Class_visitor.h"

#ifndef AST_NODE_H
#define AST_NODE_H


// Определение базового класса для узлов AST
class Ast_node {
public:
    virtual ~Ast_node() {}
    virtual void accept(class Visitor& v) = 0; // Паттерн "Посетитель" для обработки узлов
};


#endif // !AST_NODE_H