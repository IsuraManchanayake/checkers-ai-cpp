#include <iomanip>
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

#include "piece.h"

namespace checkers_AI {

    piece* piece::_empty_piece = nullptr;

    piece::piece(const int x, const int y, const piece::color_type color, const int id)
        : pos(x, y), color(color), id(id) {
    }

    piece::piece(const vec& v, const color_type col, const int id)
        : pos(v), color(color), id(id) {
    }

    piece::piece()
        : pos(vec::zero), id(-1), color(color_type::empty) {
    }

    piece* piece::make_empty() {
        if (_empty_piece == nullptr) {
            _empty_piece = new piece();
            _empty_piece->is_empty = true;
        }
        return _empty_piece;
    }

    piece* piece::create_piece(const vec& v, const char char_repr, const int id) {
        piece* instance = new piece();
        instance->id = id;
        instance->pos = v;
        switch (char_repr) {
        case 'r':
            instance->color = color_type::red;
            instance->is_queen = false;
            break;
        case 'R':
            instance->color = color_type::red;
            instance->is_queen = true;
            break;
        case 'b':
            instance->color = color_type::black;
            instance->is_queen = false;
            break;
        case 'B':
            instance->color = color_type::black;
            instance->is_queen = true;
            break;
        default:
            instance = make_empty();
        }
        return instance;
    }

    std::ostream& operator<<(std::ostream& os, piece* piece) {
        if (piece->is_empty) {
            os << "   ";
        }
        else {
            char piece_char = piece->color == piece::color_type::red ? 'r' : 'b';
            piece_char = piece->is_queen ? piece_char ^ (1 << 5) : piece_char;
#ifdef _WIN32
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
            GetConsoleScreenBufferInfo(hstdout, &csbi);
            SetConsoleTextAttribute(hstdout, piece->color == piece::color_type::red ? 12 : 9);
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

    piece::color_type operator!(const piece::color_type color) {
        return color == piece::color_type::red ? piece::color_type::black : piece::color_type::red;
    }
}