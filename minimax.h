#pragma once

#include "position.h"

typedef struct IterativeDeepeningParameters IterativeDeepeningParameters;

struct IterativeDeepeningParameters
{
    Position position;
    Position child_position;
};

/*
Compares two moves according to the history heuristic.

Parameters:
- const void* item1: A position.
- const void* item2: Another position.

Returns: A negative number if item1 should go before item2, a positive number if
item2 should go before item1.
*/
int compare_moves(const void* item1, const void* item2);

/*
The history table for the history heuristic.
*/
extern int history[120][120];

void* iterative_deepening(void* parameters);

/*
Performs a recursive minimax tree search with alpha-beta pruning.

Parameters:
- Position* position: The position to search.
- int depth: The search depth.
- int alpha: The alpha variable for alpha-beta pruning. Should be -200000 in the
  initial call.
- int beta: See above. Should be 200000 in the initial call.
- int* nodes: A counter that gets incremented by 1 for every node visited.
- Position* best_child: Overwritten by the function to contain a copy of the
  position in which the best move found has been made.

Returns: The positions score in centipawns. Positive if the current player has
an advantage, negative if they have a disadvantage.
*/
int minimax(Position* position, int depth, int alpha, int beta, int* nodes,
    Position* best_child);

Position run_iterative_deepening_thread(Position* position);
