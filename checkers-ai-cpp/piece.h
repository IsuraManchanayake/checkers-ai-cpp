#pragma once

#include <ostream>
#include <vector>

#include "vec.h"

namespace checkers_AI {
    class piece {
    public:
        enum class color_type {
            empty,
            red,
            black
        };

        piece(const int& x, const int& y, const color_type& col, const int& id);
        piece(const vec& v, const color_type& col, const int& id);
        ~piece();

        static piece* make_empty();
        static piece* create_piece(const vec & v, const char & char_repr, const int & id);

        vec pos;
        int id;
        bool is_queen = false;
        bool is_empty = false;
        color_type color;

    private:
        piece();
        static piece* _empty_piece;
    };

    std::ostream& operator<<(std::ostream& os, piece* piece);
    piece::color_type operator!(piece::color_type color);
}
