#include "bitboard.h"
#include "types.h"

Color& operator++(Color& c, int) {
    if (c == WHITE) {
        c = BLACK;
    } else {
        c = WHITE;
    } 
    return c;
}

Square& operator++(Square& s, int) {
    if (s == SQ_OVERFLOW) {
        s = A1;
    } else {
        s = Square(s+1);
    } 
    return s;
}

