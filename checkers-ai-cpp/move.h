#pragma once

#include <ostream>
#include <vector>

#include "piece.h"

namespace checkers_AI {
    class move {
    public:
        enum class move_kind_type {
            MOVE,
            CAPTURE
        };

        move(piece* mover, const int& x, const int& y);
        move(piece* mover, const vec& to);
        move(piece* mvoer, const int& x, const int& y, std::vector<piece*> capture_pieces);
        move(piece* mvoer, const vec& to, std::vector<piece*> capture_pieces);
        ~move();

        piece* mover;
        vec from;
        vec to;
        piece* blance_piece = piece::make_empty();
        std::vector<piece*> capture_pieces;
        bool is_promoting = false;
        move_kind_type move_kind;
    };

    std::ostream& operator<<(std::ostream& os, const move* move);
}
