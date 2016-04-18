//
// Created by Peter on 4/10/2016.
//

#include "Food.h"
#include<iomanip>
#include <sstream>

namespace Gaming {
    const char Food::FOOD_ID = 'F';

    Food::Food(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity) {

    }

    Food::~Food() { }

    void Food::print(std::ostream &os) const {
        std::stringstream ss;
        ss << Food::FOOD_ID << __id;
        std::string output = ss.str();
        os << output;
        return;
    }

}
