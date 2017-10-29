#pragma once

#include <vector>

#include "config.h"
#include "move.h"
#include "piece.h"

namespace checkers_AI {
    class board {
    public:
        board();
        ~board();

        piece** operator[](const int& raw);
        void execute_move(move* move);
        void reverse_move(move* move);
        std::vector<move*> list_all_moves(piece* piece);
        std::vector<move*> list_all_moves();
        piece* & operator[](const vec & pos);
        piece* operator[](const vec & pos) const;

    private:
        piece* _board[board_height][board_width];
        bool _validate_position(const vec & pos) const;
        bool _occupiable(const vec & pos) const;
        void _list_more_captures(piece* mover, std::vector<move*>& moves, std::vector<piece*>& captures);
    };

    std::ostream& operator<<(std::ostream& os, board* board);
}

