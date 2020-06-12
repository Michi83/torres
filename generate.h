#pragma once

#include "position.h"

/*
Checks if a square is attacked.

Parameters:
- Position* position: A position.
- int square: The square to be examined.
- int attacker: The attacker, WHITE or BLACK.

Returns: 1 if the square is attacked, 0 otherwise.
*/
int attacked(Position* position, int square, int attacker);

/*
Checks if a square is attacked by a bishop.

Parameters:
- Position* position: A position.
- int square: The square to be examined.
- int attacker: The attacker, WHITE or BLACK.

Returns: 1 if the square is attacked, 0 otherwise.
*/
int attacked_by_bishop(Position* position, int square, int attacker);

/*
Checks if a square is attacked by a king.

Parameters:
- Position* position: A position.
- int square: The square to be examined.
- int attacker: The attacker, WHITE or BLACK.

Returns: 1 if the square is attacked, 0 otherwise.
*/
int attacked_by_king(Position* position, int square, int attacker);

/*
Checks if a square is attacked by a knight.

Parameters:
- Position* position: A position.
- int square: The square to be examined.
- int attacker: The attacker, WHITE or BLACK.

Returns: 1 if the square is attacked, 0 otherwise.
*/
int attacked_by_knight(Position* position, int square, int attacker);

/*
Checks if a square is attacked by a pawn.

Parameters:
- Position* position: A position.
- int square: The square to be examined.
- int attacker: The attacker, WHITE or BLACK.

Returns: 1 if the square is attacked, 0 otherwise.
*/
int attacked_by_pawn(Position* position, int square, int attacker);

/*
Checks if a square is attacked by a queen.

Parameters:
- Position* position: A position.
- int square: The square to be examined.
- int attacker: The attacker, WHITE or BLACK.

Returns: 1 if the square is attacked, 0 otherwise.
*/
int attacked_by_queen(Position* position, int square, int attacker);

/*
Checks if a square is attacked by a rook.

Parameters:
- Position* position: A position.
- int square: The square to be examined.
- int attacker: The attacker, WHITE or BLACK.

Returns: 1 if the square is attacked, 0 otherwise.
*/
int attacked_by_rook(Position* position, int square, int attacker);

/*
Displacements for bishop moves.
*/
extern int bishop_displacements[];

/*
Checks if black kingside castling is possible.

Parameters:
- Position* position: A position.

Returns: 1 if castling is possible, 0 otherwise.
*/
int black_kingside_castling(Position* position);

/*
Checks if black queenside castling is possible.

Parameters:
- Position* position: A position.

Returns: 1 if castling is possible, 0 otherwise.
*/
int black_queenside_castling(Position* position);

/*
Checks if a square is occupied by the current player's opponent.

Parameters:
- Position* position: A position.
- int square: The square to be examined.

Returns: 1 if the square is occupied by the current player's opponent, 0
otherwise.
*/
int capturable(Position* position, int square);

/*
Checks if a square is occupied by the current player's opponent or empty.

Parameters:
- Position* position: A position.
- int square: The square to be examined.

Returns: 1 if the square is occupied by the current player's opponent or empty,
0 otherwise.
*/
int capturable_or_empty(Position* position, int square);

/*
Checks if a player is in check.

Parameters:
- Position* position: A position.
- int defender: The defender, WHITE or BLACK.

Returns: 1 if the player is in check, 0 otherwise.
*/
int check(Position* position, int defender);

/*
Checks if a square belongs to the current player's second rank and thus can be
the origin of a double step.

Parameters:
- Position* position: A position.
- int square: The square to be examined.

Returns: 1 if the square belongs to the current player's second rank, 0
otherwise.
*/
int double_step(Position* position, int square);

/*
Generates bishop moves from a square.

Parameters:
- Position* position: A position.
- int origin: The origin square.
- PositionList* position_list: A position list to add the moves to.
*/
void generate_bishop_moves(Position* position, int origin,
    PositionList* position_list);

/*
Generates king moves from a square.

Parameters:
- Position* position: A position.
- int origin: The origin square.
- PositionList* position_list: A position list to add the moves to.
*/
void generate_king_moves(Position* position, int origin,
    PositionList* position_list);

/*
Generates knight moves from a square.

Parameters:
- Position* position: A position.
- int origin: The origin square.
- PositionList* position_list: A position list to add the moves to.
*/
void generate_knight_moves(Position* position, int origin,
    PositionList* position_list);

/*
Generates moves for a position. For each legal move, a copy of the position is
made and then the move is made on the copy.

Parameters:
- Position* position: A position.
- int origin: The origin square.
- PositionList* position_list: A position list to add the moves to.
*/
void generate_moves(Position* position, PositionList* position_list);

/*
Generates pawn moves from a square.

Parameters:
- Position* position: A position.
- int origin: The origin square.
- PositionList* position_list: A position list to add the moves to.
*/
void generate_pawn_moves(Position* position, int origin,
    PositionList* position_list);

/*
Generates queen moves from a square.

Parameters:
- Position* position: A position.
- int origin: The origin square.
- PositionList* position_list: A position list to add the moves to.
*/
void generate_queen_moves(Position* position, int origin,
    PositionList* position_list);

/*
Generates rook moves from a square.

Parameters:
- Position* position: A position.
- int origin: The origin square.
- PositionList* position_list: A position list to add the moves to.
*/
void generate_rook_moves(Position* position, int origin,
    PositionList* position_list);

/*
Displacements for king moves.
*/
extern int king_displacements[];

/*
Displacements for knight moves.
*/
extern int knight_displacements[];

/*
Checks if a position is legal, i.e. if the preceding move did not leave the king
in check.

Parameters:
- Position* position: The position to be examined.

Returns: 1 if the position is legal, 0 otherwise.
*/
int legal(Position* position);

/*
Copies a position and makes a move in the copy.

Parameters:
- Position* position: The position before the move.
- int origin: The origin square.
- int target: The target square.
- int promotion: The piece to promote to or NONE.
- Position* copy. Overwritten by the function to contain the position after the
  move.
*/
void make_move(Position* position, int origin, int target, int promotion,
    Position* copy);

/*
Displacements for pawn moves.
*/
extern int pawn_displacements[];

/*
Checks if a square belongs to the current player's eighth rank and thus can be
the target of a pawn promotion.

Parameters:
- Position* position: A position.
- int square: The square to be examined.

Returns: 1 if the square belongs to the current player's eighth rank, 0
otherwise.
*/
int promotion(Position* position, int square);

/*
Displacements for queen moves.
*/
extern int queen_displacements[];

/*
Displacements for rook moves.
*/
extern int rook_displacements[];

/*
Checks if white kingside castling is possible.

Parameters:
- Position* position: A position.

Returns: 1 if castling is possible, 0 otherwise.
*/
int white_kingside_castling(Position* position);

/*
Checks if white queenside castling is possible.

Parameters:
- Position* position: A position.

Returns: 1 if castling is possible, 0 otherwise.
*/
int white_queenside_castling(Position* position);
