#pragma once

#include "board.h"
#include "piece.h"

namespace checkers_AI {
    template<typename T>
    class evaluator {
    public:
        typedef T res_type;
        static const res_type min_value;
        static const res_type max_value;
        static const res_type win_value;
        static const res_type lost_value;
        static const res_type draw_value;
        virtual const res_type evaluate(const board * board, const piece::color_type) = 0;
    }; 
}