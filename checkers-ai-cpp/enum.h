#pragma once

namespace checkers_AI {
    /**
     * @brief The result of the game at a given time.
     * 
     */
    enum class game_result {
        ndefined, /**< The result before game starts */
        play, /**< The result while the game play goes on */
        red, /**< The result after red wins */
        black, /**< The result after black wins */
        draw /**< The result after game draws */
    };
}