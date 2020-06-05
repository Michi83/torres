#include <stdio.h>
#include <string.h>
#include <time.h>
#include "torres.h"

int compare_moves(Move* move1, Move* move2)
{
    return move1->origin == move2->origin && move1->target == move2->target
        && move1->promotion == move2->promotion;
}

Move iterative_deepening(Position* position, int min_time, int verbose)
{
    Move principal_variation[256];
    memset(principal_variation, 0, 256 * sizeof (Move));
    for (int depth = 1; depth < 256; depth++)
    {
        int nodes = 0;
        clock_t time1 = clock();
        int score = minimax(position, depth, -200000, 200000, &nodes,
            principal_variation);
        clock_t time2 = clock();
        int time = 100 * (time2 - time1) / CLOCKS_PER_SEC;
        if (verbose)
        {
            printf("%3d %7d %7d %11d ", depth, score, time, nodes);
            for (int i = 0; i < depth; i++)
            {
                Move* move = principal_variation + i;
                if (move->origin == 0)
                {
                    break;
                }
                print_move(move);
                printf(" ");
            }
            printf("\n");
        }
        if (score >= 100000 || score <= -100000 || time > min_time)
        {
            break;
        }
    }
    return principal_variation[0];
}

int minimax(Position* position, int depth, int alpha, int beta, int* nodes,
    Move* principal_variation)
{
    (*nodes)++;
    if (depth == 0)
    {
        return evaluate(position);
    }
    MoveList move_list;
    generate_moves(position, &move_list);
    presort_moves(&move_list, principal_variation);
    int score = alpha;
    // reset the current best move
    memset(principal_variation, 0, sizeof (Move));
    int legal_moves = 0;
    for (int i = 0; i < move_list.count; i++)
    {
        Move* move = move_list.moves + i;
        make_move(position, move);
        if (legal(position))
        {
            legal_moves = 1;
            Move child_principal_variation[depth - 1];
            // Copy principal variation down to be used for presorting in the
            // recursive call.
            memcpy(child_principal_variation, principal_variation + 1,
                (depth - 1) * sizeof (Move));
            int child_score = -minimax(position, depth - 1, -beta, -alpha,
                nodes, child_principal_variation);
            if (child_score > score)
            {
                score = child_score;
                principal_variation[0] = *move;
                memcpy(principal_variation + 1, child_principal_variation,
                    (depth - 1) * sizeof (Move));
                if (score > alpha)
                {
                    alpha = score;
                    if (alpha >= beta)
                    {
                        // cutoff!
                        unmake_move(position, move);
                        return beta;
                    }
                }
            }
        }
        unmake_move(position, move);
    }
    if (!legal_moves)
    {
        // checkmate or stalemate
        return check(position, position->player) ? -100000 - depth : 0;
    }
    return score;
}

void presort_moves(MoveList* move_list, Move* best_move)
{
    for (int i = 0; i < move_list->count; i++)
    {
        if (compare_moves(move_list->moves + i, best_move))
        {
            Move temp = move_list->moves[0];
            move_list->moves[0] = move_list->moves[i];
            move_list->moves[i] = temp;
            return;
        }
    }
}