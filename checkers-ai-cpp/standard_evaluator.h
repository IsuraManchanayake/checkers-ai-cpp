#pragma once

#include "evaluator.h"

namespace checkers_AI {
    class standard_evaluator : public evaluator<int>
    {
    public:
        standard_evaluator();
        ~standard_evaluator();

        const int evaluate(const board* board, const piece::color_type color);
    };
}