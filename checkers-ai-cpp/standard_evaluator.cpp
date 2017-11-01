#include <climits>

#include "standard_evaluator.h"

namespace checkers_AI {

    const int standard_evaluator::min_value = INT_MIN;
    const int standard_evaluator::max_value = INT_MAX;
    const int standard_evaluator::win_value = 1000;
    const int standard_evaluator::lost_value = -1000;
    const int standard_evaluator::draw_value = 0;

    standard_evaluator::standard_evaluator() {
    }

    standard_evaluator::~standard_evaluator() {
    }

    const int standard_evaluator::evaluate(const board * board, piece::color_type color) {
        int score = board->stat->r - board->stat->b + 10 * (board->stat->R - board->stat->B);
        return color == piece::color_type::RED ? score : -score;
    }
}