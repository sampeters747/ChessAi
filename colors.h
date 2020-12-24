#pragma once

// Declaring Colors
enum Color : int {
    WHITE, BLACK
};

Color& operator++(Color&, int);