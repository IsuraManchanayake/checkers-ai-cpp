#include <iostream>

#include "checkers_ai.h"

using namespace std;

int main() {
	checkers_AI::board* board = new checkers_AI::board();
	checkers_AI::move* move = new checkers_AI::move((*board)[3][0], 1, 4);
	board->execute_move(move);
	cout << board << endl;

	system("pause");
	return 0;
}