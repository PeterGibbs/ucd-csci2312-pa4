//
// Created by Peter on 4/10/2016.
//

#include "Resource.h"
#include "Agent.h"

namespace Gaming {
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double capacity = Game::STARTING_RESOURCE_CAPACITY) : Piece(g,
                                                                                                                     p) {
        __capacity = capacity;
    }

    Resource::~Resource() {

    };

    void Resource::age() {
        if (__capacity > 1) { __capacity = 0; } else {

            __capacity /= Resource::RESOURCE_SPOIL_FACTOR;
        }
    }

    double Resource::consume() {
        finish();
        return getCapacity();

    }

    ActionType Resource::takeTurn(const Surroundings &s) const {
        return STAY;
    }

    Piece &Resource::operator*(Piece &rv) {
        return rv.interact(this);
    }

    Piece &Resource::interact(Agent *consumer) {
        consumer->addEnergy(consume());
        return *this;
    }

    Piece &Resource::interact(Resource *) {
        return *this;
    }
}