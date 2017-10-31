#pragma once

#include <vector>

#include "config.h"
#include "board_stat.h"
#include "move.h"
#include "piece.h"

namespace checkers_AI {
    class board {
    public:
        board();
        board(const char (&char_repr)[board_height][board_width]);
        ~board();

        board_stat* stat = new board_stat();

        piece** operator[](const int& raw);
        void execute_move(move* move);
        void reverse_move(move* move);
        std::vector<move*> list_all_moves(); // use only for testing
        std::vector<move*> list_all_moves(move* last_move, piece* piece);
        std::vector<move*> list_all_moves(move* last_move);
        std::vector<piece*> list_all_blance_pieces(move* last_move);
        piece* & operator[](const vec & pos);
        piece* operator[](const vec & pos) const;

    private:
        piece* _board[board_height][board_width];

        bool _validate_position(const vec & pos) const;
        bool _occupiable(const vec & pos) const;
        void _list_more_captures(piece* mover, const vec start, std::vector<move*>& moves, std::vector<piece*> captures);
        bool _check_captures_available(piece* mover);
        void _execute_move(move* move);
        void _reverse_move(move* move);
        std::vector<move*> _list_all_raw_moves(piece::color_type color);
        std::vector<move*> _list_all_raw_moves(piece* piece);
    };

    std::ostream& operator<<(std::ostream& os, board* board);
}

