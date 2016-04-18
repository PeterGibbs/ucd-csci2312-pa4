//
// Created by Peter on 4/10/2016.
//

#include "Exceptions.h"

namespace Gaming {

    void GamingException::setName(std::string name) {
        __name = name;
    }

    std::ostream &operator<<(std::ostream &os, const GamingException &ex) {
        os << ex.__name;
        ex.__print_args(os);
        return os;
    }


    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) {
        __name = "DimensionEx";
        __exp_width = expWidth;
        __exp_height = expHeight;
        __width = width;
        __height = height;
    }

    unsigned DimensionEx::getExpWidth() const {
        return __exp_width;
    }

    unsigned DimensionEx::getExpHeight() const {
        return __exp_height;
    }

    unsigned DimensionEx::getWidth() const {
        return __width;
    }

    unsigned DimensionEx::getHeight() const {
        return __height;
    }

    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width,
                                                       unsigned height) : DimensionEx(minWidth, minHeight, width,
                                                                                      height) {
        __name = "InsufficientDimensionsEx";
    }

    void InsufficientDimensionsEx::__print_args(std::ostream &os) const {
        os << __exp_width << ',' << __exp_height << ',' << __width << ',' << __height;
    }

    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) : DimensionEx(
            maxWidth, maxHeight, width, height) {
        __name = "OutOfBoundsEx";
    }

    void OutOfBoundsEx::__print_args(std::ostream &os) const {
        os << __exp_width << ',' << __exp_height << ',' << __width << ',' << __height;
    }

    PositionEx::PositionEx(unsigned x, unsigned y) {
        __x = x;
        __y = y;
        __name = "PositionEx";
    }

    void PositionEx::__print_args(std::ostream &os) const {
        os << __x << ',' << __y;
    }

    PositionNonemptyEx::PositionNonemptyEx(unsigned x, unsigned y) : PositionEx(x, y) {
        __name = "PositionNonemptyEx";
    }

    PositionEmptyEx::PositionEmptyEx(unsigned x, unsigned y) : PositionEx(x, y) {
        __name = "PositionEmptyEx";
    }

    PosVectorEmptyEx::PosVectorEmptyEx() {
        __name = "PosVectorEmptyEx";
    }

    void PosVectorEmptyEx::__print_args(std::ostream &os) const {

    }

}