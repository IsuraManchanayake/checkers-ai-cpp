#pragma once

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
		~move();
		move_kind_type get_move_kind();

		piece* mover;
		int fx;
		int fy;
		int x;
		int y;
		piece* blance_piece = piece::make_empty();
		std::vector<piece*> capture_pieces;
		bool is_promoting = false;
		move_kind_type move_kind;
	};
}
