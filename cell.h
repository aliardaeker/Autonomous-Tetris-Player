// Christos Savvopoulos <savvopoulos@gmail.com>
// Elias Sprengel <blockbattle@webagent.eu>

#ifndef __CELL_H
#define __CELL_H

#include <string>

/**
 * Represents one Cell in the playing field.
 * Has some basic methods already implemented.
 */
class Cell {
 public:
  // Enum of all the possible Cell types.
  enum CellState { INVALID = -1, EMPTY = 0, SHAPE = 1, BLOCK = 2, SOLID = 3 };

  Cell() : x_(-1), y_(-1), state_(INVALID) {}
  Cell(int x, int y, CellState type) : x_(x), y_(y), state_(type) {}

  void SetLocation(int x, int y) {
    x_ = x;
    y_ = y;
  }

  bool Equals(const Cell& cell) const {
    if (cell.x() != x_) {
      return false;
    }
    if (cell.y() != y_) {
      return false;
    }
    if (cell.state() != state_) {
      return false;
    }
    return true;
  }

  string AsString() const {
    switch (state_) {
      case CellState::INVALID:
        return "?";
      case CellState::EMPTY:
        return " ";
      case CellState::SHAPE:
        return "+";
      case CellState::BLOCK:
        return "#";
      case CellState::SOLID:
        return "-";
    }
    return "?";
  }

  bool IsShape() const { return state_ == SHAPE; }

  bool IsSolid() const { return state_ == SOLID; }

  bool IsBlock() const { return state_ == BLOCK; }

  bool IsEmpty() const { return state_ == EMPTY; }

  CellState state() const { return state_; }

  void set_state(int state) {
    state_ = (CellState)state;
  }

  int x() const { return x_; }

  int y() const { return y_; }

 private:
  int x_, y_;
  CellState state_;
};

#endif  // __CELL_H
