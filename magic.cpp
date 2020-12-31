#include <bitset>
#include <stdlib.h>
#include <cmath>
#include "bitboard.h"
#include "magic.h"
#include "types.h"
#include "floodfill.h"



MagicTable::MagicTable(Piece pieceType, Bitboard emptyAttacks[64])
{
    int magiccounter = 0;
    std::cout << "start";
    for (Square sq = A1; sq <= H8; sq++) {
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
        Bitboard occupancySets[4096];
        // Used during magic factor generation
        int epoch[4096];
        for (int i=0; i<4096; i++) {
            epoch[i] = -1;
        }
        // Init magic lookup table, intially null values
        Bitboard* table = new Bitboard[static_cast<int>(pow(2,64-shifts[sq]))];
        // Given an initial set of bits d, n will permutate to every combination of those bits
        Bitboard n = EMPTY_BB;
        Bitboard d = masks[sq];
        do
        {
            attackSets[permCount] = d7Attacks(SQUARE_BB[sq], ~n);
            occupancySets[permCount] = n;
            permCount++;
            n = (n - d) & d;
        } while (n);
        Bitboard pMagic;
        int attemptCount = 0;
        for (int i = 0; i < permCount; ) {
            attemptCount++;
            pMagic = random_uint64_fewbits();
            //pMagic = rand() & rand()& rand();
            for (i=0; i<permCount; i++) {
                int index = (occupancySets[i]*pMagic) >> shifts[sq];
                if (epoch[index] < attemptCount) {
                    table[index] = attackSets[i];
                    epoch[index] = attemptCount;
                } else if (table[index] != attackSets[i]) {
                    
                    break;
                }
            }
        }
        magicFactors[sq] = pMagic;
        l[sq] = table;
        magiccounter += attemptCount;
        std::cout << attemptCount << std::endl;
        std::cout << magiccounter << std::endl;
        std::cout << "found one" << "         "<< sq << std::endl;
    }
    
    

}

MagicTable::~MagicTable() {
    for (Square sq=A1; sq <=H8; sq++) {
        delete l[sq];
    }
}


Bitboard MagicTable::getAttacks(Square sq, Bitboard occupied) {
    int index = ((occupied & masks[sq]) * magicFactors[sq]) >> shifts[sq];
    return l[sq][index];
}


ulong random_uint64() {
  ulong u1, u2, u3, u4;
  u1 = (ulong)(random()) & 0xFFFF; u2 = (ulong)(random()) & 0xFFFF;
  u3 = (ulong)(random()) & 0xFFFF; u4 = (ulong)(random()) & 0xFFFF;
  return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

ulong random_uint64_fewbits() {
  return random_uint64() & random_uint64() & random_uint64();
}

