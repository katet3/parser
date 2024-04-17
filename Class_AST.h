#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "Class_visitor.h"

// Определение базового класса для узлов AST
class Ast_node {
public:
    virtual ~Ast_node() {}
    virtual void accept(class Visitor& v) = 0; // Паттерн "Посетитель" для обработки узлов
};