//
// Created by Peter on 4/10/2016.
//
#include "DefaultAgentStrategy.h"
#include "Game.h"

namespace Gaming {
    DefaultAgentStrategy::DefaultAgentStrategy() { };

    DefaultAgentStrategy::~DefaultAgentStrategy() { };

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const {
        std::vector<int> validMoves;
        for (int i = 0; i < 9; i++) {
            PieceType curNeighbor = s.array[i];
            if (curNeighbor == ADVANTAGE) {
                validMoves.push_back(i);
            }
        }

        if (!validMoves.size()) {
            for (int i = 0; i < 9; i++) {
                PieceType curNeighbor = s.array[i];
                if (curNeighbor == FOOD) {
                    validMoves.push_back(i);
                }
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
        if (!validMoves.size()) {
            for (int i = 0; i < 9; i++) {
                PieceType curNeighbor = s.array[i];
                if (curNeighbor == SIMPLE) {
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
