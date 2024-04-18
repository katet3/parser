#include "Class_AST.h"
#include "Class_expression.h"
#include "Class_numeric_node.h"
#include "Class_boolean_expression.h"

#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

class Syntax_tree {
private:
    std::unique_ptr<Ast_node> root; // корневой узел дерева

public:
    Syntax_tree();
    ~Syntax_tree();

    void setRoot(std::unique_ptr<Ast_node> node);
    Ast_node* getRoot() const;

    void make_tree(std::vector<Token> tokens);
    void execute();
};

#endif // !SYNTAX_TREE_H