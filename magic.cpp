#include <bitset>
#include <stdlib.h>
#include <cmath>
#include "bitboard.h"
#include "magic.h"
#include "types.h"
#include "floodfill.h"

void Magic::init()
{
    using namespace Magic;

    Bitboard R_MASKS[64];
    Bitboard B_MASKS[64];
    Bitboard R_MAGIC[64];
    Bitboard B_MAGIC[64];

    Bitboard corners = SQUARE_BB[A1] | SQUARE_BB[H1] | SQUARE_BB[A8] | SQUARE_BB[H8];
    for (Square sq = A1; sq <= H8; sq++)
    {
        std::cout << sq << std::endl;
        Bitboard mask = ROOK_ATTACKS[sq];
        prettyPrintBB(mask);
        if (getFile(sq) != A_FILE)
            mask &= ~A_FILE;
        if (getFile(sq) != H_FILE)
            mask &= ~H_FILE;
        if (getRank(sq) != RANK_1)
            mask &= ~RANK_1;
        if (getRank(sq) != RANK_8)
            mask &= ~RANK_8;
        std::cout << std::endl;
        prettyPrintBB(mask);

        R_MASKS[sq] = mask;
    }
    for (Square sq = A1; sq <= H8; sq++)
    {
        Bitboard d = R_MASKS[sq];
        // Given an initial set of bits d, n will permutate to every combination of those bits
        Bitboard n = EMPTY_BB;
        do
        {
            // Part where we intialize lookup table for this particular square/bit combination
            Bitboard filled = d7Attacks(SQUARE_BB[sq], ~n);
            unsigned int index = (n * magicmoves_r_magics[sq]) >> magicmoves_r_shift[sq];

            n = (n - d) & d;
        } while (n);
    }
}

MagicTable::MagicTable(Piece pieceType, Bitboard emptyAttacks[64])
{
    for (Square sq = A1; A1 <= H8; sq++) {
        Bitboard squareMask;
        Bitboard edgeMask;

        if (pieceType == Bishop) {
            edgeMask = EDGE_BB;
        } else if (pieceType == Rook) {
            edgeMask = (RANK_1 | RANK_8) & ~getRank(sq);
            edgeMask |= (A_FILE | H_FILE) & ~getFile(sq);
        }
            Bitboard keyBits = emptyAttacks[sq] & ~edgeMask;
            masks[sq] = keyBits;
            shifts[sq] = 64 - std::bitset<64>(keyBits).count();

        int permCount = 0;
        // Array of all possible bitboards showing attacked squares given a piece on square sq
        // May not be full
        Bitboard attackSets[4096];
        // Used during magic factor generation
        int epoch[4096];
        for (int i=0; i<4096; i++) {
            epoch[i] = -1;
        }
        // Init magic lookup table, intially null values
        Bitboard table[pow(2,64-shifts[sq])] = {0};
        // Given an initial set of bits d, n will permutate to every combination of those bits
        Bitboard n = EMPTY_BB;
        Bitboard d = emptyAttacks[sq];
        do
        {
            attackSets[permCount] = d7Attacks(SQUARE_BB[sq], ~n);
            permCount++;
            n = (n - d) & d;
        } while (n);

        Bitboard pMagic;
        int attemptCount = 0;
        for (int i = 0; i < permCount; ) {
            pMagic = rand() & rand() & rand();
            for (i=0; i<permCount; i++) {
                int index = attackSets[i]*pMagic >> shifts[sq];
                if (epoch[index] < attemptCount) {
                    table[index] = attackSets[i];
                    epoch[index] = attemptCount;
                } else if (table[index] != attackSets[i]) {
                    break;
                }
            }
            attemptCount++;
        }
        magicFactors[sq] = pMagic;
        l[sq] = table;
    }
    
    

}