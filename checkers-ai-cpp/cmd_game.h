#pragma once

#include <iostream>

#include "default_evaluator.h"
#include "game_bot.h"

namespace checkers_AI {
    template<typename eval_type = default_evaluator>
    struct cmd_game {
        cmd_game();
        ~cmd_game();

        game_bot<eval_type>* bot;

        void start_game();
    };

    template<typename eval_type>
    inline cmd_game<eval_type>::cmd_game() {
        bot = new game_bot<eval_type>(game_bot<eval_type>::color_type::red);
    }

    template<typename eval_type>
    inline cmd_game<eval_type>::~cmd_game() {
        delete bot;
    }

    template<typename eval_type>
    inline void cmd_game<eval_type>::start_game() {
        while (true) {
            if (bot->current == bot->bot_color) {
                move bot_move_ = bot->get_next_move();
                std::cout << std::endl << "Bot moved " << bot_move_ << std::endl << std::endl
                    << "Elapsed time: " << bot->elapsed_time / 1000.0 << " ms" << std::endl
                    << "Average time: " << bot->avg_time / 1000.0 << " ms" << std::endl
                    << "Evaluated nodes: " << bot->last_evaluated_nodes << std::endl
                    << "Average time per node: " << bot->avg_time_per_node / 1000.0 << " ms" << std::endl
                    << std::endl;
            }
            else {
                std::cout << bot->_board << std::endl;
                std::vector<move> user_moves_ = bot->list_all_user_moves();
                for (unsigned int i = 0; i < user_moves_.size(); i++) {
                    std::cout << i << ": " << user_moves_[i] << std::endl;
                }
                std::cout << "Enter your move: ";
                unsigned int user_move_id_;
                std::cin >> user_move_id_;
                while (user_move_id_ < 0 || user_move_id_ >= user_moves_.size()) std::cin >> user_move_id_;
                bot->execute_move(user_moves_[user_move_id_]);
            }
        }
    }

}