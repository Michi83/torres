#include <stdio.h>
#include "torres.h"

int bishop_displacements[] = {-11, -9, 9, 11};

int king_displacements[] = {-11, -10, -9, -1, 1, 9, 10, 11};

int knight_displacements[] = {-21, -19, -12, -8, 8, 12, 19, 21};

int pawn_displacements[] = {-11, -9};

int queen_displacements[] = {-11, -10, -9, -1, 1, 9, 10, 11};

int rook_displacements[] = {-10, -1, 1, 10};

void add_move(MoveList* move_list, int origin, int target, int promotion,
    int special, Position* position)
{
    Move* move = move_list->moves + move_list->count;
    move->capture = position->board[target];
    move->castling[0] = position->castling[0];
    move->castling[1] = position->castling[1];
    move->castling[2] = position->castling[2];
    move->castling[3] = position->castling[3];
    move->en_passant = position->en_passant;
    move->origin = origin;
    move->promotion = promotion;
    move->special = special;
    move->target = target;
    move_list->count++;
}

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
        while (empty(position, origin))
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
        while (empty(position, origin))
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
        while (empty(position, origin))
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

int black_kingside_castling(Position* position)
{
    return position->castling[2] && empty(position, 26) && empty(position, 27)
        && !attacked(position, 25, WHITE) && !attacked(position, 26, WHITE);
}

int black_queenside_castling(Position* position)
{
    return position->castling[3] && empty(position, 24) && empty(position, 23)
        && empty(position, 22) && !attacked(position, 25, WHITE)
        && !attacked(position, 24, WHITE);
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

int empty(Position* position, int square)
{
    return position->board[square] == EMPTY;
}

void generate_bishop_moves(Position* position, int origin, MoveList* move_list)
{
    for (int i = 0; i < 4; i++)
    {
        int target = origin + bishop_displacements[i];
        while (empty(position, target))
        {
            add_move(move_list, origin, target, NONE, NONE, position);
            target += bishop_displacements[i];
        }
        if (capturable(position, target))
        {
            add_move(move_list, origin, target, NONE, NONE, position);
        }
    }
}

void generate_king_moves(Position* position, int origin, MoveList* move_list)
{
    for (int i = 0; i < 8; i++)
    {
        int target = origin + king_displacements[i];
        if (capturable_or_empty(position, target))
        {
            add_move(move_list, origin, target, NONE, NONE, position);
        }
    }
    // castling
    if (position->player == WHITE)
    {
        if (white_kingside_castling(position))
        {
            add_move(move_list, 95, 97, NONE, WHITE_KINGSIDE_CASTLING,
                position);
        }
        if (white_queenside_castling(position))
        {
            add_move(move_list, 95, 93, NONE, WHITE_QUEENSIDE_CASTLING,
                position);
        }
    }
    else
    {
        if (black_kingside_castling(position))
        {
            add_move(move_list, 25, 27, NONE, BLACK_KINGSIDE_CASTLING,
                position);
        }
        if (black_queenside_castling(position))
        {
            add_move(move_list, 25, 23, NONE, BLACK_QUEENSIDE_CASTLING,
                position);
        }
    }
}

void generate_knight_moves(Position* position, int origin, MoveList* move_list)
{
    for (int i = 0; i < 8; i++)
    {
        int target = origin + knight_displacements[i];
        if (capturable_or_empty(position, target))
        {
            add_move(move_list, origin, target, NONE, NONE, position);
        }
    }
}

void generate_moves(Position* position, MoveList* move_list)
{
    move_list->count = 0;
    for (int i = 0; i < 64; i++)
    {
        int origin = long_index[i];
        if (movable(position, origin))
        {
            switch (position->board[origin])
            {
            case WHITE_KING:
            case BLACK_KING:
                generate_king_moves(position, origin, move_list);
                break;
            case WHITE_QUEEN:
            case BLACK_QUEEN:
                generate_queen_moves(position, origin, move_list);
                break;
            case WHITE_BISHOP:
            case BLACK_BISHOP:
                generate_bishop_moves(position, origin, move_list);
                break;
            case WHITE_KNIGHT:
            case BLACK_KNIGHT:
                generate_knight_moves(position, origin, move_list);
                break;
            case WHITE_ROOK:
            case BLACK_ROOK:
                generate_rook_moves(position, origin, move_list);
                break;
            case WHITE_PAWN:
            case BLACK_PAWN:
                generate_pawn_moves(position, origin, move_list);
            }
        }
    }
}

void generate_pawn_moves(Position* position, int origin, MoveList* move_list)
{
    // captures
    for (int i = 0; i < 2; i++)
    {
        int target = origin + position->player * pawn_displacements[i];
        if (capturable(position, target))
        {
            if (promotion(position, target))
            {
                add_move(move_list, origin, target,
                    position->player * WHITE_QUEEN, NONE, position);
                add_move(move_list, origin, target,
                    position->player * WHITE_BISHOP, NONE, position);
                add_move(move_list, origin, target,
                    position->player * WHITE_KNIGHT, NONE, position);
                add_move(move_list, origin, target,
                    position->player * WHITE_ROOK, NONE, position);
            }
            else
            {
                add_move(move_list, origin, target, NONE, NONE, position);
            }
        }
        // en passant
        else if (target == position->en_passant)
        {
            add_move(move_list, origin, target, NONE, EN_PASSANT, position);
        }
    }
    // non captures
    int target = origin - 10 * position->player;
    if (empty(position, target))
    {
        if (promotion(position, target))
        {
            add_move(move_list, origin, target, position->player * WHITE_QUEEN,
                NONE, position);
            add_move(move_list, origin, target, position->player * WHITE_BISHOP,
                NONE, position);
            add_move(move_list, origin, target, position->player * WHITE_KNIGHT,
                NONE, position);
            add_move(move_list, origin, target, position->player * WHITE_ROOK,
                NONE, position);
        }
        else
        {
            add_move(move_list, origin, target, NONE, NONE, position);
            // double step
            if (double_step(position, origin))
            {
                target -= 10 * position->player;
                if (empty(position, target))
                {
                    add_move(move_list, origin, target, NONE, DOUBLE_STEP,
                        position);
                }
            }
        }
    }
}

void generate_queen_moves(Position* position, int origin, MoveList* move_list)
{
    for (int i = 0; i < 8; i++)
    {
        int target = origin + queen_displacements[i];
        while (empty(position, target))
        {
            add_move(move_list, origin, target, NONE, NONE, position);
            target += queen_displacements[i];
        }
        if (capturable(position, target))
        {
            add_move(move_list, origin, target, NONE, NONE, position);
        }
    }
}

void generate_rook_moves(Position* position, int origin, MoveList* move_list)
{
    for (int i = 0; i < 4; i++)
    {
        int target = origin + rook_displacements[i];
        while (empty(position, target))
        {
            add_move(move_list, origin, target, NONE, NONE, position);
            target += rook_displacements[i];
        }
        if (capturable(position, target))
        {
            add_move(move_list, origin, target, NONE, NONE, position);
        }
    }
}

int legal(Position* position)
{
    return !check(position, -position->player);
}

void make_move(Position* position, Move* move)
{
    int origin = move->origin;
    int target = move->target;
    // move piece
    if (move->promotion == NONE)
    {
        position->board[target] = position->board[origin];
    }
    else
    {
        position->board[target] = move->promotion;
    }
    position->board[origin] = EMPTY;
    // apply move special
    switch (move->special)
    {
    case EN_PASSANT:
        position->board[target + 10 * position->player] = EMPTY;
        break;
    case WHITE_KINGSIDE_CASTLING:
        position->board[96] = WHITE_ROOK;
        position->board[98] = EMPTY;
        break;
    case WHITE_QUEENSIDE_CASTLING:
        position->board[94] = WHITE_ROOK;
        position->board[91] = EMPTY;
        break;
    case BLACK_KINGSIDE_CASTLING:
        position->board[26] = BLACK_ROOK;
        position->board[28] = EMPTY;
        break;
    case BLACK_QUEENSIDE_CASTLING:
        position->board[24] = BLACK_ROOK;
        position->board[21] = EMPTY;
    }
    // set castling rights
    if (origin == 95 || origin == 98 || target == 98)
    {
        position->castling[0] = 0;
    }
    if (origin == 95 || origin == 91 || target == 91)
    {
        position->castling[1] = 0;
    }
    if (origin == 25 || origin == 28 || target == 28)
    {
        position->castling[2] = 0;
    }
    if (origin == 25 || origin == 21 || target == 21)
    {
        position->castling[3] = 0;
    }
    // set en passant rights
    if (move->special == DOUBLE_STEP)
    {
        position->en_passant = target + 10 * position->player;
    }
    else
    {
        position->en_passant = -1;
    }
    // update king posiitons
    if (origin == position->white_king)
    {
        position->white_king = target;
    }
    else if (origin == position->black_king)
    {
        position->black_king = target;
    }
    // switch player
    position->player *= -1;
}

int movable(Position* position, int square)
{
    int piece = position-> player * position->board[square];
    return piece >= WHITE_PAWN && piece <= WHITE_KING;
}

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

int promotion(Position* position, int square)
{
    return (position->player == WHITE && square / 10 == 2)
        || (position->player == BLACK && square / 10 == 9);
}

void unmake_move(Position* position, Move* move)
{
    int origin = move->origin;
    int target = move->target;
    // switch player
    position->player *= -1;
    // restore king posiitons
    if (target == position->white_king)
    {
        position->white_king = origin;
    }
    else if (target == position->black_king)
    {
        position->black_king = origin;
    }
    // restore en passant rights
    position->en_passant = move->en_passant;
    // restore castling rights
    position->castling[0] = move->castling[0];
    position->castling[1] = move->castling[1];
    position->castling[2] = move->castling[2];
    position->castling[3] = move->castling[3];
    // undo move special
    switch (move->special)
    {
    case EN_PASSANT:
        position->board[target + 10 * position->player] = -position->player;
        break;
    case WHITE_KINGSIDE_CASTLING:
        position->board[98] = WHITE_ROOK;
        position->board[96] = EMPTY;
        break;
    case WHITE_QUEENSIDE_CASTLING:
        position->board[91] = WHITE_ROOK;
        position->board[94] = EMPTY;
        break;
    case BLACK_KINGSIDE_CASTLING:
        position->board[28] = BLACK_ROOK;
        position->board[26] = EMPTY;
        break;
    case BLACK_QUEENSIDE_CASTLING:
        position->board[21] = BLACK_ROOK;
        position->board[24] = EMPTY;
        break;
    }
    // move piece
    if (move->promotion == NONE)
    {
        position->board[origin] = position->board[target];
    }
    else
    {
        position->board[origin] = position->player;
    }
    position->board[target] = move->capture;
}

int white_kingside_castling(Position* position)
{
    return position->castling[0] && empty(position, 96) && empty(position, 97)
        && !attacked(position, 95, BLACK) && !attacked(position, 96, BLACK);
}

int white_queenside_castling(Position* position)
{
    return position->castling[1] && empty(position, 94) && empty(position, 93)
        && empty(position, 92) && !attacked(position, 95, BLACK)
        && !attacked(position, 94, BLACK);
}