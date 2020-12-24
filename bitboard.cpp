#include "bitboard.h"
#include "squares.h"

using namespace std;

Bitboard SQUARE_BB[64];
Bitboard PAWN_ATTACKS[64];
Bitboard ROOK_ATTACKS[64];
Bitboard KING_ATTACKS[64];


void Bitboards::init() {
    Square sq;
    Bitboard A1_BB = 0x1;
    for (sq = A1; sq <= H8; sq++) {
        SQUARE_BB[sq] = A1_BB << sq;
    }
}

template <Direction D>
Bitboard moveOne(Bitboard bb) {
    Bitboard result;
    if (D == NORTH | D == SOUTH) {
        result = bb << D;
    } else if (D == NORTH_EAST | D == SOUTH_EAST) {
        result = bb << D & ~A_FILE;
    } else if (D == NORTH_WEST | D == SOUTH_WEST) {
        result = bb << D & ~H_FILE;
    }
    return result;
}

void prettyPrintBB(Bitboard bb) {
    uint_fast64_t a = bb;
    constexpr unsigned int mask = 0b1;
    for (int j=63; j>=0; j--) {
        uint_fast64_t bit_position = 8*(j/8)+(7-j%8);
        if (a>>bit_position & mask) {
            std::cout << '1';
        } else {
            std::cout << '0';
        };
        if ((bit_position+1)%8==0) {
            std::cout << std::endl;
        } else {
            std::cout << ' ';
        }
    }
}