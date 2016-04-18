//
// Created by Peter on 4/10/2016.
//
#include <sstream>
#include "Simple.h"

namespace Gaming {

    const char Simple::SIMPLE_ID = 'S';

    Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g, p, energy) {

    }

    Simple::~Simple() { }


    void Simple::print(std::ostream &os) const {
        std::stringstream ss;
        ss << Simple::SIMPLE_ID << __id;
        std::string output = ss.str();
        os << output;
    }


    ActionType Simple::takeTurn(const Surroundings &s) const {


        std::vector<int> validMoves;
        for (int i = 0; i < 9; i++) {
            PieceType curNeighbor = s.array[i];
            if (curNeighbor == FOOD || curNeighbor == ADVANTAGE) {
                validMoves.push_back(i);
            }
        }

        if (!validMoves.size()) {
            for (int i = 0; i < 9; i++) {
                PieceType curNeighbor = s.array[i];
                if (curNeighbor == EMPTY) {
                    validMoves.push_back(i);
                }
            }
        }
        if (validMoves.size()) {
            Position goal = Game::randomPosition(validMoves);
            return Game::reachSurroundings(Position(1, 1), goal);
        } else { return STAY; }
    }

}