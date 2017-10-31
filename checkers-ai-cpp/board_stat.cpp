#include "board_stat.h"

namespace checkers_AI {

    board_stat::board_stat() {
    }


    board_stat::~board_stat() {
    }

    board_stat & board_stat::operator+=(const piece * piece) {
        if (!piece->is_empty) {
            if (piece->is_queen) {
                piece->color == piece::color_type::RED ? R++ : B++;
            }
            else {
                piece->color == piece::color_type::RED ? r++ : b++;
            }
        }
        return *this;
    }

    board_stat & board_stat::operator-=(const piece * piece) {
        if (!piece->is_empty) {
            if (piece->is_queen) {
                piece->color == piece::color_type::RED ? R-- : B--;
            }
            else {
                piece->color == piece::color_type::RED ? r-- : b--;
            }
        }
        return *this;
    }

    board_stat & board_stat::operator+=(const move * move) {
        for (piece* capture_piece : move->capture_pieces) {
            *this -= capture_piece;
        }
        if (!move->blance_piece->is_empty) {
            *this -= move->blance_piece;
        }
        if (move->is_promoting) {
            move->mover->color == piece::color_type::RED ? r--, R++ : b--, B++;
        }
        return *this;
    }

    board_stat & board_stat::operator-=(const move * move) {
        for (piece* capture_piece : move->capture_pieces) {
            *this += capture_piece;
        }
        if (!move->blance_piece->is_empty) {
            *this += move->blance_piece;
        }
        if (move->is_promoting) {
            move->mover->color == piece::color_type::RED ? r++, R-- : b++, B--;
        }
        return *this;
    }

    const int board_stat::get_count(piece::color_type color) {
        return color == piece::color_type::RED ? r + R : b + B;
    }

    std::ostream & operator<<(std::ostream & os, board_stat *& stat) {
        os << "board statistics - [r:" << stat->r << "][b:" << stat->b << "][R:" 
           << stat->R << "][B:" << stat->B << "]" << std::endl
           << "total pieces - red: " << stat->get_count(piece::color_type::RED) << " black: " << stat->get_count(piece::color_type::BLACK);
        return os;
    }
}