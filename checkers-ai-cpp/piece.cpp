#include <iomanip>
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

#include "piece.h"

namespace checkers_AI {
    
    piece* piece::_empty_piece = nullptr;

    piece::piece(const int & x, const int & y, const piece::color_type& color, const int& id)
        : pos(x, y), color(color), id(id) {
    }

    piece::piece(const vec & v, const color_type & col, const int & id) 
        : pos(v), color(color), id(id) {
    }

    piece::~piece() {}

    piece* piece::make_empty() {
        if (_empty_piece == nullptr) {
            _empty_piece = new piece(0, 0, color_type::EMPTY, -1);
            _empty_piece->isEmpty = true;
        }
        return _empty_piece;
    }

    std::ostream & operator<<(std::ostream & os, piece* piece) {
        if (piece->isEmpty) {
            os << "   ";
        }
        else {
            char piece_char = piece->color == piece::color_type::RED ? 'r' : 'b';
            piece_char = piece->isQueen ? piece_char ^ (1 << 5) : piece_char;
#ifdef _WIN32
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
            GetConsoleScreenBufferInfo(hstdout, &csbi);
            SetConsoleTextAttribute(hstdout, piece->color == piece::color_type::RED ? 12: 9);
#elif __linux__
            os << "\033[" << piece->color == piece::color_type::RED ? 31 : 34 << "m";
#endif
            os << piece_char << std::left << std::setw(2) << std::setfill(' ') << piece->id;
            os.copyfmt(std::ios(NULL));
#ifdef _WIN32
            SetConsoleTextAttribute(hstdout, csbi.wAttributes);
#elif __linux__
            os << "\033[0m";
#endif
        }
        return os;
    }
}