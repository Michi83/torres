#pragma once

#include "position.h"

/*
Performs minimax searches of increasing depth.

Parameters:
- Position* position: The position to search.
- int min_time: The minimum time to be spent in centiseconds.
- int verbose: 1 if output is desired, 0 otherwise.

Returns: A copy of the position in which the best move found was made.
*/
Position iterative_deepening(Position* position, int min_time, int verbose);

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
