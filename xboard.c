#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generate.h"
#include "position.h"
#include "xboard.h"

int game_over(Position* position)
{
    PositionList position_list;
    generate_moves(position, &position_list);
    return position_list.count == 0;
}

void talk_to_xboard(Position (*algorithm)(Position*))
{
    Position position;
    int side = NONE;
    setbuf(stdout, NULL);
    char command[256];
    while (fgets(command, 256, stdin) == command)
    {
        if (strncmp(command, "protover", 8) == 0)
        {
            xboard_protover();
        }
        else if (strncmp(command, "rejected", 8) == 0)
        {
            xboard_rejected();
        }
        else if (strncmp(command, "new", 3) == 0)
        {
            xboard_new(&position, &side);
        }
        else if (strncmp(command, "quit", 4) == 0)
        {
            xboard_quit();
        }
        else if (strncmp(command, "force", 5) == 0)
        {
            xboard_force(&side);
        }
        else if (strncmp(command, "go", 2) == 0)
        {
            xboard_go(&position, &side, algorithm);
        }
        else if (strncmp(command, "playother", 9) == 0)
        {
            xboard_playother(&position, &side);
        }
        else if (strncmp(command, "usermove", 8) == 0)
        {
            xboard_usermove(&position, command + 9, &side, algorithm);
        }
        else if (strncmp(command, "setboard", 8) == 0)
        {
            xboard_setboard(&position, command + 9, &side, algorithm);
        }
    }
}

void xboard_force(int* side)
{
    *side = NONE;
}

void xboard_go(Position* position, int* side, Position (*algorithm)(Position*))
{
    *side = position->player;
    if (!game_over(position))
    {
        *position = (*algorithm)(position);
        printf("move ");
        print_move(&position->move);
        printf("\n");
    }
}

void xboard_new(Position* position, int* side)
{
    char fen[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -";
    initialize_position(position, fen);
    *side = BLACK;
}

void xboard_playother(Position* position, int* side)
{
    *side = -position->player;
}

void xboard_protover(void)
{
    printf("feature colors=0\n");
    printf("feature playother=1\n");
    printf("feature setboard=1\n");
    printf("feature sigint=0\n");
    printf("feature usermove=1\n");
    printf("feature done=1\n");
}

void xboard_quit(void)
{
    exit(0);
}

void xboard_rejected(void)
{
    xboard_quit();
}

void xboard_setboard(Position* position, char fen[], int* side, Position
    (*algorithm)(Position*))
{
    initialize_position(position, fen);
    if (position->player == *side)
    {
        xboard_go(position, side, algorithm);
    }
}

void xboard_usermove(Position* position, char* usermove, int* side,
    Position (*algorithm)(Position*))
{
    int file1 = usermove[0] - 96;
    int rank1 = 58 - usermove[1];
    int file2 = usermove[2] - 96;
    int rank2 = 58 - usermove[3];
    int origin = 10 * rank1 + file1;
    int target = 10 * rank2 + file2;
    int promotion = NONE;
    switch (usermove[4])
    {
    case 'q':
        promotion = position->player * WHITE_QUEEN;
        break;
    case 'b':
        promotion = position->player * WHITE_BISHOP;
        break;
    case 'n':
        promotion = position->player * WHITE_KNIGHT;
        break;
    case 'r':
        promotion = position->player * WHITE_ROOK;
    }
    PositionList position_list;
    generate_moves(position, &position_list);
    for (int i = 0; i < position_list.count; i++)
    {
        Position* child = position_list.positions + i;
        if (child->move.origin == origin && child->move.target == target
            && child->move.promotion == promotion)
        {
            *position = *child;
            break;
        }
    }
    if (position->player == *side)
    {
        xboard_go(position, side, algorithm);
    }
}
