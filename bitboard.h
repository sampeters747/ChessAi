#pragma once
#include <iostream>

using Bitboard = uint64_t;

namespace Bitboards {
    void init();
}

// Basic Bitboards
constexpr Bitboard EMPTY_BB = 0x0000000000000000;
constexpr Bitboard FULL_BB = 0xFFFFFFFFFFFFFFFF;

// Row Bitboards
constexpr Bitboard ROW_1 = 0x00000000000000FF;
constexpr Bitboard ROW_2 = ROW_1 << 8;
constexpr Bitboard ROW_3 = ROW_1 << 16;
constexpr Bitboard ROW_4 = ROW_1 << 24;
constexpr Bitboard ROW_5 = ROW_1 << 32;
constexpr Bitboard ROW_6 = ROW_1 << 40;
constexpr Bitboard ROW_7 = ROW_1 << 48;
constexpr Bitboard ROW_8 = ROW_1 << 56;

// File Bitboards
constexpr Bitboard A_FILE = 0x0101010101010101;
constexpr Bitboard B_FILE = 0x0202020202020202;
constexpr Bitboard C_FILE = 0x0404040404040404;
constexpr Bitboard D_FILE = 0x0808080808080808;
constexpr Bitboard E_FILE = 0x1010101010101010;
constexpr Bitboard F_FILE = 0x2020202020202020;
constexpr Bitboard G_FILE = 0x4040404040404040;
constexpr Bitboard H_FILE = 0x8080808080808080;

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
extern Bitboard PAWN_ATTACKS[64];
extern Bitboard ROOK_ATTACKS[64];
extern Bitboard KING_ATTACKS[64];


template<Direction D>
Bitboard moveOne(Bitboard bb);


void prettyPrintBB(Bitboard bb);

