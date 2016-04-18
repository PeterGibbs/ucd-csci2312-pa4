//
// Created by Peter on 4/10/2016.
//
#include <sstream>
#include "Strategic.h"

namespace Gaming {
    const char Strategic::STRATEGIC_ID = 'T';

    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s) : Agent(g, p, energy) {
        __strategy = s;
    }

    Strategic::~Strategic() {

    }

    void Strategic::print(std::ostream &os) const {
        std::stringstream ss;
        ss << Strategic::STRATEGIC_ID << __id;
        std::string output = ss.str();
        os << output;
    }

    ActionType Strategic::takeTurn(const Surroundings &s) const {
        return (*__strategy)(s);
    }
}


