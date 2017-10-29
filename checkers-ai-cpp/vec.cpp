#include "vec.h"

namespace checkers_AI {

    vec vec::one(1, 1);
    vec vec::dirs[] = { vec(1, 1), vec(1, -1), vec(-1, -1), vec(-1, 1) };
    
    vec::vec(const int& x, const int& y) : x(x), y(y) {
    }
    
    vec::vec() : x(0), y(0){
    }


    vec::~vec() {
    }

    vec & vec::operator+=(const vec & rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    vec checkers_AI::operator+(vec lhs, const vec & rhs) {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        return lhs;
    }

    vec checkers_AI::operator-(vec lhs, const vec & rhs) {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        return lhs;
    }

    vec operator*(const int & lhs, vec rhs) {
        rhs.x *= lhs;
        rhs.y *= lhs;
        return rhs;
    }

    vec operator*(vec lhs, const int & rhs) {
        lhs.x *= rhs;
        lhs.y *= rhs;
        return lhs;
    }

    std::ostream & operator<<(std::ostream & os, const vec & rhs) {
        os << "(" << (char)(rhs.y + 65) << rhs.x << ")";
        return os;
    }
}