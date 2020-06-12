#include <stdio.h>
#include <string.h>
#include <time.h>
#include "evaluate.h"
#include "generate.h"
#include "minimax.h"
#include "position.h"

Position iterative_deepening(Position* position, int min_time, int verbose)
{
    Position best_child;
    memset(&best_child, 0, sizeof (Position));
    for (int depth = 1; depth < 256; depth++)
    {
        int nodes = 0;
        clock_t time1 = clock();
        int score = minimax(position, depth, -200000, 200000, &nodes,
            &best_child);
        clock_t time2 = clock();
        int time = 100 * (time2 - time1) / CLOCKS_PER_SEC;
        if (verbose)
        {
            printf("%3d %7d %7d %11d ", depth, score, time, nodes);
            print_move(&best_child.move);
            printf("\n");
        }
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
    for (int i = 0; i < position_list.count; i++)
    {
        Position* child = position_list.positions + i;
        int child_score = -minimax(child, depth - 1, -beta, -alpha, nodes,
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
                    return score;
                }
            }
        }
    }
    return score;
}
