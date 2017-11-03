#pragma once

#include "evaluator.h"

namespace checkers_AI {
    class default_evaluator : public evaluator<int>
    {
    public:
        default_evaluator();
        ~default_evaluator();

        const int evaluate(const board* board, const piece::color_type color);
    };
}