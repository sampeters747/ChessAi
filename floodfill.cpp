/* floodfill.cpp
Implements dumb7 floodfill algorithm to iteratively calculate attacked spaces.
Used at startup to create lookup tables used during engine search.
*/

#include "bitboard.h"
#include "types.h"

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

Bitboard d7Attacks(Bitboard position, Bitboard unoccupied) {
    Bitboard attacks = dumbFill<NORTH>(position, unoccupied);
    attacks |= dumbFill<EAST>(position, unoccupied);
    attacks |= dumbFill<SOUTH>(position, unoccupied);
    attacks |= dumbFill<WEST>(position, unoccupied);
    return attacks;
}
