
#include <iostream>

#include "checkers_ai.h"
//#include <gtest/gtest.h>

using namespace std;

//TEST(Hello, World) {
//    checkers_AI::board board;
//    auto a = checkers_AI::piece::make_empty();
//    auto b = board[0][0];
//    cout << a << endl;
//    cout << b << endl;
//    EXPECT_EQ(checkers_AI::piece::make_empty(), board[0][0]);
//}

void move_test_1() {
    checkers_AI::board* board = new checkers_AI::board();
    checkers_AI::move* move = new checkers_AI::move((*board)[3][0], 1, 4);
    board->execute_move(move);
    cout << board << endl << endl;
    board->reverse_move(move);
    cout << board << endl;
}

void move_test_2() {
    checkers_AI::board* board = new checkers_AI::board();
    std::vector<checkers_AI::move*> valid_moves = board->list_all_moves();
    cout << board << endl;
    for (auto& move : valid_moves) {
        cout << move << endl;
    }
}

int main(int argc, char** argv) {

    move_test_2();

    system("pause");
    return 0;

    //testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
}