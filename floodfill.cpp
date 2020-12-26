/* floodfill.cpp
Implements dumb7 floodfill algorithm to iteratively calculate attacked spaces.
Used at startup to create lookup tables used during engine search.
*/

#include "bitboard.h"

template<Direction d>
Bitboard dumbFill(Bitboard p, Bitboard unoccupied) {
    Bitboard attacked = p;
    attacked |= p = moveOne<d>(p) & unoccupied;
    attacked |= p = moveOne<d>(p) & unoccupied;
    attacked |= p = moveOne<d>(p) & unoccupied;
    attacked |= p = moveOne<d>(p) & unoccupied;
    attacked |= p = moveOne<d>(p) & unoccupied;
    attacked |= p = moveOne<d>(p) & unoccupied;
    attacked |= p = moveOne<d>(p) & unoccupied;
    return moveOne<d>(attacked);
}

Bitboard test(Bitboard position, Bitboard occupied) {
    Bitboard attacks = dumbFill<NORTH>(position, occupied);
    attacks |= dumbFill<EAST>(position, occupied);
    attacks |= dumbFill<SOUTH>(position, occupied);
    attacks |= dumbFill<WEST>(position, occupied);
    return attacks;
}
