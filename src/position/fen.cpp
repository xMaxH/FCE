#include "fen.hpp"
#include "position.hpp"
#include "util.hpp"
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

  Position position;
  int row = 0;
  int col = 0;

  for (int i = 0; i < RANKS; i++) {
    for (int j = 0; j < FILES; j++) {
      position.set_square(Position::square_to_index(i, j), Color::NO_COLOR,
                          Piece::NO_PIECE);
    }
  }
  for (char c : board) {
    if (c == '/') {
      row++;
      col = 0;
      continue;
    }
    if (c >= '0' && c <= '9') {
      int n = c - '1';
      col += n;
      continue;
    } else {
      Piece piece;
      if (c == 'r' || c == 'R') {
        piece = ROOK;
      } else if (c == 'b' || c == 'B') {
        piece = BISHOP;
      } else if (c == 'k' || c == 'K') {
        piece = KING;
      } else if (c == 'n' || c == 'N') {
        piece = KNIGHT;
      } else if (c == 'Q' || c == 'q') {
        piece = QUEEN;
      } else if (c == 'p' || c == 'P') {
        piece = PAWN;
      } else {
        fce_error("Could\'t read fen position", 1);
      }
      Color color = (c >= 'A' && c <= 'Z') ? Color::BLACK : Color::WHITE;
      position.set_square(Position::square_to_index(row, col), color, piece);
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

  for (auto c : castling) {
    if (c == 'K') {
      position.castle_rights[Color::WHITE][Castle::KINGSIDE] = true;
    } else if (c == 'k') {
      position.castle_rights[Color::BLACK][Castle::KINGSIDE] = true;
    } else if (c == 'q') {
      position.castle_rights[Color::BLACK][Castle::QUEENSIDE] = true;
    } else if (c == 'Q') {
      position.castle_rights[Color::WHITE][Castle::QUEENSIDE] = true;
    } else if (c == '-') {
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
    position.en_passant = no_square_index;
  } else if (en_passant[0] >= 'a' && en_passant[0] <= 'h' &&
             en_passant[1] >= '1' && en_passant[1] <= '8') {
    position.en_passant = (en_passant[0] - 'a') + (en_passant[1] - '1') * 8;
  } else {
    fce_error("Couldn\'t read fen enpassant", 1);
  }
  position.plies_since_capture = stoi(move_since_capture);
  position.plies = stoi(move);
  return position;
}