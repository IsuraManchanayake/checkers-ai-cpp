#pragma once

#include <iostream>

#include "standard_evaluator.h"

namespace checkers_AI {

    template <typename eval_type = standard_evaluator, typename res_type = int>
    class move_resolver
    {
        static_assert(std::is_base_of<evaluator<res_type>, eval_type>::value, "eval_type should inherit from evaluator<res_type>");
    public:
        move_resolver();
        move_resolver(const int & depth);
        ~move_resolver();

        const move* resolve(board* board, move * last_opp_move, piece::color_type color);
    private:
        eval_type * _eval;
        int _depth;

        const move * _a_b_prune(board * board, res_type alpha, res_type beta, piece::color_type color, move * last_opp_move, int depth);
    };

    template <typename eval_type, typename res_type>
    inline move_resolver<eval_type, res_type>::move_resolver() {
        _eval = new eval_type();
    }
    
    template<typename eval_type, typename res_type>
        move_resolver<eval_type, res_type>::move_resolver(const int & depth)
        : _depth(depth) {
        _eval = new eval_type();
    }

    template <typename eval_type, typename res_type>
    move_resolver<eval_type, res_type>::~move_resolver() {
        delete _eval;
    }

    template<typename eval_type, typename res_type>
    inline const move * move_resolver<eval_type, res_type>::resolve(board * board, move * last_opp_move, piece::color_type color) {
        // implement
        return new move();
    }

    template<typename eval_type, typename res_type>
    inline const move * move_resolver<eval_type, res_type>::_a_b_prune(board * board, res_type alpha, res_type beta, piece::color_type color, move * last_opp_move, int depth) {
        // implement
        return new move();
    }
}