//
// Created by Peter on 4/10/2016.
//
#include "AggressiveAgentStrategy.h"
#include "Game.h"

namespace Gaming {

    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {
        __agentEnergy = agentEnergy;
    }

    AggressiveAgentStrategy::~AggressiveAgentStrategy() { };

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const {
        std::vector<int> validMoves;
        if (__agentEnergy > AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD) {
            for (int i = 0; i < 9; i++) {
                PieceType curNeighbor = s.array[i];
                if (curNeighbor == SIMPLE || curNeighbor == STRATEGIC) {
                    validMoves.push_back(i);
                }
            }
        }

        if (!validMoves.size()) {
            for (int i = 0; i < 9; i++) {
                PieceType curNeighbor = s.array[i];
                if (curNeighbor == ADVANTAGE) {
                    validMoves.push_back(i);
                }
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
        if (validMoves.size()) {
            Position goal = Game::randomPosition(validMoves);
            return Game::reachSurroundings(Position(1, 1), goal);
        } else { return STAY; }
    }


}

