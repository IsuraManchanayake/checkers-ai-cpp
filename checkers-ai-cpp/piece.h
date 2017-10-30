#pragma once

#include <ostream>
#include <vector>

#include "vec.h"

namespace checkers_AI {
    class piece {
    public:
        enum class color_type {
            EMPTY,
            RED,
            BLACK
        };

        piece(const int& x, const int& y, const color_type& col, const int& id);
        piece(const vec& v, const color_type& col, const int& id);
        piece(const vec& v, const char& char_repr, const int& id);
        ~piece();

        static piece* make_empty();

        vec pos;
        int id;
        bool is_queen = false;
        bool is_empty = false;
        color_type color;

    private:
        static piece* _empty_piece;
    };

    std::ostream& operator<<(std::ostream& os, piece* piece);
}
