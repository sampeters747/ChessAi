#pragma once
#include "bitboard.h"

template<Direction d>
Bitboard dumbFill(Bitboard p, Bitboard unoccupied);

Bitboard test(Bitboard position, Bitboard occupied);