#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "evaluate.h"
#include "generate.h"
#include "minimax.h"
#include "position.h"
#include "xboard.h"

int compare_moves(const void* item1, const void* item2)
{
    Position* position1 = (Position*)item1;
    Position* position2 = (Position*)item2;
    int origin1 = position1->move.origin;
    int target1 = position1->move.target;
    int origin2 = position2->move.origin;
    int target2 = position2->move.target;
    return history[origin2][target2] - history[origin1][target1];
}

int history[120][120];

Position iterative_deepening(Position* position)
{
    int min_time = 200;
    Position best_child;
    memset(&best_child, 0, sizeof (Position));
    memset(&history, 0, 120 * 120 * sizeof (int));
    for (int depth = 1; depth < 256; depth++)
    {
        int nodes = 0;
        clock_t time1 = clock();
        int score = minimax(position, depth, -200000, 200000, &nodes,
            &best_child);
        clock_t time2 = clock();
        int time = 100 * (time2 - time1) / CLOCKS_PER_SEC;
        if (score >= 100000 || score <= -100000 || time > min_time)
        {
            break;
        }
    }
    return best_child;
}

int minimax(Position* position, int depth, int alpha, int beta, int* nodes,
    Position* best_child)
{
    (*nodes)++;
    if (depth == 0)
    {
        int score = evaluate(position);
        return score;
    }
    PositionList position_list;
    generate_moves(position, &position_list);
    if (position_list.count == 0)
    {
        // checkmate or stalemate
        int score = check(position, position->player) ? -100000 - depth : 0;
        return score;
    }
    int score = -200000;
    Position dummy;
    qsort(position_list.positions, position_list.count, sizeof (Position),
        compare_moves);
    for (int i = 0; i < position_list.count; i++)
    {
        Position* child = position_list.positions + i;
        int child_depth = depth - 1;
        if (child_depth > 1 && i >= 3)
        {
            child_depth--;
        }
        int child_score = -minimax(child, child_depth, -beta, -alpha, nodes,
            &dummy);
        if (child_score > score)
        {
            score = child_score;
            *best_child = *child;
            if (score > alpha)
            {
                alpha = score;
                if (alpha >= beta)
                {
                    // cutoff
                    int origin = child->move.origin;
                    int target = child->move.target;
                    history[origin][target] += 1 << depth;
                    return score;
                }
            }
        }
    }
    return score;
}

int main(void)
{
    talk_to_xboard(&iterative_deepening);
    return 0;
}
