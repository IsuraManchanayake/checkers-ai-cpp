#include "config.h"
#include "move.h"

namespace checkers_AI {
	move::move(piece* mover, const int& x, const int& y)
		: x(x), y(y), fx(mover->x), fy(mover->y) {
		this->mover = mover;
		this->is_promoting = !mover->isQueen
			&& ((mover->color == piece::color_type::RED && y == board_height)
				|| (mover->color == piece::color_type::BLACK && y == 0));
	}

	move::~move() {
		delete mover;
		delete blance_piece;
		for (piece* captured_piece: capture_pieces) {
			delete captured_piece;
		}
	}

	move::move_kind_type move::get_move_kind() {
		return this->capture_pieces.size() == 0 ? move_kind_type::CAPTURE : move_kind_type::MOVE;
	}
}