#pragma once

#include "generate.h"
#include "position.h"

typedef struct Node Node;

struct Node
{
    int child_count;
    Node* children[256];
    int n;
    Node* parent;
    Position position;
    double t;
};

void backpropagate(Node* node, int result);
double calculate_uct(Node* node);
void clean_up_nodes(Node* node);
Node* create_node(Position* position, Node* parent);
int evaluate(Position* position);
void expand(Node* node);
Node* get_best_child(Node* node);
Position mcts(Position* position);
int rollout(Node* node);
Node* select_node(Node* node);
