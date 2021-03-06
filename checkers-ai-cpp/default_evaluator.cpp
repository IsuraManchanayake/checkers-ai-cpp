#include <climits>

#include "default_evaluator.h"

namespace checkers_AI {

    const int default_evaluator::min_value = INT_MIN;
    const int default_evaluator::max_value = INT_MAX;
    const int default_evaluator::win_value = 1000;
    const int default_evaluator::lost_value = -1000;
    const int default_evaluator::draw_value = 0;

    const int default_evaluator::evaluate(board* board, const piece::color_type color) const {
        int score = board->stat.r - board->stat.b + 10 * (board->stat.R - board->stat.B);
        return color == piece::color_type::red ? score : -score;
    }
}