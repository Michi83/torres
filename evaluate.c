#include "torres.h"

int evaluate(Position* position)
{
    int score = 0;
    for (int i = 0; i < 64; i++)
    {
        int square = long_index[i];
        switch (position->board[square])
        {
        case WHITE_QUEEN:
            score += 900;
            break;
        case WHITE_BISHOP:
            score += 300;
            break;
        case WHITE_KNIGHT:
            score += 300;
            break;
        case WHITE_ROOK:
            score += 500;
            break;
        case WHITE_PAWN:
            score += 100;
            break;
        case BLACK_QUEEN:
            score -= 900;
            break;
        case BLACK_BISHOP:
            score -= 300;
            break;
        case BLACK_KNIGHT:
            score -= 300;
            break;
        case BLACK_ROOK:
            score -= 500;
            break;
        case BLACK_PAWN:
            score -= 100;
        }
    }
    return position->player * score;
}