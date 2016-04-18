//
// Created by Peter on 4/10/2016.
//

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vfw.h>
//#include "Strategic.h"
//#include "Simple.h"
#include "Game.h"
#include "Advantage.h"
#include "Food.h"
#include "Strategic.h"
#include "Simple.h"

namespace Gaming {

    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const unsigned int Game::MIN_WIDTH = 3;
    const unsigned int Game::MIN_HEIGHT = 3;
    PositionRandomizer Game::__posRandomizer = Gaming::PositionRandomizer();

    Game::Game() {
        __status = NOT_STARTED;
        __width = 3;
        __height = 3;
        __grid = std::vector<Piece *>(__width * __height, nullptr);
        __round = 0;

    }

    Game::Game(unsigned width, unsigned height, bool manual) {
        if (width < MIN_WIDTH || height < MIN_HEIGHT) {
            throw (InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height));
        }
        __status = NOT_STARTED;

        __width = width;
        __height = height;
        __grid = std::vector<Piece *>(__width * __height, nullptr);
        __round = 0;
        if (!manual) {
            populate();
        }

    }

    Game::~Game() {
        for (int i = 0; i < __grid.size(); i++) {
            delete __grid[i];
        }
        __grid.clear();
    }

    void Game::addSimple(const Position &position) {

        int index = position.y + __width * position.x;
        if (__grid[index] != nullptr) { throw (PositionNonemptyEx(position.x, position.y)); }
        if (position.y > __width || position.x > __height) {
            throw (OutOfBoundsEx(__width, __height, position.y, position.x));
        }
        __grid[index] = new Simple(*this, position, STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(const Position &position, double energy) {

        int index = position.y + __width * position.x;
        if (__grid[index] != nullptr) { throw (PositionNonemptyEx(position.x, position.y)); }
        if (position.y > __width || position.x > __height) {
            throw (OutOfBoundsEx(__width, __height, position.y, position.x));
        }

        __grid[index] = new Simple(*this, position, energy);
    } // used for testing only
    void Game::addSimple(unsigned x, unsigned y) {
        int index = y + __width * x;
        if (__grid[index] != nullptr) { throw (PositionNonemptyEx(x, y)); }

        __grid[index] = new Simple(*this, Position(x, y), Game::STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(unsigned x, unsigned y, double energy) {
        int index = y + __width * x;
        if (y > __width || x > __height) { throw (OutOfBoundsEx(__width, __height, y, x)); }

        if (__grid[index] != nullptr) { throw (PositionNonemptyEx(x, y)); }

        __grid[index] = new Simple(*this, Position(x, y), Game::STARTING_AGENT_ENERGY);
    }

    void Game::addStrategic(const Position &position, Strategy *s) {
        int index = position.y + __width * position.x;
        if (position.y > __width || position.x > __height) {
            throw (OutOfBoundsEx(__width, __height, position.y, position.x));
        }

        if (__grid[index] != nullptr) { throw (PositionNonemptyEx(position.x, position.y)); }

        __grid[index] = new Strategic(*this, position, Game::STARTING_AGENT_ENERGY, s);
    }

    void Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
        int index = y + __width * x;
        if (y > __width || x > __height) { throw (OutOfBoundsEx(__width, __height, y, x)); }

        if (__grid[index] != nullptr) { throw (PositionNonemptyEx(x, y)); }

        __grid[index] = new Strategic(*this, Position(x, y), Game::STARTING_AGENT_ENERGY, s);
    }

    void Game::addFood(const Position &position) {
        if (position.y > __width || position.x > __height) {
            throw (OutOfBoundsEx(__width, __height, position.y, position.x));
        }

        int index = position.y + __width * position.x;
        if (__grid[index] != nullptr) { throw (PositionNonemptyEx(position.x, position.y)); }

        __grid[index] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
    }

    void Game::addFood(unsigned x, unsigned y) {
        if (y > __width || x > __height) { throw (OutOfBoundsEx(__width, __height, y, x)); }

        int index = y + __width * x;
        if (__grid[index] != nullptr) { throw (PositionNonemptyEx(x, y)); }

        __grid[index] = new Food(*this, Position(x, y), STARTING_RESOURCE_CAPACITY);

    }

    void Game::addAdvantage(const Position &position) {
        int index = position.y + __width * position.x;
        if (position.y > __width || position.x > __height) {
            throw (OutOfBoundsEx(__width, __height, position.y, position.x));
        }
        if (__grid[index] != nullptr) { throw (PositionNonemptyEx(position.x, position.y)); }

        __grid[index] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(unsigned x, unsigned y) {
        if (y > __width || x > __height) { throw (OutOfBoundsEx(__width, __height, y, x)); }

        int index = y + __width * x;
        if (__grid[index] != nullptr) { throw (PositionNonemptyEx(x, y)); }

        __grid[index] = new Advantage(*this, Position(x, y), STARTING_RESOURCE_CAPACITY);
    }


    const Surroundings Game::getSurroundings(const Position &pos) const {
        int sIndex = 0;


        Surroundings currentNeighbors;
        PieceType curPieceType = EMPTY;
        const Piece *curPiece = nullptr;
        for (int xOffset = -1; xOffset <= 1; xOffset++) {
            for (int yOffset = -1; yOffset <= 1; yOffset++) {
                int yPosS = pos.y + yOffset;
                int xPosS = pos.x + xOffset;
                int cindex = yPosS + __width * xPosS;
                if (yPosS >= __width || xPosS >= __height || yPosS < 0 || xPosS < 0) {
                    //std::cout<<"Found: INACCESSIBLE"<<std::endl;
                    curPieceType = INACCESSIBLE;
                } else {
                    unsigned int xPos = abs(xPosS);
                    unsigned int yPos = abs(yPosS);
                    cindex = yPos + __width * xPos;
                    try {
                        curPiece = getPiece(xPos, yPos);

                        if (xOffset == 0 && yOffset == 0) {
                            curPieceType = SELF;

                        } else {
                            curPieceType = curPiece->getType();
                        }
                    } catch (PositionEmptyEx) {
                        curPieceType = EMPTY;
                    }
                }
                currentNeighbors.array[sIndex] = curPieceType;
                sIndex++;
            }

        }
        currentNeighbors.array[4] = SELF;
        return currentNeighbors;
    }

    void Game::populate() {
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;
        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height);

        while (numStrategic > 0) {
            int i = d(gen);
            if (__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = nullptr;
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);

                numStrategic--;
            }
        }

        while (numSimple > 0) {
            int i = d(gen);
            if (__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = nullptr;
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numSimple--;
            }
        }

        while (numFoods > 0) {
            int i = d(gen);
            if (__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }

        while (numAdvantages > 0) {
            int i = d(gen);
            if (__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }
    }

    unsigned int Game::getNumPieces() const {
        unsigned int count = 0;
        for (int i = 0; i < __grid.size(); i++) {
            if (__grid[i] != nullptr) {
                count++;
            }
        }
        return count;
    }

    unsigned int Game::getNumAgents() const {
        unsigned int numAgents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Agent *curPiece = dynamic_cast<Agent *>(*it);
            if (curPiece) numAgents++;
        }

        return numAgents;
    }

    unsigned int Game::getNumSimple() const {
        unsigned int numAgents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Simple *curPiece = dynamic_cast<Simple *>(*it);
            if (curPiece) numAgents++;
        }

        return numAgents;
    }

    unsigned int Game::getNumStrategic() const {
        unsigned int numAgents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Strategic *curPiece = dynamic_cast<Strategic *>(*it);
            if (curPiece) numAgents++;
        }

        return numAgents;
    }

    unsigned int Game::getNumResources() const {
        unsigned int numAgents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Resource *curPiece = dynamic_cast<Resource *>(*it);
            if (curPiece) numAgents++;
        }

        return numAgents;
    }

    const Piece *Game::getPiece(unsigned int x, unsigned int y) const {
        if (y >= __width || x >= __height || y < 0 || x < 0) { throw (OutOfBoundsEx(__width, __height, y, x)); }
        int index = y + __width * x;
        if (__grid[index] == nullptr) { throw (PositionEmptyEx(x, y)); }
        return __grid[index];
    }


    std::ostream &operator<<(std::ostream &os, const Game &game) {

        os << "Round " << 1 << ':' << '\n';
        for (unsigned int x = 0; x < game.__height; x++) {
            for (unsigned int y = 0; y < game.__width; y++) {
                Piece *curPiece;
                try {
                    const Piece *curPiece = game.getPiece(x, y);
                    os << std::left << '[' << std::setw(5) << *game.getPiece(x, y);
                    os << ']';
                } catch (PositionEmptyEx) {
                    Piece *curPiece = nullptr;
                    os << '[' << "     " << "]";
                }


            }
            os << std::endl;
        }
        std::string s;

        switch (game.__status) {
            case Game::PLAYING:
                s = "PLAYING";
                break;
            case Game::OVER:
                s = "OVER";
                break;
            default:
                s = "NOT_STARTED";
                break;
        }
        os << "Status: " << s << std::endl;
        return os;
    }

    const ActionType Game::reachSurroundings(const Position &from, const Position &to) {
        int dx = to.x - from.x;
        int dy = to.y - from.y;

        ActionType out;


        if (dx == -1 && dy == -1) {
            out = NW;
        } else if (dx == -1 && dy == 0) {
            out = N;
        } else if (dx == -1 && dy == 1) {
            out = NE;
        } else if (dx == 0 && dy == -1) {
            out = W;
        } else if (dx == 0 && dy == 0) {
            out = STAY;
        } else if (dx == 0 && dy == 1) {
            out = E;
        } else if (dx == 1 && dy == -1) {
            out = SW;
        } else if (dx == 1 && dy == 0) {
            out = S;
        } else if (dx == 1 && dy == 1) {
            out = SE;
        }
        return out;
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const {
        bool legal = true;
        Position direction;
        int dx = 0;
        int dy = 0;
        switch (ac) {
            case NW:
                dx = -1;
                dy = -1;
                break;
            case N:
                dx = -1;
                dy = 0;
                break;
            case NE:
                dx = -1;
                dy = 1;
                break;
            case W:
                dx = 0;
                dy = -1;
                break;
            case E:
                dx = 0;
                dy = 1;
                break;
            case SW:
                dx = 1;
                dy = -1;
                break;
            case S:
                dx = 1;
                dy = 0;
                break;
            case SE:
                dx = 1;
                dy = 1;
                break;
            default:
                dx = 0;
                dy = 0;
                break;
        }
        int x = pos.x + dx;
        int y = pos.y + dy;

        if (x >= __height) {
            legal = false;
        }
        if (y >= __width) {
            legal = false;
        }
        return legal;
    }

    const Position Game::move(const Position &pos, const ActionType &ac) const {
        int dx = 0;
        int dy = 0;
        switch (ac) {
            case NW:
                dx = -1;
                dy = -1;
                break;
            case N:
                dx = -1;
                dy = 0;
                break;
            case NE:
                dx = -1;
                dy = 1;
                break;
            case W:
                dx = 0;
                dy = -1;
                break;
            case E:
                dx = 0;
                dy = 1;
                break;
            case SW:
                dx = 1;
                dy = -1;
                break;
            case S:
                dx = 1;
                dy = 0;
                break;
            case SE:
                dx = 1;
                dy = 1;
                break;
            default:
                dx = 0;
                dy = 0;
                break;
        }
        int x = pos.x + dx;
        int y = pos.y + dy;
        Position toPos(x, y);
        return toPos;


    }

    void Game::round() {
        for (int i = 0; i < __grid.size(); i++) {
            if (__grid[i] != nullptr) {

                if (!__grid[i]->getTurned()) {
                    __grid[i]->setTurned(true);
                    Surroundings s = Game::getSurroundings(__grid[i]->getPosition());
                    ActionType action = __grid[i]->takeTurn(s);
                    bool legal = isLegal(action, __grid[i]->getPosition());
                    if (legal) {
                        Position lastPos = __grid[i]->getPosition();
                        Position destination = move(lastPos, action);


                        int dindex = destination.y + __width * destination.x;

                        if (__grid[dindex] != nullptr) {
                            (*__grid[i]) * (*__grid[dindex]);
                        }
                        if (__grid[dindex] != nullptr && !__grid[dindex]->isViable()) {
                            __grid[dindex] = nullptr;
                        }
                        if (__grid[dindex] == nullptr && __grid[i]->isViable()) {
                            __grid[i]->setPosition(destination);
                            __grid[dindex] = __grid[i];
                            __grid[i] = nullptr;
                        }

                    }
                }
                if (__grid[i] != nullptr && !__grid[i]->isViable()) {
                    delete __grid[i];
                    __grid[i] = nullptr;
                }
            }
        }
        for (int i = 0; i < __grid.size(); i++) {
            if (__grid[i] != nullptr) { __grid[i]->setTurned(false); }
        }
        __round++;
    }

    void Game::play(bool verbose) {
        std::cout << *this << std::endl;
        __status = PLAYING;

        while (__status == PLAYING) {
            if (getNumResources() == 0 || getNumAgents() == 0) {
                __status = OVER;
                break;
            }

            round();
            std::cout << *this << std::endl;


        }
        std::cout << *this << std::endl;
    }


}