#include "config.h"
#include "move.h"

namespace checkers_AI {
    move::move(piece* mover, const int& x, const int& y)
        : x(x), y(y), fx(mover->x), fy(mover->y) {
        this->mover = mover;
        this->move_kind = move_kind_type::MOVE;
        this->is_promoting = !mover->isQueen
            && ((mover->color == piece::color_type::RED && y == board_height)
                || (mover->color == piece::color_type::BLACK && y == 0));
    }

    move::move(piece * mvoer, const int & x, const int & y, std::vector<piece*> capture_pieces)
        :x(x), y(y), fx(mover->x), fy(mover->y) {
        this->mover = mover;
        this->move_kind = move_kind_type::CAPTURE;
        this->capture_pieces = capture_pieces;
        this->is_promoting = !mover->isQueen
            && ((mover->color == piece::color_type::RED && y == board_height)
                || (mover->color == piece::color_type::BLACK && y == 0));
    }

    move::~move() {
        delete mover;
        delete blance_piece;
        for (piece* captured_piece : capture_pieces) {
            delete captured_piece;
        }
    }
}