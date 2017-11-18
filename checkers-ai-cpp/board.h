#pragma once

#include <ostream>
#include <vector>

#include "board_stat.h"
#include "config.h"
#include "move.h"
#include "piece.h"

namespace checkers_AI {
    /**
     * @brief The data structure which pieces are stored.
     * 
     * The indexing starts at upper left corner. All board positions with co-ordinate (x, y) and 
     * x + y % 2 == 0 are unreachable squares. An instance of board might be adequate for the 
     * whole program life time.
     * 
     */
    class board {
    public:
        /**
         * @brief Creates a board with default board position.
         * 
         */
        board();

        /**
         * @brief Creates a board with a given position provided by a 2D char array.
         * 
         * Use following characters when passing.
         *      'r' - red man
         *      'b' - black man
         *      'R' - red queen
         *      'B' - black queen
         *      '-' - empty piece
         * 
         * @param char_repr Given position as a 2D char array 
         */
        board(const char (&char_repr)[board_height][board_width]);

        /**
         * @brief Destructs the board along with the pieces and board statistics.
         * 
         */
        ~board();

        /**
         * @brief Keeps track of the number of pieces on the board.
         * 
         * This can be used in evaluators. 
         * 
         */
        board_stat* stat = new board_stat();

        /**
         * @brief Retrieves a raw of the board as an array.
         * 
         * @param raw The raw position.
         * @return piece** The raw of board with the given position.
         */
        piece** operator[](const int& raw);

        /**
         * @brief Executes a move in the board.
         * 
         * Use with caution. The validity of the move is not checked.
         * 
         * @param move Move to execute
         */
        void execute_move(const move& move);

        /**
         * @brief Reverse the move in the board.
         * 
         * Use with caution. The validity of the move is not checked.
         * 
         * @param move Move to reverse.
         */
        void reverse_move(const move& move);

        /**
         * @brief Lists down all the possible moves for a given last opponent move and a specific piece.
         * 
         * Piece color of the mover of the last_move and color of the piece must be different. Otherwise
         * undefined behaviours might occur. 
         * 
         * @param last_move Opponent's last move.
         * @param piece The specific piece to list moves.
         * @return std::vector<move> Listed moves.
         */
        std::vector<move> list_all_moves(const move& last_move, piece* piece);

        /**
         * @brief Lists down all the possible moves for a given last opponent move and a speicific player color.
         * 
         * Piece color of the mover of the last_move and color must be different. Otherwise undefined
         * behaviours might occur.
         * 
         * @param last_move Opponent's last move.
         * @param color The specific player color to list moves.
         * @return std::vector<move> Listed moves.
         */
        std::vector<move> list_all_moves(const move& last_move, piece::color_type color);

        /**
         * @brief Lists down all the possible blance pieces for a given last opponent move.
         * 
         * @param last_move Opponent's last move.
         * @return std::vector<piece*> Listed blance-able pieces.
         */
        std::vector<piece*> list_blance_pieces(const move& last_move);

        /**
         * @brief Setter for board indexed by a co-ordinate vector.
         * 
         * @param pos Position co-ordinate vector.
         * @return piece*& Settable piece of the board.
         */
        piece* & operator[](const vec & pos);

        /**
         * @brief Getter for board indexed by a co-ordinate vector.
         * 
         * @param pos Position co-ordinate vector.
         * @return piece* Gettable const piece of the board.
         */
        piece* operator[](const vec & pos) const;

    private:
        /**
         * @brief The 2D array of piece pointers
         * 
         */
        piece* _board[board_height][board_width];

        /**
         * @brief Validates the position that the it is inside the board.
         * 
         * Use with caution because this does not guarantee the position (x, y) follows x + y % 2 == 1.
         * 
         * @param pos Co-ordinate vector to validate.
         * @return bool Validity of the co-oridinate vector.
         */
        bool _validate_position(const vec & pos) const;

        /**
         * @brief Validates the position that it is inside the board and it is empty.
         * 
         * Use with caution because this does not guarantee the position (x, y) follows x + y % 2 == 1
         * 
         * @param pos Co-ordinate vector to validate
         * @return bool Validity of the co-oridinate vector. 
         */
        bool _occupiable(const vec & pos) const;

        /**
         * @brief A helper recursive function that checks captures of a piece that outs a list possible of moves with captures.  
         * 
         * @param mover The piece to check captures.
         * @param start Starting position of the mover piece.
         * @param moves List of possible moves to fill-in after incoming captures.
         * @param captures Captured pieces so far.
         */
        void _list_more_captures(piece* mover, const vec start, std::vector<move>& moves, std::vector<piece*> captures);

        /**
         * @brief Checks that captures are available for a piece.
         * 
         * Use to check a piece blance-able.  
         * 
         * @param mover Piece to check.
         * @return bool Availability of at least single capture.
         */
        bool _check_captures_available(piece* mover);

        /**
         * @brief Exectutes a move in the board.
         * 
         * Use with caution because this does not updates board statistics ie. piece counts. Use execute_move 
         * instead to update board stat along with.
         * 
         * @param move Move to execute.
         */
        void _execute_move(const move& move);

        /**
         * @brief Reverses a move in the board.
         * 
         * Use with caution because this does not updates board statistics ie. piece counts. Use execute_move 
         * instead to update board stat along with.
         * 
         * @param move Move to reverse.
         */
        void _reverse_move(const move& move);

        /**
         * @brief Lists all possible moves without considering the last opponent move ie. result does not have blance
         * pieces.
         * 
         * @param color Player's color.
         * @return std::vector<move> List of all possible moves without blance pieces.
         */
        std::vector<move> _list_all_raw_moves(piece::color_type color);

        /**
         * @brief Lists all possible moves for a piece without considering the last opponent move ie. result does not 
         * have blance pieces.
         * 
         * @param piece Piece to check moves.
         * @return std::vector<move> List of all possible moves without blance pieces.
         */
        std::vector<move> _list_all_raw_moves(piece* piece);
    };

    /**
     * @brief Writes a board to a given ostream.
     * 
     * @param os ostream to write.
     * @param board Board to write.
     * @return std::ostream& Written ostream.
     */
    std::ostream& operator<<(std::ostream& os, board* board);
}

