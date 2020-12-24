#include "squares.h"

Square& operator++(Square& s, int) {
    if (s == SQ_OVERFLOW) {
        s = A1;
    } else {
        s = Square(s+1);
    } 
    return s;
}