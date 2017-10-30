#include <iostream>
#include <ostream>

#include "board.h"

#define ITERATE_BOARD(x, y, code) \
    for(int y = 0; y < board_height; y++) { \
        for (int x = !(y & 1); x < board_width; x += 2) { \
            code \
        } \
    }

namespace checkers_AI {

    board::board() {
        for (int y = 0; y < board_height; y++) {
            for (int x = 0; x < board_width; x++) {
                _board[y][x] = piece::make_empty();
            }
        }
        int count = 0;
        for (int y = 0; y < board_height / 2 - 1; y++) {
            for (int x = !(y & 1); x < board_width; x += 2) {
                _board[y][x] = new piece(x, y, piece::color_type::RED, count++);
                *stat += _board[y][x];
            }
        }
        for (int y = board_height / 2 + 1; y < board_height; y++) {
            for (int x = !(y & 1); x < board_width; x += 2) {
                _board[y][x] = new piece(x, y, piece::color_type::BLACK, count++);
                *stat += _board[y][x];
            }
        }
    }

    board::board(const char(&char_repr)[board_height][board_width]) {
        int id = 0;
        for (int y = 0; y < board_height; y++) {
            for (int x = 0; x < board_width; x++) {
                _board[y][x] = piece::create_piece(vec(x, y), char_repr[y][x], id);
                if (!_board[y][x]->is_empty) id++;
            }
        }
    }

    board::~board() {}

    piece** board::operator[](const int& raw) {
        return _board[raw];
    }

    void board::_execute_move(move * move) {
        if (!move->blance_piece->is_empty) {
            _board[move->blance_piece->pos.y][move->blance_piece->pos.x] = piece::make_empty();
        }
        _board[move->from.y][move->from.x] = piece::make_empty();
        for (piece* capture_piece : move->capture_pieces) {
            _board[capture_piece->pos.y][capture_piece->pos.x] = piece::make_empty();
        }
        _board[move->to.y][move->to.x] = move->mover;
        move->mover->pos = move->to;
        if (move->is_promoting) {
            move->mover->is_queen = true;
        }
    }

    void board::execute_move(move * move) {
        _execute_move(move);
        *stat += move;
    }

    void board::_reverse_move(move * move) {
        if (move->is_promoting) {
            move->mover->is_queen = false;
        }
        _board[move->to.y][move->to.x] = piece::make_empty();
        for (piece* captured_piece : move->capture_pieces) {
            _board[captured_piece->pos.y][captured_piece->pos.x] = captured_piece;
        }
        _board[move->from.y][move->from.x] = move->mover;
        move->mover->pos = move->from;
        if (!move->blance_piece->is_empty) {
            _board[move->blance_piece->pos.y][move->blance_piece->pos.x] = move->blance_piece;
        }
    }

    void board::reverse_move(move * move) {
        _reverse_move(move);
        *stat -= move;
    }

    void board::_list_more_captures(piece* mover, const vec start, std::vector<move*>& moves, std::vector<piece*> captured) {
        if (!mover->is_empty) {
            if (mover->is_queen) {
                for (vec& dir : vec::dirs) {
                    for (int j = 2; j < board_max_dim; j++) {
                        vec tpos_ = mover->pos + j * dir;
                        vec cpos_ = tpos_ - dir;
                        if (_occupiable(tpos_) &&
                            !_board[cpos_.y][cpos_.x]->is_empty && _board[cpos_.y][cpos_.x]->color != mover->color) {
                            captured.push_back(_board[cpos_.y][cpos_.x]);
                            for (; _occupiable(tpos_); tpos_ += dir) {
                                move* move_ = new move(mover, start, tpos_, captured);
                                moves.push_back(move_);
                                _execute_move(move_);
                                _list_more_captures(mover, start, moves, captured);
                                _reverse_move(move_);
                            }
                            captured.pop_back();
                        }
                    }
                }
            }
            else {
                for (vec& dir : vec::dirs) {
                    vec cpos_ = mover->pos + dir;
                    vec tpos_ = cpos_ + dir;
                    if (_occupiable(tpos_) && !_board[cpos_.y][cpos_.x]->is_empty && _board[cpos_.y][cpos_.x]->color != mover->color) {
                        captured.push_back(_board[cpos_.y][cpos_.x]);
                        move* move_ = new move(mover, start, tpos_, captured);
                        moves.push_back(move_);
                        _execute_move(move_);
                        _list_more_captures(mover, start, moves, captured);
                        captured.pop_back();
                        _reverse_move(move_);
                    }
                }
            }
        }
    }

    bool board::_check_captures_available(piece * piece) {
        if (!piece->is_empty) {
            if (piece->is_queen) {
                for (vec& dir : vec::dirs) {
                    for (int j = 2; j < board_max_dim; j++) {
                        vec tpos_ = piece->pos + j * dir;
                        vec cpos_ = tpos_ - dir;
                        if (_occupiable(tpos_) && !_board[cpos_.y][cpos_.x]->is_empty && _board[cpos_.y][cpos_.x]->color != piece->color) {
                            return true;
                        }
                    }
                }
            }
            else {
                for (vec& dir : vec::dirs) {
                    vec cpos_ = piece->pos + dir;
                    vec tpos_ = cpos_ + dir;
                    if (_occupiable(tpos_) && !_board[cpos_.y][cpos_.x]->is_empty && _board[cpos_.y][cpos_.x]->color != piece->color) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    std::vector<move*> board::_list_all_raw_moves(piece::color_type color) {
        std::vector<move*> moves_;
        ITERATE_BOARD(x, y,
            if (_board[y][x]->color == color) {
                std::vector<move*> piece_moves_ = _list_all_raw_moves(_board[y][x]);
                moves_.insert(moves_.end(), piece_moves_.begin(), piece_moves_.end());
            }
        )
            return moves_;
    }

    std::vector<move*> board::_list_all_raw_moves(piece* mover) {
        std::vector<move*> moves_;
        if (!mover->is_empty) {
            if (mover->is_queen) {
                for (vec& dir : vec::dirs) {
                    for (int j = 1; j < board_max_dim; j++) {
                        vec to_ = mover->pos + j * dir;
                        if (_occupiable(to_)) {
                            moves_.push_back(new move(mover, to_));
                        }
                        else {
                            break;
                        }
                    }
                }
            }
            else {
                int dir_ = mover->color == piece::color_type::RED ? 1 : -1;
                vec to1_(mover->pos.x + 1, mover->pos.y + dir_);
                vec to2_(mover->pos.x - 1, mover->pos.y + dir_);
                if (_occupiable(to1_)) {
                    moves_.push_back(new move(mover, to1_));
                }
                if (_occupiable(to2_)) {
                    moves_.push_back(new move(mover, to2_));
                }
            }
            _list_more_captures(mover, mover->pos, moves_, std::vector<piece*>());
        }
        return moves_;
    }

    std::vector<piece*> board::list_all_blance_pieces(move* last_move) {
        std::vector<piece*> blance_pieces_;
        if (last_move->move_kind == move::move_kind_type::MOVE) {
            _reverse_move(last_move);
            ITERATE_BOARD(x, y,
                if (_board[y][x]->color != last_move->mover->color && _check_captures_available(_board[y][x])) {
                    blance_pieces_.push_back(_board[y][x]);
                }
            )
                _execute_move(last_move);
        }
        return blance_pieces_;
    }

    // Use only for testing
    std::vector<move*> board::list_all_moves() {
        std::vector<move*> red_moves_ = _list_all_raw_moves(piece::color_type::RED);
        std::vector<move*> black_moves_ = _list_all_raw_moves(piece::color_type::BLACK);
        red_moves_.insert(red_moves_.end(), black_moves_.begin(), black_moves_.end());
        return red_moves_;
    }

    std::vector<move*> board::list_all_moves(move * last_move, piece * mover) {
        std::vector<piece*> blance_pieces_ = list_all_blance_pieces(last_move);
        std::vector<move*> moves_ = _list_all_raw_moves(mover);
        for (piece* blanced_piece : blance_pieces_) {
            _board[blanced_piece->pos.y][blanced_piece->pos.x] = piece::make_empty();
            std::vector<move*> moves_after_blance_ = _list_all_raw_moves(mover);
            for (move* move_ : moves_after_blance_) {
                move_->blance_piece = blanced_piece;
            }
            moves_.insert(moves_.end(), moves_after_blance_.begin(), moves_after_blance_.end());
            _board[blanced_piece->pos.y][blanced_piece->pos.x] = blanced_piece;
        }
        return moves_;
    }

    std::vector<move*> board::list_all_moves(move * last_move) {
        std::vector<piece*> blance_pieces_ = list_all_blance_pieces(last_move);
        std::vector<move*> moves_ = _list_all_raw_moves(!last_move->mover->color);
        for (piece* blanced_piece : blance_pieces_) {
            _board[blanced_piece->pos.y][blanced_piece->pos.x] = piece::make_empty();
            std::vector<move*> moves_after_blance = _list_all_raw_moves(!last_move->mover->color);
            for (move* move_ : moves_after_blance) {
                move_->blance_piece = blanced_piece;
            }
            moves_.insert(moves_.end(), moves_after_blance.begin(), moves_after_blance.end());
            _board[blanced_piece->pos.y][blanced_piece->pos.x] = blanced_piece;
        }
        return moves_;
    }

    piece *& board::operator[](const vec & pos) {
        return _board[pos.y][pos.x];
    }

    piece * board::operator[](const vec & pos) const {
        return _board[pos.y][pos.x];
    }

    bool board::_validate_position(const vec & pos) const {
        return pos.x >= 0 && pos.x < board_width && pos.y >= 0 && pos.y < board_height;
    }

    bool board::_occupiable(const vec & pos) const {
        return _validate_position(pos) && _board[pos.y][pos.x]->is_empty;
    }

    std::ostream& operator<<(std::ostream& os, board* board) {
        os << "         ";
        for (int i = 0; i < board_width; i++) {
            os << "  " << i << "   ";
        }
        os << std::endl << "        +";
        for (int i = 0; i < board_width; i++) {
            os << "-----+";
        }
        os << std::endl;
        for (int i = 0; i < board_height; i++) {
            os << "  " << i << "(" << (char)(i + 65) << ")" << "  |";
            for (int j = 0; j < board_width; j++) {
                os << " " << (*board)[i][j] << " |";
            }
            os << std::endl << "        +";
            for (int j = 0; j < board_width; j++) {
                os << "-----+";
            }
            os << std::endl;
        }
        return os;
    }
}