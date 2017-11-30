#pragma once

#include "evaluator.h"

namespace checkers_AI {
    class nero_evaluator : public evaluator<float>
    {
    public:
        const float evaluate(board* board, const piece::color_type color) const ;
    private:
        const float _eval_piece_position(board* board, piece* piece) const ;
        const bool _validate(const vec& pos) const ;
    };
}