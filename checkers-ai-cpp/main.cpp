
#include <iostream>

#include "checkers_ai.h"
//#include <gtest/gtest.h>

using std::cout;
using std::endl;
using namespace checkers_AI;

void move_test_1() {
    board* board_ = new board();
    move* move_ = new move((*board_)[3][0], 1, 4);
    board_->execute_move(move_);
    cout << board_ << endl << endl;
    board_->reverse_move(move_);
    cout << board_ << endl;
}

void move_test_2() {
    board* board_ = new board();
    std::vector<move*> valid_moves = board_->list_all_moves();
    cout << board_ << endl;
    for (auto& move : valid_moves) {
        cout << move << endl;
    }
}

void create_board_test_1() {
    board* board_ = new board({
        { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
        { 'r', '-', 'r', '-', 'r', '-', '-', '-', '-', '-' },
        { '-', '-', '-', 'r', '-', '-', '-', '-', '-', '-' },
        { '-', '-', '-', '-', '-', '-', 'B', '-', '-', '-' },
        { '-', 'r', '-', 'r', '-', '-', '-', 'b', '-', '-' },
        { '-', '-', '-', '-', 'b', '-', 'b', '-', '-', '-' },
        { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
        { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
        { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
        { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
    });
    std::vector<move*> valid_moves = board_->list_all_moves();
    cout << board_ << endl;
    cout << board_->stat << endl;
    for (auto & move : valid_moves) {
        cout << move << endl;
        /*board->execute_move(move);
        cout << board->stat << endl;
        cout << board << endl;
        board->reverse_move(move);*/
    }
}

void move_test_3() {
    board* board_ = new board({
        // 0    1    2    3    4    5    6    7    8    9
        { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },   // 0
        { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },   // 1
        { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },   // 2
        { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },   // 3
        { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },   // 4
        { '-', '-', 'b', '-', 'r', '-', '-', '-', '-', '-' },   // 5
        { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },   // 6
        { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },   // 7
        { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },   // 8
        { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },   // 9
    });
    move* move1 = new move((*board_)[5][2], 3, 4);
    board_->execute_move(move1);
    cout << move1 << endl << board_ << endl;
    move* move2 = new move((*board_)[5][4], 3, 6);
    board_->execute_move(move2);
    cout << move2 << endl << board_ << endl;
    cout << "########################################################################################################\n";
    for (auto& move : board_->list_all_moves(move2, piece::color_type::BLACK)) {
        cout << move << endl;
        board_->execute_move(move);
        cout << board_ << endl;
        board_->reverse_move(move);
    }
}

void game_test_1() {
    cmd_game<> * game = new cmd_game<>();
    game->start_game();
}

int main(int argc, char** argv) {

    game_test_1();

    system("pause");
    return 0;
}