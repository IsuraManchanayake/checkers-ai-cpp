#pragma once

#include <ostream>
#include <vector>

#include "vec.h"

namespace checkers_AI {
    /**
     * @brief A piece in the game checkers is represented by checkers_AI::piece.
     * 
     * A piece has it's own identity (id) and co-ordinate (pos) in the board. A piece has 
     * one of two colors (red or black) and it might be a man or a queen. A man can move
     * to front left direction or front right direction while a queen can move to any of
     * the four diagonal directions. Movements are possible only if the target square and
     * the intermediate squares are not occupied by any other piece. Both men and queens
     * can capture opposite color pieces by jumping over them to any of the four diagonal
     * directions. Men jumps over by only one square when capturing and queens can jump as
     * long as she is not blocked by any other piece. Pieces can capture other pieces 
     * recursively in a single move.
     * 
     * Empty squares of the board is represented by an empty piece. An empty piece is a
     * constant piece with predefined position (0, 0) and empty color.
     */
    class piece {
    public:
        //
        // ─── ENUMS ───────────────────────────────────────────────────────
        //

        /**
         * @brief Color type of a piece.
         * 
         */
        enum class color_type {
            empty,
            red,
            black
        };

        //
        // ───────────────────────────────────────────────────── ENUMS ─────
        //

            
        //
        // ─── CONSTRUCTORS AND FACTORIES ──────────────────────────────────
        //

        /**
         * @brief Creates a piece with given x, y co-ordinates, color and an identifier.
         * 
         * @param x x co-ordinate.
         * @param y y co-ordinate.
         * @param col Color of the piece.
         * @param id Identifier of the piece.
         */
        piece(const int x, const int y, const color_type col, const int id);

        /**
         * @brief Creates a piece with given co-ordinate, color and an identifier.
         * 
         * @param v Co-ordinate vector.
         * @param col Color of the piece.
         * @param id Identifier of the piece.
         */
        piece(const vec& v, const color_type col, const int id);

        /**
         * @brief Returns the singleton empty piece.
         * 
         * Empty squares of the board is represented by an empty piece. Empty piece is
         * a constant piece with (0, 0) as it's position, color_type::empty as it's color,
         * -1 as it's identifier, true as it's is_empty, false as it's is_queen.
         * 
         * @return piece* Pointer to constant singleton empty piece.
         */
        static piece* make_empty();
        
        /**
         * @brief Creates a piece with given character representation for a piece.
         * 
         * char representations
         * ====================
         * 'r' - red man
         * 'R' - red queen
         * 'b' - black man
         * 'B' - black queen
         * ' ' - empty piece
         * 
         * @param v Co-ordinate of the piece
         * @param char_repr Character representation of the piece
         * @param id Identifier of the piece.
         * @return piece* Created piece pointer.
         */
        static piece* create_piece(const vec& v, const char char_repr, const int id);

        //
        // ──────────────────────────────── CONSTRUCTORS AND FACTORIES ─────
        //


        //
        // ─── ATTRIBUTES ──────────────────────────────────────────────────
        //

        /**
         * @brief Co-ordinate vector of the position of the piece on the board.
         * 
         */
        vec pos;

        /**
         * @brief Identifier of the piece set at it's creation.
         * 
         */
        int id;

        /**
         * @brief Man/queen status of the piece.
         * 
         */
        bool is_queen = false;

        /**
         * @brief Empty status of the piece. Note: is_empty = true only for piece::_empty_piece
         * 
         */
        bool is_empty = false;

        /**
         * @brief Color of the piece.
         * 
         */
        color_type color;

        //
        // ──────────────────────────────────────────────── ATTRIBUTES ─────
        //

    private:
        /**
         * @brief Creates an piece but with default values.
         * 
         */
        piece();

        /**
         * @brief The singleton empty piece object.
         * 
         */
        static piece* _empty_piece;
    };

    //
    // ─── OPERATOR OVERLOADS ─────────────────────────────────────────────────────────
    //

    /**
     * @brief Writes a piece object to given ostream. Red color is used for red pieces and blue 
     * is used for black pieces. 
     * 
     * @param os ostream to write.
     * @param piece piece pointer to write.
     * @return std::ostream& Written ostream.
     */
    std::ostream& operator<<(std::ostream& os, piece* piece);

    /**
     * @brief Flips the color from black to red and vice versa.
     * 
     * @param color Color to flip.
     * @return piece::color_type Flipped color.
     */
    piece::color_type operator!(const piece::color_type color);

    //
    // ─────────────────────────────────────────────────────── OPERATOR OVERLOADS ─────
    //
}
