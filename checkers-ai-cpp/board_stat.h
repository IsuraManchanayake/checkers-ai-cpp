#pragma once

#include <ostream>

#include "enum.h"
#include "move.h"

namespace checkers_AI {
    class board_stat
    {
    public:
        board_stat();
        ~board_stat();

        int r = 0;
        int R = 0;
        int b = 0;
        int B = 0;

        board_stat & operator+=(const piece* piece);
        board_stat & operator-=(const piece* piece);
        board_stat & operator+=(const move& move);
        board_stat & operator-=(const move& move);

        const int get_count(piece::color_type color);
        const game_result get_board_result();
    };

    std::ostream & operator<<(std::ostream & os, board_stat* & stat);
}