#pragma once

#include <ostream>

namespace checkers_AI {
    /**
     * @brief A 2D co-ordinate in the checkers_AI::board is represented by a checkers_AI::vec.
     * 
     * vec origin is the upper left corner of the board.
     */
    struct vec
    {
    public:

        //
        // ─── CONSTRUCTORS ────────────────────────────────────────────────
        //

        /**
         * @brief Creates a co-ordinate vector with x and y values given.
         * 
         * @param x Horizontal co-ordinate value. Increases in the direction of right.
         * @param y Vertical co-ordinate value. Increases in the direction of down.
         */
        vec(const int& x, const int& y);

        //
        // ────────────────────────────────────────────── CONSTRUCTORS ─────
        //


        //
        // ─── OPERATOR OVERLOADS ──────────────────────────────────────────
        //

        /**
         * @brief Adds two co-ordinates to make a new vector same as vector addition.
         * 
         * @param lhs First co-rodinate to add.
         * @param rhs Second co-ordinate to add.
         * @return vec Addition of the two co-rodinates.
         */
        friend vec operator+(vec lhs, const vec& rhs);

        /**
         * @brief Substracts two co-ordinates to make a new vector same as vector difference.
         * 
         * @param lhs Co-ordinate to substract from.
         * @param rhs Co-ordinate substracting.
         * @return vec Difference of the two co-rodinates.
         */
        friend vec operator-(vec lhs, const vec& rhs);

        /**
         * @brief Multiplies a co-ordinate by an integer same as vector multiplication.
         * 
         * @param lhs Multiplication factor.
         * @param rhs Co-ordinate to multiply.
         * @return vec Product after multiplication.
         */
        friend vec operator*(const int& lhs, vec rhs);

        /**
         * @brief Multiplies a co-ordinate by an integer same as vector multiplication.
         * 
         * @param lhs Co-ordinate to multiply.
         * @param rhs Multiplication factor.
         * @return vec Product after multiplication.
         */
        friend vec operator*(vec lhs, const int& rhs);

        /**
         * @brief Writes co-ordinate to given ostream.
         * 
         * @param os ostream to write.
         * @param rhs vec object to write.
         * @return std::ostream& Written ostream.
         * 
         * @example std::cout << vec(3, 4) << std::end; would print (3, 4) in the console.
         */
        friend std::ostream& operator<<(std::ostream& os, const vec& rhs);

        /**
         * @brief Addition assignment with another vector.
         * 
         * @param rhs Co-ordinate to add.
         * @return vec& Result co-ordinate.
         */
        vec & operator+=(const vec & rhs);

        //
        // ──────────────────────────────────────── OPERATOR OVERLOADS ─────
        //


        //
        // ─── ATTRIBUTES ──────────────────────────────────────────────────
        //
            
        /**
         * @brief Horizontal value of the co-ordinate. 
         * 
         * Increases in the direction of right.
         */
        int x;

        /**
         * @brief Vertical value of the co-ordinate.
         * 
         * Increases in the direction of down.
         */
        int y;
        
        //
        // ──────────────────────────────────────────────── ATTRIBUTES ─────
        //


        //
        // ─── CONSTANTS ───────────────────────────────────────────────────
        //
            
        /**
         * @brief Constant unit vector. Here x = y = 1.
         * 
         */
        static const vec one;

        /**
         * @brief Constant zero vector. Here x = y = 0.
         * 
         */
        static const vec zero;

        /**
         * @brief Constant array of 4 directional vectors.
         * 
         * dirs[0] = vec(1, 1)
         * dirs[1] = vec(1, -1)
         * dirs[2] = vec(-1, -1)
         * dirs[3] = vec(-1, 1)
         * These are the 4 valid directions a checkers_AI::piece can move
         * 
         */
        static const vec dirs[4];
        
        //
        // ───────────────────────────────────────────────── CONSTANTS ─────
        //
    };
}