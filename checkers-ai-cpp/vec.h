#pragma once

#include <ostream>

namespace checkers_AI {
    struct vec
    {
    public:
        vec(const int& x, const int& y);
        vec();
        ~vec();

        friend vec operator+(vec lhs, const vec& rhs);
        friend vec operator-(vec lhs, const vec& rhs);
        friend vec operator*(const int& lhs, vec rhs);
        friend vec operator*(vec lhs, const int& rhs);
        friend std::ostream& operator<<(std::ostream& os, const vec& rhs);
        vec & operator+=(const vec & rhs);

        int x;
        int y;
        static const vec one;
        static const vec zero;
        static const vec dirs[4];
    };
}