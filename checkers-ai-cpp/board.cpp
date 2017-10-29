#include <algorithm>
#include <ostream>

#include "board.h"

namespace checkers_AI {

    board::board() {
        for (int i = 0; i < board_height; i++) {
            for (int j = 0; j < board_width; j++) {
                _board[i][j] = piece::make_empty();
            }
        }
        int count = 0;
        for (int i = 0; i < board_height / 2 - 1; i++) {
            for (int j = !(i & 1); j < board_width; j += 2) {
                _board[i][j] = new piece(j, i, piece::color_type::RED, count++);
            }
        }
        for (int i = board_height / 2 + 1; i < board_height; i++) {
            for (int j = !(i & 1); j < board_width; j += 2) {
                _board[i][j] = new piece(j, i, piece::color_type::BLACK, count++);
            }
        }
    }


    board::~board() {}

    piece** board::operator[](const int& raw) {
        return _board[raw];
    }

    void board::execute_move(move * move) {
        if (!move->blance_piece->isEmpty) {
            _board[move->blance_piece->y][move->blance_piece->x] = piece::make_empty();
        }
        _board[move->fy][move->fx] = piece::make_empty();
        for (piece* capture_piece : move->capture_pieces) {
            _board[capture_piece->y][capture_piece->x] = piece::make_empty();
        }
        _board[move->y][move->x] = move->mover;
        move->mover->y = move->y;
        move->mover->x = move->x;
        if (move->is_promoting) {
            move->mover->isQueen = true;
        }
    }

    void board::reverse_move(move * move) {
        if (move->is_promoting) {
            move->mover->isQueen = false;
        }
        _board[move->y][move->x] = piece::make_empty();
        for (piece* captured_piece : move->capture_pieces) {
            _board[captured_piece->y][captured_piece->x] = captured_piece;
        }
        _board[move->fy][move->fx] = move->mover;
        move->mover->y = move->fy;
        move->mover->x = move->fx;
        if (!move->blance_piece->isEmpty) {
            _board[move->blance_piece->y][move->blance_piece->x] = move->blance_piece;
        }
    }

    std::vector<move*> board::list_all_moves(piece* mover) {
        std::vector<move*> moves_;
        if (!mover->isEmpty) {
            if (mover->isQueen) {
                for (int i = 0; i < 4; i++) {
                    int dx_ = 2 * (i % 2) - 1;
                    int dy_ = 2 * (i / 2) - 1;
                    for (int j = 1; j < board_max_dim; j++) {
                        int tx_ = j * dx_;
                        int ty_ = j * dy_;
                        if (_occupiable(tx_, ty_)) {
                            moves_.push_back(new move(mover, tx_, ty_));
                        }
                        else {
                            break;
                        }
                    }
                }
            }
            else {
                int dir_ = mover->color == piece::color_type::RED ? 1 : -1;
                int x0_ = mover->x + 1;
                int x1_ = mover->x - 1;
                int y_ = mover->y + dir_;
                if (_occupiable(x0_, y_)) {
                    moves_.push_back(new move(mover, x0_, y_));
                }
                if (_occupiable(x1_, y_)) {
                    moves_.push_back(new move(mover, x1_, y_));
                }
            }
            _list_more_captures(mover, moves_, std::vector<piece*>());
        }
        return moves_;
    }

    void board::_list_more_captures(piece* mover, std::vector<move*>& moves, std::vector<piece*>& captured) {
        if (!mover->isEmpty) {
            if (mover->isQueen) {
                for (int i = 0; i < 4; i++) {
                    int dx_ = 2 * (i % 2) - 1;
                    int dy_ = 2 * (i / 2) - 1;
                    for (int j = 2; j < board_max_dim; j++) {
                        int cx_ = mover->x + (j - 1) * dx_;
                        int cy_ = mover->y + (j - 1) * dy_;
                        int tx_ = cx_ + dx_;
                        int ty_ = cy_ + dy_;
                        if (_occupiable(tx_, ty_) && !_board[cy_][cx_]->isEmpty && _board[cy_][cx_]->color != mover->color) {
                            captured.push_back(_board[cy_][cx_]);
                            for (; _occupiable(tx_, ty_); tx_ += dx_, ty_ += dy_) {
                                move* move_ = new move(mover, tx_, ty_, captured);
                                moves.push_back(move_);
                                execute_move(move_);
                                _list_more_captures(mover, moves, captured);
                                reverse_move(move_);
                            }
                            captured.pop_back();
                        }
                        else {
                            break;
                        }
                    }
                }
            }
            else {
                for (int i = 0; i < 4; i++) {
                    int dx_ = 2 * (i % 2) - 1;
                    int dy_ = 2 * (i / 2) - 1;
                    int cx_ = mover->x + dx_;
                    int cy_ = mover->y + dy_;
                    int tx_ = cx_ + dx_;
                    int ty_ = cy_ + dy_;
                    if (_occupiable(tx_, ty_) && !_board[cy_][cx_]->isEmpty && _board[cy_][cx_]->color != mover->color) {
                        captured.push_back(_board[cy_][cx_]);
                        move* move_ = new move(mover, tx_, ty_, captured);
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
        return moves;
    }

    bool board::_validate_position(const int & x, const int & y) const {
        return x >= 0 && x < board_width && y >= 0 && y < board_height;
    }

    bool board::_occupiable(const int & x, const int & y) const {
        return _validate_position(x, y) && _board[x][y]->isEmpty;
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