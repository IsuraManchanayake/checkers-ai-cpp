#pragma once

namespace checkers_AI {
    // board parameters
    const int board_width = 10;
    const int board_height = 10;
    const int board_max_dim = board_width > board_height ? board_width : board_height;

    // game parameters
    const int max_non_captures = 50;
}
