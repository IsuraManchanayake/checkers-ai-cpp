#include <climits>

#include "nero_evaluator.h"

namespace checkers_AI {
    const float nero_evaluator::min_value = FLT_MIN;
    const float nero_evaluator::max_value = FLT_MAX;
    const float nero_evaluator::win_value = 1000.0f;
    const float nero_evaluator::lost_value = -1000.0f;
    const float nero_evaluator::draw_value = 0.0f;

    nero_evaluator::nero_evaluator() {
    }

    nero_evaluator::~nero_evaluator() {
    }

    const float nero_evaluator::evaluate(board * board, const piece::color_type color) {
        float red_score_ = 0.0;
        float black_score_ = 0.0;
        for (int y = 0; y < board_height; y++) {
            for (int x = !(y & 1); x < board_width; x++) {
                piece* piece_ = (*board)[y][x];
                if (!piece_->is_empty) {
                    (color == piece::color_type::red ? red_score_ : black_score_) += _eval_piece_position(board, piece_);
                }
            }
        }
        return color == piece::color_type::red ? red_score_ - black_score_ : black_score_ - red_score_;
    }

    const float nero_evaluator::_eval_piece_position(board* board, piece * piece) {
        float piece_value_;
        if (piece->is_queen) {
            piece_value_ = 10.0;
        }
        else {
            piece_value_ = 1.0;
            int bottom_end_ = piece->color == piece::color_type::red ? 0 : board_height - 1;
            int rank_ = std::abs(piece->pos.y - bottom_end_);
            piece_value_ *= (1 + (rank_ * 0.5f) / board_height);
            if (piece->pos.x == 0 || piece->pos.x == board_width - 1) {
                piece_value_ *= 1.5f;
            }
        }
        int incr_ = piece->color == piece::color_type::red ? 1 : -1;
        vec bkp_1_ = piece->pos - vec(-1, incr_);
        vec bkp_2_ = piece->pos - vec(1, incr_);
        if (_validate(bkp_1_) && (*board)[bkp_1_]->color == piece->color) {
            piece_value_ *= 1.1f;
        }
        if (_validate(bkp_2_) && (*board)[bkp_2_]->color == piece->color) {
            piece_value_ *= 1.1f;
        }
        return piece_value_;
    }

    const bool nero_evaluator::_validate(const vec & pos) {
        return pos.x > 0 && pos.x < board_width && pos.y > 0 && pos.y < board_height;
    }
}