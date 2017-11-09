#pragma once

#include "game_bot.h"

namespace checkers_AI {
    template<typename eval_type_1, typename eval_type_2>
    struct bot_game
    {
        bot_game();
        ~bot_game();

        game_bot<eval_type_1>* red_bot;
        game_bot<eval_type_2>* black_bot;

        void start_game();
    };

    template<typename eval_type_1, typename eval_type_2>
    inline bot_game<eval_type_1, eval_type_2>::bot_game() {
        red_bot = new game_bot<eval_type_1>(piece::color_type::red);
        black_bot = new game_bot<eval_type_2>(piece::color_type::black);
    }

    template<typename eval_type_1, typename eval_type_2>
    inline bot_game<eval_type_1, eval_type_2>::~bot_game() {
        delete red_bot;
        delete black_bot;
    }

    template<typename eval_type_1, typename eval_type_2>
    inline void bot_game<eval_type_1, eval_type_2>::start_game() {
        while (true) {
            if (red_bot->current == red_bot->bot_color) {
                move red_bot_move_ = red_bot->get_next_move();
                if (!red_bot_move_.is_empty) {
                    black_bot->execute_move(red_bot_move_);
                    std::cout << std::endl
                        << "Red Bot moved " << red_bot_move_ << std::endl << std::endl
                        << "Elapsed time: " << red_bot->elapsed_time / 1000.0 << " ms" << std::endl
                        << "Average time: " << red_bot->avg_time / 1000.0 << " ms" << std::endl
                        << "Evaluated nodes: " << red_bot->last_evaluated_nodes << std::endl
                        << "Average time per node: " << red_bot->avg_time_per_node / 1000.0 << " ms" << std::endl
                        << std::endl
                        << red_bot->_board << std::endl;
                }
            }
            else {
                move black_bot_move_ = black_bot->get_next_move();
                if (!black_bot_move_.is_empty) {
                    red_bot->execute_move(black_bot_move_);
                    std::cout << std::endl
                        << "Black Bot moved " << black_bot_move_ << std::endl << std::endl
                        << "Elapsed time: " << black_bot->elapsed_time / 1000.0 << " ms" << std::endl
                        << "Average time: " << black_bot->avg_time / 1000.0 << " ms" << std::endl
                        << "Evaluated nodes: " << black_bot->last_evaluated_nodes << std::endl
                        << "Average time per node: " << black_bot->avg_time_per_node / 1000.0 << " ms" << std::endl
                        << std::endl
                        << black_bot->_board << std::endl;
                }
            }
            system("pause");
        }
    }
}