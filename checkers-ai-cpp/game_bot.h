#pragma once

#include <chrono>
#include <vector>

#include "board.h"
#include "default_evaluator.h"
#include "move.h"
#include "move_resolver.h"

namespace checkers_AI {
    template<typename eval_type = default_evaluator>
    class game_bot
    {
    public:
        typedef piece::color_type color_type;

        game_bot(color_type bot_color);
        ~game_bot();

        board* _board;
        move last_move = move::create_empty();
        color_type bot_color;
        color_type current = color_type::red;
        int bot_move_count = 0;
        int opp_move_count = 0;
        int last_evaluated_nodes = 0;
        long long elapsed_time = 0; // micro seconds
        float avg_time_per_node = 0; // micro seconds
        float avg_time = 0; // micro seconds
        game_result gr;

        move get_next_move();
        void execute_move(const move& move);
        std::vector<move> list_all_moves(color_type color);
        std::vector<move> list_all_user_moves();
    };

    template<typename eval_type>
    inline game_bot<eval_type>::game_bot(color_type bot_color)
        : bot_color(bot_color) {
        _board = new board();
    }

    template<typename eval_type>
    inline game_bot<eval_type>::~game_bot() {
        delete _board;
    }

    template<typename eval_type>
    inline move game_bot<eval_type>::get_next_move() {
        if (current == bot_color) {
            move_resolver<eval_type> resolver_;
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            move move_ = resolver_.resolve(_board, last_move, bot_color);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            last_evaluated_nodes = resolver_.evaluated;
            last_move = move_;
            _board->execute_move(move_);
            bot_move_count++;
            current = !current;

            elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
            avg_time = (avg_time * (bot_move_count - 1) + elapsed_time) / bot_move_count;
            if (last_evaluated_nodes > 0)
                avg_time_per_node = (avg_time_per_node * (bot_move_count - 1) + elapsed_time / last_evaluated_nodes) / bot_move_count;

            return move_;
        }
        return move::create_empty();
    }

    template<typename eval_type>
    inline void game_bot<eval_type>::execute_move(const move& move) {
        if (current != bot_color) {
            _board->execute_move(move);
            opp_move_count++;
            last_move = move;
            current = !current;
        }
    }

    template<typename eval_type>
    inline std::vector<move> game_bot<eval_type>::list_all_moves(color_type color) {
        return _board->list_all_moves(last_move, color);
    }

    template<typename eval_type>
    inline std::vector<move> game_bot<eval_type>::list_all_user_moves() {
        return _board->list_all_moves(last_move, !bot_color);
    }
}