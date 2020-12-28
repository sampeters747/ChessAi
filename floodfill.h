#pragma once
#include "bitboard.h"

template<Direction d>
Bitboard dumbFill(Bitboard p, Bitboard unoccupied);

Bitboard d7Attacks(Bitboard position, Bitboard unoccupied);