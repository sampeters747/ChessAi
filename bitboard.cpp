#include "bitboard.h"
#include "squares.h"
#include "colors.h"

using namespace std;

Bitboard SQUARE_BB[64];
Bitboard FORWARD_DIAG_BB[15];
Bitboard BACKWARD_DIAG_BB[15];

Bitboard PAWN_ATTACKS[2][64];
Bitboard ROOK_ATTACKS[64];
Bitboard BISHOP_ATTACKS[64];
Bitboard KING_ATTACKS[64];
Bitboard QUEEN_ATTACKS[64];
Bitboard KNIGHT_ATTACKS[64];


void Bitboards::init() {
    Square sq;
    Bitboard A1_BB = 0x1;
    // Populating SQUARE_BB array
    for (sq = A1; sq <= H8; sq++) {
        SQUARE_BB[sq] = A1_BB << sq;
    }

    // Populating FORWARD_DIAGONAL_BB and BACKWARD_DIAGONAL_BB arrays
    Bitboard forward_diagonal = 0x8040201008040201;
    Bitboard backward_diagonal = 0x102040810204080;
    Bitboard current_forward = forward_diagonal;
    Bitboard current_backward = backward_diagonal;
    for (int i=0; i<15; i++) {
        if (i < 7) {
            current_forward = moveOne<NORTH>(current_forward);
            current_backward = moveOne<NORTH>(current_backward);
        } else if (i == 7) {
            current_forward = forward_diagonal;
            current_backward = backward_diagonal;
        } else {
            current_forward = moveOne<SOUTH>(current_forward);
            current_backward = moveOne<SOUTH>(current_backward);
        }
        FORWARD_DIAG_BB[i] = current_forward;
        BACKWARD_DIAG_BB[i] = current_backward;
    }
    // Populating PAWN_ATTACKS array
    for (sq = A1; sq <= H8; sq++) {
        Bitboard current = SQUARE_BB[sq];
        // Calculating possible attacks if a white pawn was on square sq
        PAWN_ATTACKS[WHITE][sq] = moveOne<NORTH_WEST>(current) | moveOne<NORTH_EAST>(current);
        // Calculating possible attacks if a black pawn was on square sq
        PAWN_ATTACKS[BLACK][sq] = moveOne<SOUTH_WEST>(current) | moveOne<SOUTH_EAST>(current);
    }
    // Populating ROOK_ATTACKS array
    for (sq = A1; sq <= H8; sq++) {
        Bitboard current = SQUARE_BB[sq];
        Bitboard attacked;
        for (Bitboard rank: RANKS) {
            if (current & rank) {
                attacked = current | rank;
                break;
            }
        }
        for (Bitboard file: FILES) {
            if (current & file) {
                attacked = attacked | file;
                break;
            }
        }
        attacked = attacked & ~current;
        ROOK_ATTACKS[sq] = attacked;
    }
    
    // Populating BISHOP_ATTACKS array
    for (sq = A1; sq <= H8; sq++) {
        Bitboard current = SQUARE_BB[sq];
        Bitboard attacked;
        for (Bitboard fd: FORWARD_DIAG_BB) {
            if (current & fd) {
                attacked = current | fd;
                break;
            }
        }
        for (Bitboard bd: BACKWARD_DIAG_BB) {
            if (current & bd) {
                attacked = attacked | bd;
                break;
            }
        }
        attacked = attacked & ~current;
        BISHOP_ATTACKS[sq] = attacked;
    }
    
    // Populating KING_ATTACKS array
    for (sq = A1; sq <= H8; sq++) {
        Bitboard current = SQUARE_BB[sq];
        KING_ATTACKS[sq] = moveOne<NORTH>(current) |
                            moveOne<NORTH_EAST>(current) |
                            moveOne<EAST>(current) |
                            moveOne<SOUTH_EAST>(current) |
                            moveOne<SOUTH>(current) |
                            moveOne<SOUTH_WEST>(current) |
                            moveOne<WEST>(current) |
                            moveOne<NORTH_WEST>(current);   
    }

    // Populating QUEEN_ATTACKS array
    for (sq = A1; sq <= H8; sq++) {
        QUEEN_ATTACKS[sq] = ROOK_ATTACKS[sq] | BISHOP_ATTACKS[sq];
    }

    // Populating KNIGHT_ATTACKS array
    for (sq = A1; sq <= H8; sq++) {
        Bitboard current = SQUARE_BB[sq];
        KNIGHT_ATTACKS[sq] = moveOne<NORTH_EAST>(moveOne<NORTH>(current)) |
                            moveOne<NORTH_WEST>(moveOne<NORTH>(current)) |
                            moveOne<NORTH_EAST>(moveOne<EAST>(current)) |
                            moveOne<SOUTH_EAST>(moveOne<EAST>(current)) |
                            moveOne<SOUTH_EAST>(moveOne<SOUTH>(current)) |
                            moveOne<SOUTH_WEST>(moveOne<SOUTH>(current)) |
                            moveOne<NORTH_WEST>(moveOne<WEST>(current)) |
                            moveOne<SOUTH_WEST>(moveOne<WEST>(current));
    }
}

template <Direction D>
Bitboard moveOne(Bitboard bb) {
    Bitboard result;
    switch (D)
    {
    case NORTH:
        result = bb << NORTH;
        break;
    case SOUTH:
        result = bb >> -SOUTH;
        break;
    case EAST:
        result = bb << EAST & ~A_FILE;
        break;
    case WEST:
        result = bb >> -WEST & ~H_FILE;
        break;
    case NORTH_EAST:
        result = bb << NORTH_EAST & ~A_FILE;
        break;
    case SOUTH_EAST:
        result = bb >> -SOUTH_EAST & ~A_FILE;
        break;
    case NORTH_WEST:
        result = bb << NORTH_WEST & ~H_FILE;
        break;
    case SOUTH_WEST:
        result = bb >> -SOUTH_WEST & ~H_FILE;
        break;
    default:
        std::cout << "moveOne() reached default case in switch, something is terribly wrong"<< std::endl;
    }
    return result;
}

void prettyPrintBB(Bitboard bb) {
    Bitboard a = bb;
    constexpr unsigned int mask = 0b1;
    for (int j=63; j>=0; j--) {
        Bitboard bit_position = 8*(j/8)+(7-j%8);
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