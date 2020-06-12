#pragma once

#include "position.h"

/*
Piece-square table for the black bishop.
*/
extern int black_bishop_table[];

/*
Endgame piece-square table for the black king.
*/
extern int black_king_endgame_table[];

/*
Piece-square table for the black king.
*/
extern int black_king_table[];

/*
Piece-square table for the black knight.
*/
extern int black_knight_table[];

/*
Piece-square table for the black pawn.
*/
extern int black_pawn_table[];

/*
Piece-square table for the black queen.
*/
extern int black_queen_table[];

/*
Piece-square table for the black rook.
*/
extern int black_rook_table[];

/*
Checks if a position is an endgame.

Parameters:
- Position* position: The position to be examined.

Returns: 1 if it is an endgame, 0 otherwise.
*/
int endgame(Position* position);

/*
Statically evaluates a position.

Parameters:
- Position* position: The position to be examined.

Returns: The position's score in centipawns. Positive if the current player has
an advantage, negative if the current player has a disadvantage.
*/
int evaluate(Position* position);

/*
Piece-square table for the white bishop.
*/
extern int white_bishop_table[];

/*
Endgame piece-square table for the white king.
*/
extern int white_king_endgame_table[];

/*
Piece-square table for the white king.
*/
extern int white_king_table[];

/*
Piece-square table for the white knight.
*/
extern int white_knight_table[];

/*
Piece-square table for the white pawn.
*/
extern int white_pawn_table[];

/*
Piece-square table for the white queen.
*/
extern int white_queen_table[];

/*
Piece-square table for the white rook.
*/
extern int white_rook_table[];
