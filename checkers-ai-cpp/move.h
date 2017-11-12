#pragma once

#include <ostream>
#include <vector>

#include "piece.h"

namespace checkers_AI {
    /**
     * @brief A single move is represented by checkers_AI::move.
     * 
     * The rules for piece movements are described in checkers_AI::piece.
     * A move can include a blance piece. If the opponent could capture a piece(s)
     * but he didn't, the other player can take out the piece which could capture
     * other piece(s) out of the board and move normally. 
     * 
     * If a man move to last row, the piece turns into a queen. This is called 
     * promoting. A player can make one or more queens.
     * 
     * @see checkers_AI::piece
     * 
     */
    class move {
    public:

        //
        // ─── ENUMS ───────────────────────────────────────────────────────
        //

        /**
         * @brief Types of move_kinds. This is set at the creation of a move.
         * 
         */
        enum class move_kind_type {
            move,   /**< A plain move without capture. May or may not include a blance piece. */
            capture /**< A move with one or more captures. May or may not include a blance piece. */
        };

        //
        // ───────────────────────────────────────────────────── ENUMS ─────
        //


        //
        // ─── CONSTRUCTORS AND FACTORIES ──────────────────────────────────
        //

        /**
         * @brief Creates a move with given mover and target x, y co-ordinate values.
         * 
         * @param mover Moving piece.
         * @param x x value of the target co-ordinate.
         * @param y y value of the target co-ordinate.
         */
        move(piece* mover, const int& x, const int& y);

        /**
         * @brief Creates a move with given mover and target co-ordinate vector.
         * 
         * @param mover Moving piece.
         * @param to Target co-ordinate vector.
         */
        move(piece* mover, const vec& to);

        /**
         * @brief Creates a move with given mover, target x, y co-ordinate values and list of capturing pieces. 
         * 
         * @param mover Moving piece.
         * @param x x value of the target co-ordinate.
         * @param y y value of the target co-ordinate.
         * @param capture_pieces List of capturing pieces.
         */
        move(piece* mover, const int& x, const int& y, std::vector<piece*> capture_pieces);

        /**
         * @brief Creates a move with given mover, target co-oridinate vector and list of capturing pieces.
         * 
         * @param mover Moving piece.
         * @param to Target co-ordinate vector.
         * @param capture_pieces List of capturing pieces.
         */
        move(piece* mover, const vec& to, std::vector<piece*> capture_pieces);

        /**
         * @brief Creates a move with given mover, origin co-ordinate vector, target co-ordinate vector and 
         * list of capturing pieces.
         * 
         * @param mover Moving piece.
         * @param from Origin co-ordinate vector.
         * @param to Target co-ordinate vector.
         * @param capture_pieces List of capturing pieces.
         */
        move(piece* mover, const vec& from, const vec& to, std::vector<piece*> capture_pieces);
        
        /**
         * @brief Creates/returns the singleton empty move. An empty move does nothing in it's execution or reversing. 
         * 
         * @return move Singleton empty move.
         */
        static move create_empty();

        //
        // ──────────────────────────────── CONSTRUCTORS AND FACTORIES ─────
        //

            
        //
        // ─── ATTRIBUTES ──────────────────────────────────────────────────
        //

        /**
         * @brief Moving piece.
         * 
         */
        piece* mover;

        /**
         * @brief The starting position of the move.
         * 
         * This is needed to keep track of the starting position after executing the move to reverse move.
         * 
         */
        vec from;

        /**
         * @brief The target position of the piece.
         * 
         */
        vec to;

        /**
         * @brief Blancing piece.
         * 
         * If the opponent player could capture a piece and he didn't he can remove that piece (blance piece)
         * out of the board and keep moving normally. A piece can only be blanced only if the opponent could capture
         * a piece with that piece and did not capture any other piece.
         * 
         */
        piece* blance_piece = piece::make_empty();

        /**
         * @brief List of capturing pieces.
         * 
         */
        std::vector<piece*> capture_pieces;

        /**
         * @brief If a man moves to last row, it becomes a queen. This is called promoting.
         * 
         */
        bool is_promoting = false;

        /**
         * @brief The kind of movement ie. whether it is a capturing move or a normal plain move.
         * 
         * The blance piece is not taken into consider when defining move_kind. This value is set 
         * only at the creation of the move. Do not set this after creation.
         * 
         */
        move_kind_type move_kind;

        /**
         * @brief If the move is empty, nothing is done at it's execution or reversing.
         * 
         * This is set only at it's creation. Do not set this after creation.
         * 
         */
        bool is_empty = false;

        //
        // ──────────────────────────────────────────────── ATTRIBUTES ─────
        //
    private:
        
        /**
         * @brief The singleton empty move. An empty move does nothing in it's execution or reversing.
         * 
         */
        static move* _empty_move;
    };

    /**
     * @brief Writes a move to given ostream.
     * 
     * @param os ostream to write.
     * @param move move to write.
     * @return std::ostream& Written ostream.
     */
    std::ostream& operator<<(std::ostream& os, const move& move);
}
