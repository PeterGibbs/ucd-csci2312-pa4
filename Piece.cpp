//
// Created by Peter on 4/10/2016.
//
#include "Game.h"
#include "Piece.h"

namespace Gaming {
    unsigned int Piece::__idGen = 1000;

    Piece::Piece(const Game &g, const Position &p) : __game(g) {
        __id = __idGen;
        __idGen++;
        __position = p;
        __finished = false;
        __turned = false;
    }

    Piece::~Piece() { };

    std::ostream &operator<<(std::ostream &os, const Piece &piece) {
        piece.print(os);
        return os;
    }

}