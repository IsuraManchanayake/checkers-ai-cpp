#include "standard_evaluator.h"

namespace checkers_AI {

    standard_evaluator::standard_evaluator() {
    }

    standard_evaluator::~standard_evaluator() {
    }

    const int standard_evaluator::evaluate(const board * board, piece::color_type color) {
        int score = board->stat->r - board->stat->b + 10 * (board->stat->R - board->stat->B);
        return color == piece::color_type::RED ? score : -score;
    }
}