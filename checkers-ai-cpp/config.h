#pragma once

namespace checkers_AI {
    
    //
    // ─── BOARD PARAMETERS ───────────────────────────────────────────────────────────
    //

    const int board_width = 10; /**< Width of the board */
    const int board_height = 10; /**< height of the board */
    const int board_max_dim = board_width > board_height ? board_width : board_height; /**< Maximum of the height and the width of the board */

    //
    // ───────────────────────────────────────────────────────── BOARD PARAMETERS ─────
    //

    //
    // ─── GAME PARAMETERS ────────────────────────────────────────────────────────────
    //
    
    const int max_non_captures = 50; /**< Maximum number of non capturing moves before the game is drawn */

    //
    // ────────────────────────────────────────────────────────── GAME PARAMETERS ─────
    //
}
