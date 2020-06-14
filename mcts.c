#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mcts.h"
#include "generate.h"
#include "position.h"
#include "xboard.h"

void backpropagate(Node* node, int result)
{
    node->n++;
    if (node->position.player == result)
    {
        node->t++;
    }
    else if (result == 0)
    {
        node->t += 0.5;
    }
    if (node->parent != NULL)
    {
        backpropagate(node->parent, result);
    }
}

double calculate_uct(Node* node)
{
    return (node->n - node->t) / node->n
        + sqrt(2 * log(node->parent->n) / node->n);
}

void clean_up_nodes(Node* node)
{
    for (int i = 0; i < node->child_count; i++)
    {
        clean_up_nodes(node->children[i]);
    }
    free(node);
}

Node* create_node(Position* position, Node* parent)
{
    Node* node = calloc(1, sizeof (Node));
    node->parent = parent;
    node->position = *position;
    return node;
}

int evaluate(Position* position)
{
    PositionList position_list;
    generate_moves(position, &position_list);
    if (position_list.count == 0 && check(position, position->player))
    {
        return -position->player;
    }
    else
    {
        return 0;
    }
}

void expand(Node* node)
{
    PositionList position_list;
    generate_moves(&node->position, &position_list);
    for (int i = 0; i < position_list.count; i++)
    {
        Position* child_position = position_list.positions + i;
        Node* child = create_node(child_position, node);
        node->children[node->child_count] = child;
        node->child_count++;
    }
}

Node* get_best_child(Node* node)
{
    double best_score = -1;
    Node* best_child = NULL;
    for (int i = 0; i < node->child_count; i++)
    {
        Node* child = node->children[i];
        double score = (child->n - child->t) / child->n;
        if (score > best_score)
        {
            best_score = score;
            best_child = child;
        }
    }
    return best_child;
}

Position mcts(Position* position)
{
    Node* root = create_node(position, NULL);
    for (int i = 0; i < 1000; i++)
    {
        Node* node = select_node(root);
        if (node->n > 0)
        {
            expand(node);
            if (node->child_count > 0)
            {
                node = node->children[0];
            }
        }
        int result = rollout(node);
        backpropagate(node, result);
    }
    Node* best_child = get_best_child(root);
    Position best_child_position = best_child->position;
    clean_up_nodes(root);
    return best_child_position;
}

int rollout(Node* node)
{
    Position position = node->position;
    while (1)
    {
        PositionList position_list;
        generate_moves(&position, &position_list);
        if (position_list.count == 0 || position.halfmove_clock == 100)
        {
            break;
        }
        int i = rand() % position_list.count;
        position = position_list.positions[i];
    }
    return evaluate(&position);
}

Node* select_node(Node* node)
{
    while (node->child_count > 0)
    {
        double best_uct = -1;
        Node* best_child = NULL;
        for (int i = 0; i < node->child_count; i++)
        {
            Node* child = node->children[i];
            if (child->n == 0)
            {
                best_child = child;
                break;
            }
            double uct = calculate_uct(child);
            if (uct > best_uct)
            {
                best_uct = uct;
                best_child = child;
            }
        }
        node = best_child;
    }
    return node;
}

int main(void)
{
    talk_to_xboard(&mcts);
    return 0;
}
