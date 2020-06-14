#pragma once

#include "position.h"

int game_over(Position* position);
void talk_to_xboard(Position (*algorithm)(Position*));
void xboard_force(int* side);
void xboard_go(Position* position, int* side, Position (*algorithm)(Position*));
void xboard_new(Position* position, int* side);
void xboard_playother(Position* position, int* side);
void xboard_protover(void);
void xboard_quit(void);
void xboard_rejected(void);
void xboard_setboard(Position* position, char fen[], int* side, Position
    (*algorithm)(Position*));
void xboard_usermove(Position* position, char* usermove, int* side,
    Position (*algorithm)(Position*));
