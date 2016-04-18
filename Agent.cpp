//
// Created by Peter on 4/10/2016.
//

#include "Agent.h"
#include "Resource.h"

namespace Gaming {
    const double  Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy = Game::STARTING_AGENT_ENERGY) : Piece(g, p) {
        __energy = energy;
    }

    Agent::~Agent() { }


    void Agent::age() {
        __energy = __energy -= Agent::AGENT_FATIGUE_RATE;
    }

    Piece &Agent::operator*(Piece &rv) {
        return rv.interact(this);
    }

    Piece &Agent::interact(Agent *other) {
        if (other->getEnergy() == getEnergy()) {
            finish();
            other->finish();
        }
        if (other->getEnergy() > getEnergy()) {
            finish();

        }
        if (other->getEnergy() < getEnergy()) {
            __energy -= other->getEnergy();
        }
        return *this;
    }

    Piece &Agent::interact(Resource *item) {
        item->interact(this);
        return *this;
    }
}