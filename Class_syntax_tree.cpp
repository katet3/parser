#include "Class_syntax_tree.h"

Syntax_tree::Syntax_tree() {}

Syntax_tree::~Syntax_tree() {}

void Syntax_tree::setRoot(std::unique_ptr<Ast_node> node) {
    root = std::move(node);
}

Ast_node* Syntax_tree::getRoot() const {
    return root.get();
}

void Syntax_tree::execute() {
    if (root) {
        // Предположим, что у Ast_node есть метод accept, который принимает Visitor
        // Пример выполнения дерева с помощью паттерна "Посетитель"
        // root->accept(visitor);
    }
}


void Syntax_tree::make_tree(std::vector<Token> tokens)
{
    Numeric_node var1(1);
    std::unique_ptr<Numeric_node> l = std::make_unique<Numeric_node>(var1);
    std::unique_ptr<Numeric_node> r = std::make_unique<Numeric_node>(var1);

    Boolean_expression_node a(l, '<', r);
}