#pragma once
#include <iostream>

using Bitboard = uint64_t;

namespace Bitboards {
    void init();
}

// Basic Bitboards
constexpr Bitboard EMPTY_BB = 0x0000000000000000;
constexpr Bitboard FULL_BB = 0xFFFFFFFFFFFFFFFF;

// Rank Bitboards
constexpr Bitboard RANK_1 = 0x00000000000000FF;
constexpr Bitboard RANK_2 = RANK_1 << 8;
constexpr Bitboard RANK_3 = RANK_1 << 16;
constexpr Bitboard RANK_4 = RANK_1 << 24;
constexpr Bitboard RANK_5 = RANK_1 << 32;
constexpr Bitboard RANK_6 = RANK_1 << 40;
constexpr Bitboard RANK_7 = RANK_1 << 48;
constexpr Bitboard RANK_8 = RANK_1 << 56;
constexpr Bitboard RANKS[8] = {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8};

// File Bitboards
constexpr Bitboard A_FILE = 0x0101010101010101;
constexpr Bitboard B_FILE = 0x0202020202020202;
constexpr Bitboard C_FILE = 0x0404040404040404;
constexpr Bitboard D_FILE = 0x0808080808080808;
constexpr Bitboard E_FILE = 0x1010101010101010;
constexpr Bitboard F_FILE = 0x2020202020202020;
constexpr Bitboard G_FILE = 0x4040404040404040;
constexpr Bitboard H_FILE = 0x8080808080808080;
constexpr Bitboard FILES[8] = {A_FILE, B_FILE, C_FILE, D_FILE, E_FILE, F_FILE, G_FILE, H_FILE};

// Other Bitboards
constexpr Bitboard EDGE_BB = A_FILE | H_FILE | RANK_1 | RANK_8;
constexpr Bitboard NOT_EDGE_BB = ~EDGE_BB;

// Declaring Directions
enum Direction : int {
    NORTH = 8,
    SOUTH = -8,
    EAST = 1,
    WEST = -1,
    SOUTH_EAST = -7,
    SOUTH_WEST = -9,
    NORTH_WEST = 7,
    NORTH_EAST = 9,
};

// Declaring arrays of bitboards that we'll initilize later
extern Bitboard SQUARE_BB[64];
extern Bitboard FORWARD_DIAG_BB[15];
extern Bitboard BACKWARD_DIAG_BB[15];

extern Bitboard PAWN_ATTACKS[2][64];
extern Bitboard ROOK_ATTACKS[64];
extern Bitboard BISHOP_ATTACKS[64];
extern Bitboard KING_ATTACKS[64];
extern Bitboard QUEEN_ATTACKS[64];
extern Bitboard KNIGHT_ATTACKS[64];

// Shifts all the bits in a bitboard over one space in any direction
template<Direction D>
Bitboard moveOne(Bitboard bb);

void prettyPrintBB(Bitboard bb);

