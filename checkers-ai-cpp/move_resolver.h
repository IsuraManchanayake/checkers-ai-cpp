#pragma once

#include <algorithm>
#include <random>

#include "board.h"
#include "enum.h"
#include "default_evaluator.h"
#include "evaluator.h"
#include "move.h"
#include "piece.h"

namespace checkers_AI {

    template <typename eval_type = default_evaluator>
    class move_resolver
    {
        static_assert(std::is_base_of<evaluator<typename eval_type::res_type>, eval_type>::value,
            "eval_type should inherit from evaluator<eval_type::res_type>");
    public:
        move_resolver(const int & depth);
        move_resolver();
        ~move_resolver();

        int evaluated = 0;

        typedef typename eval_type::res_type res_type;
        move resolve(board * board, const move& last_opp_move, piece::color_type color);
    private:
        eval_type * _eval;
        int _depth = 5;
        piece::color_type _color;

        const res_type _a_b_prune(board * board, res_type alpha, res_type beta, piece::color_type color, const move& last_opp_move, int depth);
    };

    template<typename eval_type>
    move_resolver<eval_type>::move_resolver(const int & depth)
        : _depth(depth) {
        _eval = new eval_type();
    }

    template <typename eval_type>
    inline move_resolver<eval_type>::move_resolver() {
        _eval = new eval_type();
    }

    template <typename eval_type>
    move_resolver<eval_type>::~move_resolver() {
        delete _eval;
    }

    template<typename eval_type>
    inline move move_resolver<eval_type>::resolve(board * board, const move& last_opp_move, piece::color_type color) {
        _color = color;
        std::vector<move> valid_moves_ = board->list_all_moves(last_opp_move, color);
        if (std::any_of(valid_moves_.cbegin(), valid_moves_.cend(),
            [](const move& move) { return move.move_kind == move::move_kind_type::capture; })) {
            valid_moves_.erase(std::remove_if(valid_moves_.begin(), valid_moves_.end(),
                [](const move& move) { return move.move_kind == move::move_kind_type::move; }), valid_moves_.end());
        }
        sort(valid_moves_.begin(), valid_moves_.end(),
            [](const move& move_1, const move& move_2) { return move_1.capture_pieces.size() > move_2.capture_pieces.size(); });
        move best_move_ = move::create_empty();
        res_type alpha_ = eval_type::min_value;
        res_type beta_ = eval_type::max_value;
        std::shuffle(valid_moves_.begin(), valid_moves_.end(), std::default_random_engine(std::random_device()()));
        for (auto & move : valid_moves_) {
            board->execute_move(move);
            res_type v_ = _a_b_prune(board, alpha_, beta_, !color, move, _depth - 1);
            board->reverse_move(move);
            if (v_ > alpha_) {
                alpha_ = v_;
                best_move_ = move;
            }
        }
        return best_move_;
    }

    template<typename eval_type>
    inline const typename eval_type::res_type
        move_resolver<eval_type>::_a_b_prune(board * board, res_type alpha, res_type beta, piece::color_type color, const move& last_opp_move, int depth) {
        game_result gr_ = board->stat->get_board_result();
        if (gr_ == game_result::black) {
            return color == piece::color_type::black ? eval_type::win_value : eval_type::lost_value;
        }
        else if (gr_ == game_result::red) {
            return color == piece::color_type::red ? eval_type::win_value : eval_type::lost_value;
        }
        if (depth == 0) {
            evaluated++;
            return _eval->evaluate(board, color);
        }
        std::vector<move> valid_moves_ = board->list_all_moves(last_opp_move, color);
        if (valid_moves_.size() == 0) {
            return eval_type::draw_value;
        }
        if (color == _color) {
            res_type v_ = eval_type::min_value;
            sort(valid_moves_.begin(), valid_moves_.end(), 
                [](const move& move_1, const move& move_2) { return move_1.capture_pieces.size() > move_2.capture_pieces.size(); });
            for (auto & move : valid_moves_) {
                board->execute_move(move);
                res_type best_ = _a_b_prune(board, alpha, beta, !color, move, depth - 1);
                if (v_ < best_) {
                    v_ = best_;
                }
                board->reverse_move(move);
                if (alpha < v_) {
                    alpha = v_;
                }
                if (alpha >= beta) {
                    return alpha;
                }
            }
            return v_;
        }
        else {
            res_type v_ = eval_type::max_value;
            sort(valid_moves_.begin(), valid_moves_.end(),
                [](const move& move_1, const move& move_2) { return move_1.capture_pieces.size() < move_2.capture_pieces.size(); });
            for (auto & move : valid_moves_) {
                board->execute_move(move);
                res_type best_ = _a_b_prune(board, alpha, beta, !color, move, depth - 1);
                if (v_ > best_) {
                    v_ = best_;
                }
                board->reverse_move(move);
                if (beta > v_) {
                    beta = v_;
                }
                if (alpha >= beta) {
                    return beta;
                }
            }
            return v_;
        }
    }
}