#pragma once

#include "position.h"

/*
Checks if the current player has legal moves.

Parameters:
- Position* position: The position to be examined.

Return: 1 if the current player doesn't have legal moves, 0 otherwise.
*/
int game_over(Position* position);

/*
Handles the xboard protocol's "go" command.

Parameters:
- Position* position: A position.
- int verbose: 1 if output is desired, 0 otherwise.
*/
void xboard_go(Position* position, int verbose);

/*
Handles the xboard protocol's "usermove" command.

Parameters:
- Position* position: A position.
- char* usermove: The usermove in "pure" algebraic notation.
*/
void xboard_usermove(Position* position, char* usermove);
