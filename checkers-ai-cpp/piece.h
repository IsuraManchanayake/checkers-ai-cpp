#pragma once

#include <ostream>
#include <vector>

namespace checkers_AI {
	class piece {
	public:
		enum class color_type {
			EMPTY,
			RED,
			BLACK
		};

		piece(const int& x, const int& y, const color_type& col, const int& id);
		~piece();

		static piece* make_empty();

		int x;
		int y;
		int id;
		bool isQueen = false;
		bool isEmpty = false;
		color_type color;

	private:
		static piece* _empty_piece;
	};

	std::ostream& operator<<(std::ostream& os, piece* piece);
}
