#pragma once

#include "board.h"
#include "piece.h"

namespace checkers_AI {

    /**
     * @brief The helper heuristic interface to evaluate leaf nodes of alpha beta pruning tree of the move_resolver.
     * 
     * @tparam T The result type of the heuristic. The result type must have following properties.
     *  1. A negative infinity value
     *  2. A positive infinity value.
     *  3. A value to represent winning state.
     *  4. A value to represent lost state.
     *  5. A value to represent draw state.
     *  6. Definition for all comparison operators.
     */
    template<typename T>
    class evaluator {
    public:
        typedef T res_type;

        /**
         * @brief Definition for negative infinity.
         * 
         */
        static const res_type min_value;

        /**
         * @brief Definition for positive infinity.
         * 
         */
        static const res_type max_value;

        /**
         * @brief Definition for winning state.
         * 
         */
        static const res_type win_value;

        /**
         * @brief Definition for lost state.
         * 
         */
        static const res_type lost_value;

        /**
         * @brief Definition for draw state.
         * 
         */
        static const res_type draw_value;

        /**
         * @brief Evaluates a given board for a given player color.
         * 
         * @param board Existing board. 
         * @param color_type Color of the player.
         * @return res_type Evaluated heuristic value.
         */
        virtual const res_type evaluate(board*, const piece::color_type) const = 0;
    }; 
}