#include <stdio.h>
#include <string.h>
#include "torres.h"

int game_over(Position* position)
{
    MoveList move_list;
    generate_moves(position, &move_list);
    for (int i = 0; i < move_list.count; i++)
    {
        Move* move = move_list.moves + i;
        make_move(position, move);
        if (legal(position))
        {
            unmake_move(position, move);
            return 0;
        }
        unmake_move(position, move);
    }
    return 1;
}

void xboard_go(Position* position, int verbose)
{
    if (!game_over(position))
    {
        Move move = iterative_deepening(position, 100, verbose);
        make_move(position, &move);
        printf("move ");
        print_move(&move);
        printf("\n");
        print_position(position);
    }
}

void xboard_usermove(Position* position, char* usermove)
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
        promotion = WHITE_QUEEN;
        break;
    case 'b':
        promotion = WHITE_BISHOP;
        break;
    case 'n':
        promotion = WHITE_KNIGHT;
        break;
    case 'r':
        promotion = WHITE_ROOK;
    }
    MoveList move_list;
    generate_moves(position, &move_list);
    for (int i = 0; i < move_list.count; i++)
    {
        Move move = move_list.moves[i];
        if (move.origin == origin && move.target == target
            && move.promotion == promotion)
        {
            make_move(position, &move);
            break;
        }
    }
    print_position(position);
}

int main(void)
{
    setbuf(stdout, NULL);
    int side = NONE;
    Position position;
    char fen[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -";
    int verbose = 0;
    char command[256];
    while (fgets(command, 256, stdin) == command)
    {
        if (strncmp(command, "protover", 8) == 0)
        {
            printf("feature colors=0\n");
            printf("feature playother=1\n");
            printf("feature setboard=1\n");
            printf("feature sigint=0\n");
            printf("feature usermove=1\n");
            printf("feature done=1\n");
        }
        else if (strncmp(command, "new", 3) == 0)
        {
            initialize_position(&position, fen);
            side = BLACK;
        }
        else if (strncmp(command, "quit", 4) == 0)
        {
            return 0;
        }
        else if (strncmp(command, "force", 5) == 0)
        {
            side = NONE;
        }
        else if (strncmp(command, "go", 2) == 0)
        {
            side = position.player;
            xboard_go(&position, verbose);
        }
        else if (strncmp(command, "playother", 9) == 0)
        {
            side = -position.player;
        }
        else if (strncmp(command, "usermove", 8) == 0)
        {
            xboard_usermove(&position, command + 9);
            if (side == position.player)
            {
                xboard_go(&position, verbose);
            }
        }
        else if (strncmp(command, "setboard", 8) == 0)
        {
            initialize_position(&position, command + 9);
        }
        else if (strncmp(command, "post", 4) == 0)
        {
            verbose = 1;
        }
        else if (strncmp(command, "nopost", 6) == 0)
        {
            verbose = 0;
        }
    }
    return 0;
}