#pragma once

// NOTE: CURRENTLY BROKEN AND UNUSED

#include "position.h"

#define TRANSPOSITION_TABLE_SIZE 65536

typedef struct Transposition Transposition;

/*
Contains previously calculated information about a position;

Fields:
- Move best_move: The best move in this position.
- int depth: The search depth.
- uint64_t hash: The position's hash.
- int score: The position's score in centipawns. Positive if the current player
  has an advantage, negative if the current player has a disadvantage.
*/
struct Transposition
{
    Move best_move;
    int depth;
    uint64_t hash;
    int score;
};

/*
Adds a transposition to the transposition table. May overwrite an existing
transposition.

Parameters:
- Position* position: A position.
- int depth: The search depth.
- int score: The position's score in centipawns. Positive if the current player
  has an advantage, negative if the current player has a disadvantage.
- Move* best_move: The presumed best move in this position.
*/
void add_transposition(Position* position, int depth, int score,
    Move* best_move);

/*
Random keys for the hash function.
*/
extern uint64_t black_bishop_keys[];

/*
Random keys for the hash function.
*/
extern uint64_t black_king_keys[];

/*
Random keys for the hash function.
*/
extern uint64_t black_knight_keys[];

/*
Random keys for the hash function.
*/
extern uint64_t black_pawn_keys[];

/*
Random keys for the hash function.
*/
extern uint64_t black_queen_keys[];

/*
Random keys for the hash function.
*/
extern uint64_t black_rook_keys[];

/*
Calculates a position's hash.

Parameters:
- Position* position: A position.

Returns: The position's hash.
*/
uint64_t calculate_hash(Position* position);

/*
Random keys for the hash function.
*/
extern uint64_t castling_keys[];

/*
Random keys for the hash function.
*/
extern uint64_t en_passant_keys[];

/*
Retrieves a transposition for a position.

Parameters:
- Position* position: A position.
- int min_depth: The required minimum depth.

Returns: The transposition or NULL if there is none.
*/
Transposition* get_transposition(Position* position, int min_depth);

/*
Random key for the hash function.
*/
extern uint64_t player_key;

/*
The engine's transposition table holding information about previously examined
positions, thus avoiding some duplicate calculations.
*/
extern Transposition transposition_table[];

/*
Random keys for the hash function.
*/
extern uint64_t white_bishop_keys[];

/*
Random keys for the hash function.
*/
extern uint64_t white_king_keys[];

/*
Random keys for the hash function.
*/
extern uint64_t white_knight_keys[];

/*
Random keys for the hash function.
*/
extern uint64_t white_pawn_keys[];

/*
Random keys for the hash function.
*/
extern uint64_t white_queen_keys[];

/*
Random keys for the hash function.
*/
extern uint64_t white_rook_keys[];
