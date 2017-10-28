#pragma once

#include <vector>

#include "config.h"
#include "piece.h"
#include "move.h"

namespace checkers_AI {
	class board {
	public:
		board();
		~board();

		piece** operator[](const int& raw);
		void execute_move(move* move);
		void reverse_move(move* move);

	private:
		piece* _board[board_height][board_width];
	};

	std::ostream& operator<<(std::ostream& os, board* board);
}

