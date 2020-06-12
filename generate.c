#include "generate.h"
#include "position.h"

int attacked(Position* position, int target, int attacker)
{
    if (attacked_by_king(position, target, attacker))
    {
        return 1;
    }
    if (attacked_by_queen(position, target, attacker))
    {
        return 1;
    }
    if (attacked_by_bishop(position, target, attacker))
    {
        return 1;
    }
    if (attacked_by_knight(position, target, attacker))
    {
        return 1;
    }
    if (attacked_by_rook(position, target, attacker))
    {
        return 1;
    }
    if (attacked_by_pawn(position, target, attacker))
    {
        return 1;
    }
    return 0;
}

int attacked_by_bishop(Position* position, int target, int attacker)
{
    for (int i = 0; i < 4; i++)
    {
        int origin = target - bishop_displacements[i];
        while (position->board[origin] == EMPTY)
        {
            origin -= bishop_displacements[i];
        }
        if (attacker * position->board[origin] == WHITE_BISHOP)
        {
            return 1;
        }
    }
    return 0;
}

int attacked_by_king(Position* position, int target, int attacker)
{
    for (int i = 0; i < 8; i++)
    {
        int origin = target - king_displacements[i];
        if (attacker * position->board[origin] == WHITE_KING)
        {
            return 1;
        }
    }
    return 0;
}

int attacked_by_knight(Position* position, int target, int attacker)
{
    for (int i = 0; i < 8; i++)
    {
        int origin = target - knight_displacements[i];
        if (attacker * position->board[origin] == WHITE_KNIGHT)
        {
            return 1;
        }
    }
    return 0;
}

int attacked_by_pawn(Position* position, int target, int attacker)
{
    for (int i = 0; i < 2; i++)
    {
        int origin = target - attacker * pawn_displacements[i];
        if (attacker * position->board[origin] == WHITE_PAWN)
        {
            return 1;
        }
    }
    return 0;
}

int attacked_by_queen(Position* position, int target, int attacker)
{
    for (int i = 0; i < 8; i++)
    {
        int origin = target - queen_displacements[i];
        while (position->board[origin] == EMPTY)
        {
            origin -= queen_displacements[i];
        }
        if (attacker * position->board[origin] == WHITE_QUEEN)
        {
            return 1;
        }
    }
    return 0;
}

int attacked_by_rook(Position* position, int target, int attacker)
{
    for (int i = 0; i < 4; i++)
    {
        int origin = target - rook_displacements[i];
        while (position->board[origin] == EMPTY)
        {
            origin -= rook_displacements[i];
        }
        if (attacker * position->board[origin] == WHITE_ROOK)
        {
            return 1;
        }
    }
    return 0;
}

int bishop_displacements[] = {-11, -9, 9, 11};

int black_kingside_castling(Position* position)
{
    return position->castling[2] && position->board[26] == EMPTY
        && position->board[27] == EMPTY && !attacked(position, 25, WHITE)
        && !attacked(position, 26, WHITE);
}

int black_queenside_castling(Position* position)
{
    return position->castling[3] && position->board[24] == EMPTY
        && position->board[23] == EMPTY && position->board[22] == EMPTY
        && !attacked(position, 25, WHITE) && !attacked(position, 24, WHITE);
}

int capturable(Position* position, int square)
{
    int piece = position->player * position->board[square];
    return piece <= BLACK_PAWN && piece >= BLACK_KING;
}

int capturable_or_empty(Position* position, int square)
{
    int piece = position->player * position->board[square];
    return piece <= EMPTY && piece >= BLACK_KING;
}

int check(Position* position, int defender)
{
    return (defender == WHITE
        && attacked(position, position->white_king, BLACK))
        || (defender == BLACK
        && attacked(position, position->black_king, WHITE));
}

int double_step(Position* position, int square)
{
    return (position->player == WHITE && square / 10 == 8)
        || (position->player == BLACK && square / 10 == 3);
}

void generate_bishop_moves(Position* position, int origin,
    PositionList* position_list)
{
    for (int i = 0; i < 4; i++)
    {
        int target = origin + bishop_displacements[i];
        while (position->board[target] == EMPTY)
        {
            Position* copy = position_list->positions + position_list->count;
            make_move(position, origin, target, NONE, copy);
            if (legal(copy))
            {
                position_list->count++;
            }
            target += bishop_displacements[i];
        }
        if (capturable(position, target))
        {
            Position* copy = position_list->positions + position_list->count;
            make_move(position, origin, target, NONE, copy);
            if (legal(copy))
            {
                position_list->count++;
            }
        }
    }
}

void generate_king_moves(Position* position, int origin,
    PositionList* position_list)
{
    for (int i = 0; i < 8; i++)
    {
        int target = origin + king_displacements[i];
        if (capturable_or_empty(position, target))
        {
            Position* copy = position_list->positions + position_list->count;
            make_move(position, origin, target, NONE, copy);
            if (legal(copy))
            {
                position_list->count++;
            }
        }
    }
    // castling
    if (position->player == WHITE)
    {
        if (white_kingside_castling(position))
        {
            Position* copy = position_list->positions + position_list->count;
            make_move(position, 95, 97, NONE, copy);
            copy->board[96] = WHITE_ROOK;
            copy->board[98] = EMPTY;
            if (legal(copy))
            {
                position_list->count++;
            }
        }
        if (white_queenside_castling(position))
        {
            Position* copy = position_list->positions + position_list->count;
            make_move(position, 95, 93, NONE, copy);
            copy->board[94] = WHITE_ROOK;
            copy->board[91] = EMPTY;
            if (legal(copy))
            {
                position_list->count++;
            }
        }
    }
    else
    {
        if (black_kingside_castling(position))
        {
            Position* copy = position_list->positions + position_list->count;
            make_move(position, 25, 27, NONE, copy);
            copy->board[26] = BLACK_ROOK;
            copy->board[28] = EMPTY;
            if (legal(copy))
            {
                position_list->count++;
            }
        }
        if (black_queenside_castling(position))
        {
            Position* copy = position_list->positions + position_list->count;
            make_move(position, 25, 23, NONE, copy);
            copy->board[24] = BLACK_ROOK;
            copy->board[21] = EMPTY;
            if (legal(copy))
            {
                position_list->count++;
            }
        }
    }
}

void generate_knight_moves(Position* position, int origin,
    PositionList* position_list)
{
    for (int i = 0; i < 8; i++)
    {
        int target = origin + knight_displacements[i];
        if (capturable_or_empty(position, target))
        {
            Position* copy = position_list->positions + position_list->count;
            make_move(position, origin, target, NONE, copy);
            if (legal(copy))
            {
                position_list->count++;
            }
        }
    }
}

void generate_moves(Position* position, PositionList* position_list)
{
    position_list->count = 0;
    for (int i = 0; i < 64; i++)
    {
        int origin = long_index[i];
        switch (position->player * position->board[origin])
        {
        case WHITE_KING:
            generate_king_moves(position, origin, position_list);
            break;
        case WHITE_QUEEN:
            generate_queen_moves(position, origin, position_list);
            break;
        case WHITE_BISHOP:
            generate_bishop_moves(position, origin, position_list);
            break;
        case WHITE_KNIGHT:
            generate_knight_moves(position, origin, position_list);
            break;
        case WHITE_ROOK:
            generate_rook_moves(position, origin, position_list);
            break;
        case WHITE_PAWN:
            generate_pawn_moves(position, origin, position_list);
        }
    }
}

void generate_pawn_moves(Position* position, int origin,
    PositionList* position_list)
{
    // captures
    for (int i = 0; i < 2; i++)
    {
        int target = origin + position->player * pawn_displacements[i];
        if (capturable(position, target))
        {
            if (promotion(position, target))
            {
                for (int promotion = WHITE_QUEEN; promotion >= WHITE_ROOK;
                    promotion--)
                {
                    Position* copy = position_list->positions
                        + position_list->count;
                    make_move(position, origin, target,
                        position->player * promotion, copy);
                    if (legal(copy))
                    {
                        position_list->count++;
                    }
                }
            }
            else
            {
                Position* copy = position_list->positions + position_list->count;
                make_move(position, origin, target, NONE, copy);
                if (legal(copy))
                {
                    position_list->count++;
                }
            }
        }
        // en passant
        else if (target == position->en_passant)
        {
            Position* copy = position_list->positions + position_list->count;
            make_move(position, origin, target, NONE, copy);
            copy->board[target + 10 * position->player] = EMPTY;
            if (legal(copy))
            {
                position_list->count++;
            }
        }
    }
    // non captures
    int target = origin - 10 * position->player;
    if (position->board[target] == EMPTY)
    {
        if (promotion(position, target))
        {
            for (int promotion = WHITE_QUEEN; promotion >= WHITE_ROOK;
                promotion--)
            {
                Position* copy = position_list->positions
                    + position_list->count;
                make_move(position, origin, target,
                    position->player * promotion, copy);
                if (legal(copy))
                {
                    position_list->count++;
                }
            }
        }
        else
        {
            Position* copy = position_list->positions + position_list->count;
            make_move(position, origin, target, NONE, copy);
            if (legal(copy))
            {
                position_list->count++;
            }
            // double step
            if (double_step(position, origin))
            {
                int target2 = target - 10 * position->player;
                if (position->board[target2] == EMPTY)
                {
                    Position* copy = position_list->positions
                        + position_list->count;
                    make_move(position, origin, target2, NONE, copy);
                    copy->en_passant = target;
                    if (legal(copy))
                    {
                        position_list->count++;
                    }
                }
            }
        }
    }
}

void generate_queen_moves(Position* position, int origin,
    PositionList* position_list)
{
    for (int i = 0; i < 8; i++)
    {
        int target = origin + queen_displacements[i];
        while (position->board[target] == EMPTY)
        {
            Position* copy = position_list->positions + position_list->count;
            make_move(position, origin, target, NONE, copy);
            if (legal(copy))
            {
                position_list->count++;
            }
            target += queen_displacements[i];
        }
        if (capturable(position, target))
        {
            Position* copy = position_list->positions + position_list->count;
            make_move(position, origin, target, NONE, copy);
            if (legal(copy))
            {
                position_list->count++;
            }
        }
    }
}

void generate_rook_moves(Position* position, int origin,
    PositionList* position_list)
{
    for (int i = 0; i < 4; i++)
    {
        int target = origin + rook_displacements[i];
        while (position->board[target] == EMPTY)
        {
            Position* copy = position_list->positions + position_list->count;
            make_move(position, origin, target, NONE, copy);
            if (legal(copy))
            {
                position_list->count++;
            }
            target += rook_displacements[i];
        }
        if (capturable(position, target))
        {
            Position* copy = position_list->positions + position_list->count;
            make_move(position, origin, target, NONE, copy);
            if (legal(copy))
            {
                position_list->count++;
            }
        }
    }
}

int king_displacements[] = {-11, -10, -9, -1, 1, 9, 10, 11};

int knight_displacements[] = {-21, -19, -12, -8, 8, 12, 19, 21};

int legal(Position* position)
{
    return !check(position, -position->player);
}

void make_move(Position* position, int origin, int target, int promotion,
    Position* copy)
{
    // copy position
    *copy = *position;
    // move piece
    if (promotion == NONE)
    {
        copy->board[target] = copy->board[origin];
    }
    else
    {
        copy->board[target] = promotion;
    }
    copy->board[origin] = EMPTY;
    // switch player
    copy->player = -copy->player;
    // update castling rights
    if (origin == 95 || origin == 98 || target == 98)
    {
        copy->castling[0] = 0;
    }
    if (origin == 95 || origin == 91 || target == 91)
    {
        copy->castling[1] = 0;
    }
    if (origin == 25 || origin == 28 || target == 28)
    {
        copy->castling[2] = 0;
    }
    if (origin == 25 || origin == 21 || target == 21)
    {
        copy->castling[3] = 0;
    }
    // delete earlier en passant target
    copy->en_passant = -1;
    // update halfmove clock
    if (position->board[origin] == position->player
        || position->board[target] != EMPTY)
    {
        copy->halfmove_clock = 0;
    }
    else
    {
        copy->halfmove_clock++;
    }
    // update king posiitons
    if (origin == position->white_king)
    {
        copy->white_king = target;
    }
    else if (origin == position->black_king)
    {
        copy->black_king = target;
    }
    // set move
    copy->move.origin = origin;
    copy->move.target = target;
    copy->move.promotion = promotion;
}

int pawn_displacements[] = {-11, -9};

int promotion(Position* position, int square)
{
    return (position->player == WHITE && square / 10 == 2)
        || (position->player == BLACK && square / 10 == 9);
}

int queen_displacements[] = {-11, -10, -9, -1, 1, 9, 10, 11};

int rook_displacements[] = {-10, -1, 1, 10};

int white_kingside_castling(Position* position)
{
    return position->castling[0] && position->board[96] == EMPTY
        && position->board[97] == EMPTY && !attacked(position, 95, BLACK)
        && !attacked(position, 96, BLACK);
}

int white_queenside_castling(Position* position)
{
    return position->castling[1] && position->board[94] == EMPTY
        && position->board[93] == EMPTY && position->board[92] == EMPTY
        && !attacked(position, 95, BLACK) && !attacked(position, 94, BLACK);
}
