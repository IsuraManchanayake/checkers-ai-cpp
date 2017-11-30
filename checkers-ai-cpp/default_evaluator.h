#pragma once

#include "board.h"
#include "evaluator.h"
#include "piece.h"

namespace checkers_AI {
    /**
     * @brief The default evaluator class to evaluate heuristics in move_resolver.
     * 
     * This takes only piece counts into account by giving a score of 10 for queen
     * pieces and 1 for a man piece. The differnce of scores of the two players is
     * the result. 
     * 
     */
    class default_evaluator : public evaluator<int>
    {
    public:

        /**
         * @brief Evaluates a given board for a given player color.
         * 
         * This takes only piece counts into account by giving a score of 10 for queen
         * pieces and 1 for a man piece. The differnce of scores of the two players is
         * the result. 
         * 
         * @param board Existing board. 
         * @param color_type Color of the player.
         * @return int Evaluated heuristic value.
         */
        const int evaluate(board* board, const piece::color_type color) const;
    };
}