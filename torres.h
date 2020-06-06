#pragma once

#define WHITE 1
#define BLACK -1
#define WHITE_KING 6
#define WHITE_QUEEN 5
#define WHITE_BISHOP 4
#define WHITE_KNIGHT 3
#define WHITE_ROOK 2
#define WHITE_PAWN 1
#define BLACK_KING -6
#define BLACK_QUEEN -5
#define BLACK_BISHOP -4
#define BLACK_KNIGHT -3
#define BLACK_ROOK -2
#define BLACK_PAWN -1
#define EMPTY 0
#define LAVA -128
#define NONE 0
#define DOUBLE_STEP 1
#define EN_PASSANT 2
#define WHITE_KINGSIDE_CASTLING 3
#define WHITE_QUEENSIDE_CASTLING 4
#define BLACK_KINGSIDE_CASTLING 5
#define BLACK_QUEENSIDE_CASTLING 6

typedef struct Move Move;
typedef struct MoveList MoveList;
typedef struct Position Position;

/*
Displacements for bishop moves.
*/
extern int bishop_displacements[];

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
Displacements for king moves.
*/
extern int king_displacements[];

/*
Displacements for knight moves.
*/
extern int knight_displacements[];

/*
A mapping between short and long indices, see struct Position.
*/
extern int long_index[];

/*
Displacements for pawn moves.
*/
extern int pawn_displacements[];

/*
Displacements for queen moves.
*/
extern int queen_displacements[];

/*
Displacements for rook moves.
*/
extern int rook_displacements[];

/*
Piece-square table for the white bishop.
*/
extern int white_bishop_table[];

/*
Piece-square table for the white king.
*/
extern int white_king_table[];

/*
Endgame piece-square table for the white king.
*/
extern int white_king_endgame_table[];

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

/*
Adds a move to a move list.

Parameters:
- MoveList* move_list: The move list to add the move to.
- int origin: The move's origin square.
- int target: The move's target square.
- int promotion: The piece to promote to. May be NONE.
- int special: Special rules to apply to the move. For values see struct Move.
- Position* position: A position from which additional information about the
  move is gathered.
*/
void add_move(MoveList* move_list, int origin, int target, int promotion,
    int special, Position* position);

/*
Checks if a square is attacked.

Parameters:
- Position* position: A position.
- int square: The square to be examined.
- int attacker: The attacker, WHITE or BLACK.

Returns: 1 if the square is attacked, 0 otherwise.
*/
int attacked(Position* position, int square, int attacker);

/*
Checks if a square is attacked by a bishop.

Parameters:
- Position* position: A position.
- int square: The square to be examined.
- int attacker: The attacker, WHITE or BLACK.

Returns: 1 if the square is attacked, 0 otherwise.
*/
int attacked_by_bishop(Position* position, int square, int attacker);

/*
Checks if a square is attacked by a king.

Parameters:
- Position* position: A position.
- int square: The square to be examined.
- int attacker: The attacker, WHITE or BLACK.

Returns: 1 if the square is attacked, 0 otherwise.
*/
int attacked_by_king(Position* position, int square, int attacker);

/*
Checks if a square is attacked by a knight.

Parameters:
- Position* position: A position.
- int square: The square to be examined.
- int attacker: The attacker, WHITE or BLACK.

Returns: 1 if the square is attacked, 0 otherwise.
*/
int attacked_by_knight(Position* position, int square, int attacker);

/*
Checks if a square is attacked by a pawn.

Parameters:
- Position* position: A position.
- int square: The square to be examined.
- int attacker: The attacker, WHITE or BLACK.

Returns: 1 if the square is attacked, 0 otherwise.
*/
int attacked_by_pawn(Position* position, int square, int attacker);

/*
Checks if a square is attacked by a queen.

Parameters:
- Position* position: A position.
- int square: The square to be examined.
- int attacker: The attacker, WHITE or BLACK.

Returns: 1 if the square is attacked, 0 otherwise.
*/
int attacked_by_queen(Position* position, int square, int attacker);

/*
Checks if a square is attacked by a rook.

Parameters:
- Position* position: A position.
- int square: The square to be examined.
- int attacker: The attacker, WHITE or BLACK.

Returns: 1 if the square is attacked, 0 otherwise.
*/
int attacked_by_rook(Position* position, int square, int attacker);

/*
Checks if black kingside castling is possible.

Parameters:
- Position* position: A position.

Returns: 1 if castling is possible, 0 otherwise.
*/
int black_kingside_castling(Position* position);

/*
Checks if black queenside castling is possible.

Parameters:
- Position* position: A position.

Returns: 1 if castling is possible, 0 otherwise.
*/
int black_queenside_castling(Position* position);

/*
Checks if a square is occupied by the current player's opponent.

Parameters:
- Position* position: A position.
- int square: The square to be examined.

Returns: 1 if the square is occupied by the current player's opponent, 0
otherwise.
*/
int capturable(Position* position, int square);

/*
Checks if a square is occupied by the current player's opponent or empty.

Parameters:
- Position* position: A position.
- int square: The square to be examined.

Returns: 1 if the square is occupied by the current player's opponent or empty,
0 otherwise.
*/
int capturable_or_empty(Position* position, int square);

/*
Checks if a player is in check.

Parameters:
- Position* position: A position.
- int defender: The defender, WHITE or BLACK.

Returns: 1 if the player is in check, 0 otherwise.
*/
int check(Position* position, int defender);

/*
Compares two moves.

Parameters:
Move* move1: A move.
Move* move2: Another move.

Returns: 1 if the moves have the same origin, target and promotion, 0 otherwise.
*/
int compare_moves(Move* move1, Move* move2);

/*
Checks if a square belongs to the current player's second rank and thus can be
the origin of a double step.

Parameters:
- Position* position: A position.
- int square: The square to be examined.

Returns: 1 if the square belongs to the current player's second rank, 0
otherwise.
*/
int double_step(Position* position, int square);

/*
Checks if a square is empty.

Parameters:
- Position* position: A position.
- int square: The square to be examined.

Returns: 1 if the square is empty, 0 otherwise.
*/
int empty(Position* position, int square);

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
Checks if the current player has legal moves.

Parameters:
- Position* position: The position to be examined.

Return: 1 if the current player doesn't have legal moves, 0 otherwise.
*/
int game_over(Position* position);

/*
Generates bishop moves from a square.

Parameters:
- Position* position: A position.
- int origin: The origin square.
- MoveList* move_list: A move list to add the moves to.
*/
void generate_bishop_moves(Position* position, int origin, MoveList* move_list);

/*
Generates king moves from a square.

Parameters:
- Position* position: A position.
- int origin: The origin square.
- MoveList* move_list: A move list to add the moves to.
*/
void generate_king_moves(Position* position, int origin, MoveList* move_list);

/*
Generates knight moves from a square.

Parameters:
- Position* position: A position.
- int origin: The origin square.
- MoveList* move_list: A move list to add the moves to.
*/
void generate_knight_moves(Position* position, int origin, MoveList* move_list);

/*
Generates moves for a position. Move generation is pseudo-legal, i.e. moves may
leave the king in check.

Parameters:
- Position* position: A position.
- int origin: The origin square.
- MoveList* move_list: A move list to add the moves to. Emptied automatically at
  the beginning.
*/
void generate_moves(Position* position, MoveList* move_list);

/*
Generates pawn moves from a square.

Parameters:
- Position* position: A position.
- int origin: The origin square.
- MoveList* move_list: A move list to add the moves to.
*/
void generate_pawn_moves(Position* position, int origin, MoveList* move_list);

/*
Generates queen moves from a square.

Parameters:
- Position* position: A position.
- int origin: The origin square.
- MoveList* move_list: A move list to add the moves to.
*/
void generate_queen_moves(Position* position, int origin, MoveList* move_list);

/*
Generates rook moves from a square.

Parameters:
- Position* position: A position.
- int origin: The origin square.
- MoveList* move_list: A move list to add the moves to.
*/
void generate_rook_moves(Position* position, int origin, MoveList* move_list);

/*
Initializes a position with a FEN string.

Parameters:
- Position* position: The position to be initialized.
- char fen[]: The FEN string. There is no validity check, so make sure the
  string is valid before calling the function.
*/
void initialize_position(Position* position, char* fen);

/*
Performs minimax searches of increasing depth.

Parameters:
- Position* position: The position to search.
- int min_time: The minimum time to be spent in centiseconds.
- int verbose: 1 if output is desired, 0 otherwise.

Returns: The best move found.
*/
Move iterative_deepening(Position* position, int min_time, int verbose);

/*
Checks if a position is legal, i.e. if the preceding move did not leave the king
in check.

Parameters:
- Position* position: The position to be examined.

Returns: 1 if the position is legal, 0 otherwise.
*/
int legal(Position* position);

/*
Makes a move in a position.

Parameters:
- Position* position: The position.
- Move* move: The move.
*/
void make_move(Position* position, Move* move);

/*
Performs a recursive minimax tree search with alpha-beta pruning.

Parameters:
- Position* position: The position to search.
- int depth: The search depth.
- int alpha: The alpha variable for alpha-beta pruning. Should be -200000 in the
  initial call.
- int beta: See above. Should be 200000 in the initial call.
- int* nodes: A counter that gets incremented by 1 for every node visited.
- Move* principal_variation: An array of Moves for the principal variation (i.e.
  the sequence of best moves) to be written to.

Returns: The positions score in centipawns. Positive if the current player has
an advantage, negative if they have a disadvantage.
*/
int minimax(Position* position, int depth, int alpha, int beta, int* nodes,
  Move* principal_variation);

/*
Checks if a square is occupied by the current player.

Parameters:
- Position* position: A position.
- int square: The square to be examined.

Returns: 1 if the square is occupied by the current player, 0 otherwise.
*/
int movable(Position* position, int square);

/*
Presorts a move list so that the presumed best moves can be searched first.

Parameters:
- MoveList* move_list: The move list to be sorted.
- Move* best_move: The presumed best move.
*/
void presort_moves(MoveList* move_list, Move* best_move);

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

/*
Checks if a square belongs to the current player's eighth rank and thus can be
the target of a pawn promotion.

Parameters:
- Position* position: A position.
- int square: The square to be examined.

Returns: 1 if the square belongs to the current player's eighth rank, 0
otherwise.
*/
int promotion(Position* position, int square);

/*
Retracts a move in a position.

Parameters:
- Position* position: The position.
- Move* move: The move.
*/
void unmake_move(Position* position, Move* move);

/*
Checks if white kingside castling is possible.

Parameters:
- Position* position: A position.

Returns: 1 if castling is possible, 0 otherwise.
*/
int white_kingside_castling(Position* position);

/*
Checks if white queenside castling is possible.

Parameters:
- Position* position: A position.

Returns: 1 if castling is possible, 0 otherwise.
*/
int white_queenside_castling(Position* position);

/*
Handles the "go" command of the xboard protocol.

Parameters:
- Position* position: A position.
- int verbose: 1 if output is desired, 0 otherwise.
*/
void xboard_go(Position* position, int verbose);

/*
Handles the "usermove" command of the xboard protocol.

Parameters:
- Position* position: A position.
- char* usermove: The usermove in "pure" algebraic notation.
*/
void xboard_usermove(Position* position, char* usermove);

/*
Contains information for making and retracting moves.

Fields:
- int capture: The piece captured by the move. May be EMPTY.
- int castling[4]: The castling rights before the move.
- int en_passant: The en passant target before the move.
- int origin: The origin square.
- int promotion: The promotion piece type or NONE.
- int special: Special rules to be applied. Possible values:
  - NONE
  - DOUBLE_STEP
  - EN_PASSANT
  - WHITE_KINGSIDE_CASTLING
  - WHITE_QUEENSIDE_CASTLING
  - BLACK_KINGSIDE_CASTLING
  - BLACK_QUEENSIDE_CASTLING
- int target: The target square.
*/
struct Move
{
    int capture;
    int castling[4];
    int en_passant;
    int origin;
    int promotion;
    int special;
    int target;
};

/*
A list of a variable number of moves.

Fields:
- int count: The number of moves currently in the list.
- Move moves[256]: The moves in the list.
*/
struct MoveList
{
    int count;
    Move moves[256];
};

/*
Contains the game state. Only one position should exist at runtime. During tree
search moves are made and retracted in it.

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
- int player: The current player, WHITE or BLACK.
- int white_king: The white king's position.
*/
struct Position
{
    int black_king;
    int board[120];
    int castling[4];
    int en_passant;
    int player;
    int white_king;
};