//
// Created by Peter on 4/10/2016.
//

#include <iomanip>
#include <sstream>
#include "Advantage.h"


namespace Gaming {
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;
    const char Advantage::ADVANTAGE_ID = 'D';

    Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity) {
        __capacity *= Advantage::ADVANTAGE_MULT_FACTOR;
    }

    Advantage::~Advantage() { }

    double Advantage::getCapacity() const {
        return __capacity;
    }

    double Advantage::consume() {
        finish();
        return getCapacity();
    }

    void Advantage::print(std::ostream &os) const {
        std::stringstream ss;
        ss << Advantage::ADVANTAGE_ID << __id;
        std::string output = ss.str();

        os << output;
        return;
    }
}