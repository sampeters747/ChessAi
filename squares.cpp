#include "bitboard.h"
#include "squares.h"

Square& operator++(Square& s, int) {
    if (s == SQ_OVERFLOW) {
        s = A1;
    } else {
        s = Square(s+1);
    } 
    return s;
}

Bitboard getFile(Square sq) {
    return FILES[sq%8];
}
Bitboard getRank(Square sq) {
    return FILES[sq/8];
}