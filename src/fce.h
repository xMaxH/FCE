#ifndef FCE_H
#define FCE_H
#include "stdint.h"
#include <cstdint>
#include <stdint.h>
#include <stdbool.h>
#define QUEEN_WORTH 9
#define ROOK_WORTH 5
#define PAWN_WORTH 1
#define BISHOP_WORTH 3
#define KNIGHT_WORTH 3
#define BOARD_SIZE_88  64
#define BOARD_COLS 8
#define BOARD_ROWS 8

enum color{
    WHITE = 0,
    BLACK = 1
};

enum token {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

struct move {
    uint8_t from;
    uint8_t to;
};

struct figure {
    enum token token;
    enum color color;
    int rows;
    int cols;
};

struct state {
    // all the quares of the board, pointer to the corresponding piece/square
    uint8_t board[64];
    // store pieces in a list which makes move generation and searching for specific pieces easier
    struct figure figures[32];
    int16_t eval;
    enum color side;
    bool white_queenside_castle;
    bool white_kingside_castle;
    bool black_kingside_castle;
    bool black_queenside_castle;
    uint16_t move;
    int moves_since_capture_or_pawn;
    struct square *en_passant;
};

void fce_error(const char *message);

struct state *state_make();
void print_fce_board(struct state *state);
void state_init(struct state *state);
struct state *move_piece();
void read_fen_save_to_state(const char* fen, struct state* state);
char get_symbol(enum token token);
char *get_bool(bool vals);
char get_rows(int rows);
char get_cols(int cols);
char *get_color(enum color color);
#endif