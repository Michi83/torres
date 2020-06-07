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
    Move best_move;
    memset(&best_move, 0, sizeof (Move));
    for (int depth = 1; depth < 256; depth++)
    {
        int nodes = 0;
        clock_t time1 = clock();
        int score = minimax(position, depth, -200000, 200000, &nodes,
            &best_move);
        clock_t time2 = clock();
        int time = 100 * (time2 - time1) / CLOCKS_PER_SEC;
        if (verbose)
        {
            printf("%3d %7d %7d %11d ", depth, score, time, nodes);
            print_move(&best_move);
            printf("\n");
        }
        if (score >= 100000 || score <= -100000 || time > min_time)
        {
            break;
        }
    }
    return best_move;
}

int minimax(Position* position, int depth, int alpha, int beta, int* nodes,
    Move* best_move)
{
    (*nodes)++;
    Transposition* transposition = get_transposition(position, depth);
    if (transposition != NULL)
    {
        *best_move = transposition->best_move;
        return transposition->score;
    }
    if (depth == 0)
    {
        int score = evaluate(position);
        add_transposition(position, 0, score, NULL);
        return score;
    }
    MoveList move_list;
    generate_moves(position, &move_list);
    int score = -200000;
    int legal_moves = 0;
    for (int i = 0; i < move_list.count; i++)
    {
        Move* move = move_list.moves + i;
        make_move(position, move);
        if (legal(position))
        {
            legal_moves = 1;
            Move best_child_move;
            memset(&best_child_move, 0, sizeof (Move));
            int child_score = -minimax(position, depth - 1, -beta, -alpha,
                nodes, &best_child_move);
            if (child_score > score)
            {
                score = child_score;
                *best_move = *move;
                if (score > alpha)
                {
                    alpha = score;
                    if (alpha >= beta)
                    {
                        // cutoff!
                        unmake_move(position, move);
                        add_transposition(position, depth, score, best_move);
                        return score;
                    }
                }
            }
        }
        unmake_move(position, move);
    }
    if (!legal_moves)
    {
        // checkmate or stalemate
        score = check(position, position->player) ? -100000 - depth : 0;
    }
    add_transposition(position, depth, score, best_move);
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