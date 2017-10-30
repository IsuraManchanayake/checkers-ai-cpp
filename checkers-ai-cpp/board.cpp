#include <ostream>

#include "board.h"

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
            }
        }
        for (int y = board_height / 2 + 1; y < board_height; y++) {
            for (int x = !(y & 1); x < board_width; x += 2) {
                _board[y][x] = new piece(x, y, piece::color_type::BLACK, count++);
            }
        }
    }

    board::board(const char(&char_repr)[board_height][board_width]) {
        int id = 0;
        for (int y = 0; y < board_height; y++) {
            for (int x = 0; x < board_width; x++) {
                _board[y][x] = new piece(vec(y, x), char_repr[y][x], id);
                if (!_board[y][x]->is_empty) id++;
            }
        }
    }


    board::~board() {}

    piece** board::operator[](const int& raw) {
        return _board[raw];
    }

    void board::execute_move(move * move) {
        if (!move->blance_piece->is_empty) {
            _board[move->blance_piece->pos.y][move->blance_piece->pos.x] = piece::make_empty();
        }
        _board[move->from.y][move->from.x] = piece::make_empty();
        for (piece* capture_piece : move->capture_pieces) {
            _board[capture_piece->pos.y][capture_piece->pos.x] = piece::make_empty();
        }
        _board[move->to.y][move->to.y] = move->mover;
        move->mover->pos = move->to;
        if (move->is_promoting) {
            move->mover->is_queen = true;
        }
    }

    void board::reverse_move(move * move) {
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

    std::vector<move*> board::list_all_moves(piece* mover) {
        std::vector<move*> moves_;
        if (!mover->is_empty) {
            if (mover->is_queen) {
                for (vec& dir : vec::dirs) {
                    for (int j = 1; j < board_max_dim; j++) {
                        vec to = j * dir;
                        if (_occupiable(to)) {
                            moves_.push_back(new move(mover, to));
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
            _list_more_captures(mover, moves_, std::vector<piece*>());
        }
        return moves_;
    }

    void board::_list_more_captures(piece* mover, std::vector<move*>& moves, std::vector<piece*>& captured) {
        if (!mover->is_empty) {
            if (mover->is_queen) {
                for (vec& dir : vec::dirs) {
                    for (int j = 2; j < board_max_dim; j++) {
                        vec tpos_ = j * dir;
                        vec cpos_ = tpos_ - dir;
                        if (_occupiable(tpos_)
                            && !_board[cpos_.y][cpos_.x]->is_empty
                            && _board[cpos_.y][cpos_.x]->color != mover->color) {
                            captured.push_back(_board[cpos_.y][cpos_.x]);
                            for (; _occupiable(tpos_); tpos_ += dir) {
                                move* move_ = new move(mover, tpos_, captured);
                                moves.push_back(move_);
                                execute_move(move_);
                                _list_more_captures(mover, moves, captured);
                                reverse_move(move_);
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
                    if (_occupiable(tpos_)
                        && !_board[cpos_.y][cpos_.x]->is_empty
                        && _board[cpos_.y][cpos_.x]->color != mover->color) {
                        captured.push_back(_board[cpos_.y][cpos_.x]);
                        move* move_ = new move(mover, tpos_, captured);
                        moves.push_back(move_);
                        execute_move(move_);
                        _list_more_captures(mover, moves, captured);
                        captured.pop_back();
                        reverse_move(move_);
                    }
                }
            }
        }
    }

    std::vector<move*> board::list_all_moves() {
        std::vector<move*> moves;
        for (int y = 0; y < board_height; y++) {
            for (int x = 0; x < board_width; x++) {
                if (!_board[y][x]->is_empty) {
                    std::vector<move*> piece_moves_ = list_all_moves(_board[y][x]);
                    moves.insert(moves.end(), piece_moves_.begin(), piece_moves_.end());
                }
            }
        }
        return moves;
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