#include "fen.hpp"
#include "core.hpp"
#include "position.hpp"
#include <string.h>

Position parse_fen(std::string fen) {

  int start = 0;
  int next = fen.find(' ', start);
  std::string board = fen.substr(start, next - start);
  start = next + 1;
  next = fen.find(' ', start);
  std::string side = fen.substr(start, next - start);
  start = next + 1;
  next = fen.find(' ', start);
  std::string castling = fen.substr(start, next - start);
  start = next + 1;
  next = fen.find(' ', start);
  std::string en_passant = fen.substr(start, next - start);
  start = next + 1;
  next = fen.find(' ', start);
  std::string move_since_capture = fen.substr(start, next - start);
  start = next + 1;
  next = fen.find('\0', start);
  std::string move = fen.substr(start, next - start);

  Position position{};

  uint8_t row = 7;
  uint8_t col = 0;
  for (char curr : board) {
    if (curr == '/') {
      row -= 1;
      col = 0;
    } else if (curr >= '0' && curr <= '9') {
      int moveCols = curr - '0';
      col += moveCols;
    } else {
      Piece piece;
      if (curr == 'r' || curr == 'R') {
        piece = ROOK;
      } else if (curr == 'b' || curr == 'B') {
        piece = BISHOP;
      } else if (curr == 'k' || curr == 'K') {
        piece = KING;
      } else if (curr == 'n' || curr == 'N') {
        piece = KNIGHT;
      } else if (curr == 'Q' || curr == 'q') {
        piece = QUEEN;
      } else if (curr == 'p' || curr == 'P') {
        piece = PAWN;
      } else {
        piece = NO_PIECE;
        fce_error("Could\'t read fen position", 1);
      }
      Color color = (curr >= 'a' && curr <= 'z') ? Color::BLACK : Color::WHITE;
      position.setSquare((row << 3) + col, color, piece);
      col++;

    }
  }
  if (side == "w") {
    position.to_move = Color::WHITE;
  } else if (side == "b") {
    position.to_move = Color::BLACK;
  } else {
    fce_error("Couldn\'t parse side to move in fen", 1);
  }

  for (auto curr : castling) {
    if (curr == 'K') {
      position.castle_rights[Color::WHITE][Castle::KINGSIDE] = true;
    } else if (curr == 'k') {
      position.castle_rights[Color::BLACK][Castle::KINGSIDE] = true;
    } else if (curr == 'q') {
      position.castle_rights[Color::BLACK][Castle::QUEENSIDE] = true;
    } else if (curr == 'Q') {
      position.castle_rights[Color::WHITE][Castle::QUEENSIDE] = true;
    } else if (curr == '-') {
      position.castle_rights[Color::BLACK][Castle::QUEENSIDE] = false;
      position.castle_rights[Color::BLACK][Castle::KINGSIDE] = false;
      position.castle_rights[Color::WHITE][Castle::QUEENSIDE] = false;
      position.castle_rights[Color::WHITE][Castle::KINGSIDE] = false;
      break;
    } else {
      fce_error("Could\'t read fen castling", 1);
    }
  }

  if (en_passant[0] == '-') {
    position.en_passant = SQUARE_NONE;
  } else if (en_passant[0] >= 'a' && en_passant[0] <= 'h' &&
             en_passant[1] >= '1' && en_passant[1] <= '8') {
    position.en_passant =
        (SquareIndex)(en_passant[0] - 'a') + (en_passant[1] - '1') * 8;
  } else {
    fce_error("Couldn\'t read fen enpassant", 1);
  }
  position.plies_since_capture = stoi(move_since_capture);
  position.plies = stoi(move);
  return position;
}