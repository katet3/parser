#pragma once

#include "Class_AST.h"
// Класс синтаксического дерева
class SyntaxTree {
private:
    std::unique_ptr<Ast_node> root; // корневой узел дерева

public:
    // Задает корневой узел дерева
    void setRoot(std::unique_ptr<Ast_node> node) { root = std::move(node); }

    Ast_node* getRoot() const { return root.get(); }

    // Функция для выполнения дерева (может использовать visitor для выполнения)
    void execute() {
        if (root) {
            // Здесь может быть код для обработки дерева, например, обход с помощью Visitor
        }
    }
};