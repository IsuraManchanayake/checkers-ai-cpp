#pragma once

#include "board.h"

namespace checkers_AI {
    template<typename res_type>
    class evaluator {
    public:
        virtual const res_type evaluate(const board * board, const piece::color_type) = 0;
    };
}