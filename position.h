#pragma once

#define BLACK -1
#define BLACK_BISHOP -4
#define BLACK_KING -6
#define BLACK_KNIGHT -3
#define BLACK_PAWN -1
#define BLACK_QUEEN -5
#define BLACK_ROOK -2
#define EMPTY 0
#define LAVA -128
#define NONE 0
#define WHITE 1
#define WHITE_BISHOP 4
#define WHITE_KING 6
#define WHITE_KNIGHT 3
#define WHITE_PAWN 1
#define WHITE_QUEEN 5
#define WHITE_ROOK 2

typedef struct Move Move;
typedef struct Position Position;
typedef struct PositionList PositionList;

/*
Contains information about a move.

Fields:
- int origin: The origin square.
- int promotion: The promotion piece type or NONE.
- int target: The target square.
*/
struct Move
{
    int origin;
    int promotion;
    int target;
};

/*
Contains a game state.

Fields:
- int black_king: The black king's position.
- int board[120]: Internally, the board has 120 squares with a margin of "lava"
  squares like this:
  # # # # # # # # # #
  # # # # # # # # # #
  # r n b q k b n r #
  # p p p p p p p p #
  # . . . . . . . . #
  # . . . . . . . . #
  # . . . . . . . . #
  # . . . . . . . . #
  # P P P P P P P P #
  # R N B Q K B N R #
  # # # # # # # # # #
  # # # # # # # # # #
  This makes it easy to avoid moves over the edge of the board. There are two
  ways of numbering the squares: The "long" index numbers all squares from 0 to
  119, the "short" index numbers only the real squares from 0 to 63. Almost
  always, the long index is used. The array long_index maps short indices to
  long indices.
- int castling[4]: The castling rights, white kingside, white queenside, black
  kingside and black queenside.
- int en_passant: The target square of an en passant move or -1 if the preceding
  move was not a double step.
- int halfmove_clock: The number of halfmoves since the last pawn was moved or
  the last piece was captured.
- Move move: The move that led to this position.
- int player: The current player, WHITE or BLACK.
- int white_king: The white king's position.
*/
struct Position
{
    int black_king;
    int board[120];
    int castling[4];
    int en_passant;
    int halfmove_clock;
    Move move;
    int player;
    int white_king;
};

/*
A list of a variable number of positions.

Fields:
- int count: The number of positions currently in the list.
- Position positions[256]: The positions in the list.
*/
struct PositionList
{
    int count;
    Position positions[256];
};

/*
Initializes a position with a FEN string.

Parameters:
- Position* position: The position to be initialized.
- char* fen: The FEN string. There is no validity check, so make sure the string
  is valid before calling the function.
*/
void initialize_position(Position* position, char* fen);

/*
A mapping between short and long indices, see struct Position.
*/
extern int long_index[];

/*
Prints a move in "pure" algebraic notation. Ordinary moves are given as origin
and target without a delimiter, e.g. e2e4. For promotions the new piece type is
appended, e.g. e7e8q. For castling moves only the king's move is given, e.g.
e1g1.

Parameters:
- Move* move: The move to be printed.
*/
void print_move(Move* move);

/*
Prints an "ASCII art" board. Upper-case letters are white pieces, lower-case
letters are black pieces.

Parameters:
- Position* position: The position to be printed.
*/
void print_position(Position* position);
