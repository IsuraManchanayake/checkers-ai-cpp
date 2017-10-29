#include "config.h"
#include "move.h"

namespace checkers_AI {

    move::move(piece * mover, const vec & to) 
        : to(to), from(mover->pos) {
        this->mover = mover;
        this->move_kind = move_kind_type::MOVE;
        this->is_promoting = !mover->isQueen
            && ((mover->color == piece::color_type::RED && to.y == board_height)
                || (mover->color == piece::color_type::BLACK && to.y == 0));
    }

    move::move(piece* mover, const int& x, const int& y)
        : move(mover, vec(x, y)) {
    }

    move::move(piece * mvoer, const vec & to, std::vector<piece*> capture_pieces) 
        : to(to), from(mover->pos) {
        this->mover = mover;
        this->move_kind = move_kind_type::CAPTURE;
        this->capture_pieces = capture_pieces;
        this->is_promoting = !mover->isQueen
            && ((mover->color == piece::color_type::RED && to.y == board_height)
                || (mover->color == piece::color_type::BLACK && to.y == 0));
    }

    move::move(piece * mvoer, const int & x, const int & y, std::vector<piece*> capture_pieces)
        : move(mover, vec(x, y), capture_pieces) {
    }

    move::~move() {
        delete mover;
        delete blance_piece;
        for (piece* captured_piece : capture_pieces) {
            delete captured_piece;
        }
    }

    std::ostream & operator<<(std::ostream & os, const move * move) {
        os << (move->move_kind == move::move_kind_type::MOVE ? "move " : "capture ");
        os << move->mover << " from "<< move->from <<" to " << move->to;
        if (move->move_kind == move::move_kind_type::CAPTURE) {
            os << " capturing ";
            for (piece* capture_piece : move->capture_pieces) {
                os << capture_piece << " ";
            }
        }
        if (!move->blance_piece->isEmpty) {
            os << " blancing " << move->blance_piece;
        }
        return os;
    }
}