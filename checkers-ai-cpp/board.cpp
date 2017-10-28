#include <ostream>

#include "board.h"

namespace checkers_AI {

	board::board() {
		for (int i = 0; i < board_height; i++) {
			for (int j = 0; j < board_width; j++) {
				_board[i][j] = piece::make_empty();
			}
		}
		int count = 0;
		for (int i = 0; i < board_height / 2 - 1; i++) {
			for (int j = !(i & 1); j < board_width; j += 2) {
				_board[i][j] = new piece(j, i, piece::color_type::RED, count++);
			}
		}
		for (int i = board_height / 2 + 1; i < board_height; i++) {
			for (int j = !(i & 1); j < board_width; j += 2) {
				_board[i][j] = new piece(j, i, piece::color_type::BLACK, count++);
			}
		}
	}


	board::~board()	{}

	piece** board::operator[](const int& raw) {
		return _board[raw];
	}

	void board::execute_move(move * move) {
		if (!move->blance_piece->isEmpty) {
			_board[move->blance_piece->y][move->blance_piece->x] = piece::make_empty();
		}
		_board[move->fy][move->fx] = piece::make_empty();
		for (piece* capture_piece : move->capture_pieces) {
			_board[capture_piece->y][capture_piece->x] = piece::make_empty();
		}
		_board[move->y][move->x] = move->mover;
		move->mover->y = move->y;
		move->mover->x = move->x;
		if (move->is_promoting) {
			move->mover->isQueen = true;
		}
	}

	void board::reverse_move(move * move) {
	}

	std::ostream& operator<<(std::ostream& os, board* board) {
		os << "         ";
		for (int i = 0; i < board_width; i++) {
			os << "  " << i << "   ";
		}
		os << std::endl << "        +";
		for (int i = 0; i < board_width; i++) {
			os << "-----+";
		}
		os << std::endl;
		for (int i = 0; i < board_height; i++) {
			os << "  " << i << "(" << (char)(i + 65) << ")" << "  |";
			for (int j = 0; j < board_width; j++) {
				os << " " << (*board)[i][j] << " |";
			}
			os << std::endl << "        +";
			for (int j = 0; j < board_width; j++) {
				os << "-----+";
			}
			os << std::endl;
		}
		return os;
	}
}