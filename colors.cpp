#include "colors.h"

Color& operator++(Color& c, int) {
    if (c == WHITE) {
        c = BLACK;
    } else {
        c = WHITE;
    } 
    return c;
}