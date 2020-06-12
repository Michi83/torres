#include <stdio.h>
#include <string.h>
#include "position.h"

void initialize_position(Position* position, char fen[])
{
    memset(position->board, LAVA, 120 * sizeof (int));
    position->castling[0] = 0;
    position->castling[1] = 0;
    position->castling[2] = 0;
    position->castling[3] = 0;
    position->halfmove_clock = 0;
    position->move.origin = 0;
    position->move.target = 0;
    position->move.promotion = NONE;
    int rank = 0;
    int file = 0;
    int i;
    for (i = 0; fen[i] != ' '; i++)
    {
        int square = long_index[8 * rank + file];
        switch (fen[i])
        {
        case 'K':
            position->board[square] = WHITE_KING;
            position->white_king = square;
            file++;
            break;
        case 'Q':
            position->board[square] = WHITE_QUEEN;
            file++;
            break;
        case 'B':
            position->board[square] = WHITE_BISHOP;
            file++;
            break;
        case 'N':
            position->board[square] = WHITE_KNIGHT;
            file++;
            break;
        case 'R':
            position->board[square] = WHITE_ROOK;
            file++;
            break;
        case 'P':
            position->board[square] = WHITE_PAWN;
            file++;
            break;
        case 'k':
            position->board[square] = BLACK_KING;
            position->black_king = square;
            file++;
            break;
        case 'q':
            position->board[square] = BLACK_QUEEN;
            file++;
            break;
        case 'b':
            position->board[square] = BLACK_BISHOP;
            file++;
            break;
        case 'n':
            position->board[square] = BLACK_KNIGHT;
            file++;
            break;
        case 'r':
            position->board[square] = BLACK_ROOK;
            file++;
            break;
        case 'p':
            position->board[square] = BLACK_PAWN;
            file++;
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
            for (int j = 0; j < fen[i] - 48; j++)
            {
                position->board[square + j] = EMPTY;
                file++;
            }
            break;
        case '/':
            rank++;
            file = 0;
        }
    }
    i++;
    switch (fen[i])
    {
    case 'w':
        position->player = WHITE;
        break;
    case 'b':
        position->player = BLACK;

    }
    i += 2;
    while (fen[i] != ' ')
    {
        switch (fen[i])
        {
        case 'K':
            position->castling[0] = 1;
            break;
        case 'Q':
            position->castling[1] = 1;
            break;
        case 'k':
            position->castling[2] = 1;
            break;
        case 'q':
            position->castling[3] = 1;
        }
        i++;
    }
    i++;
    if (fen[i] == '-')
    {
        position->en_passant = -1;
    }
    else
    {
        file = fen[i] - 97;
        rank = 56 - fen[i + 1];
        position->en_passant = 8 * rank + file;
    }
}

int long_index[64] =
{
    21, 22, 23, 24, 25, 26, 27, 28,
    31, 32, 33, 34, 35, 36, 37, 38,
    41, 42, 43, 44, 45, 46, 47, 48,
    51, 52, 53, 54, 55, 56, 57, 58,
    61, 62, 63, 64, 65, 66, 67, 68,
    71, 72, 73, 74, 75, 76, 77, 78,
    81, 82, 83, 84, 85, 86, 87, 88,
    91, 92, 93, 94, 95, 96, 97, 98
};

void print_move(Move* move)
{
    printf("%c", 96 + move->origin % 10);
    printf("%d", 10 - move->origin / 10);
    printf("%c", 96 + move->target % 10);
    printf("%d", 10 - move->target / 10);
    switch (move->promotion)
    {
    case WHITE_QUEEN:
    case BLACK_QUEEN:
        printf("q");
        break;
    case WHITE_BISHOP:
    case BLACK_BISHOP:
        printf("b");
        break;
    case WHITE_KNIGHT:
    case BLACK_KNIGHT:
        printf("n");
        break;
    case WHITE_ROOK:
    case BLACK_ROOK:
        printf("r");
    }
}

void print_position(Position* position)
{
    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0)
        {
            printf("# %d ", 8 - i / 8);
        }
        int square = long_index[i];
        int piece = position->board[square];
        switch (piece)
        {
        case WHITE_KING:
            printf("K ");
            break;
        case WHITE_QUEEN:
            printf("Q ");
            break;
        case WHITE_BISHOP:
            printf("B ");
            break;
        case WHITE_KNIGHT:
            printf("N ");
            break;
        case WHITE_ROOK:
            printf("R ");
            break;
        case WHITE_PAWN:
            printf("P ");
            break;
        case BLACK_KING:
            printf("k ");
            break;
        case BLACK_QUEEN:
            printf("q ");
            break;
        case BLACK_BISHOP:
            printf("b ");
            break;
        case BLACK_KNIGHT:
            printf("n ");
            break;
        case BLACK_ROOK:
            printf("r ");
            break;
        case BLACK_PAWN:
            printf("p ");
            break;
        case EMPTY:
            printf(". ");
        }
        if (i % 8 == 7)
        {
            printf("\n");
        }
    }
    printf("#   a b c d e f g h \n");
}
