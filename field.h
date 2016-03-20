// Christos Savvopoulos <savvopoulos@gmail.com>
// Elias Sprengel <blockbattle@webagent.eu>

#ifndef __FIELD_H
#define __FIELD_H

#include <cassert>
#include <cstdlib>
#include <memory>
#include <string>

#include "cell.h"

using namespace std;

/**
 * Represents the playing field for one player.
 * Has some basic methods already implemented.
 */
class Field {
 public:
  // Parses the input string to get a grid with Cell objects.
  Field(int width, int height, const string& fieldStr)
      : width_(width), height_(height), grid_(width * height) {
    int x = 0;
    int y = 0;
    const char* strPos = fieldStr.c_str();

    while (strPos < fieldStr.c_str() + fieldStr.size()) {
      // Read cell code.
      char* strNext = nullptr;
      int cellCode = strtol(strPos, &strNext, 10);
      assert(strPos != strNext);  // check that we read sth.
      strPos = strNext;
      strNext = nullptr;

      // Update this cell.
      grid_[y * width + x].SetLocation(x, y);
      grid_[y * width + x].set_state(cellCode);

      // Advance position, parse separator.
      x++;
      if (x == width_) {
        assert(*strPos == ';' || y == height_ - 1);
        x = 0;
        y++;
      } else {
        assert(*strPos == ',');
      }
      strPos++;
    }
  }

  bool IsOutOfBounds(const Cell& c) {
    return c.x() >= width_ || c.x() < 0 || c.y() >= height_ || c.y() < 0;
  }

  bool HasCollision(const Cell& block_cell) const {
    const Cell& field_cell = GetCell(block_cell.x(), block_cell.y());
    return (block_cell.IsShape() &&
            (field_cell.IsSolid() || field_cell.IsBlock()));
  }

  const Cell& GetCell(int x, int y) const { return grid_[y * width_ + x]; }

  int width() const { return width_; }

  int height() const { return height_; }

 private:
  int width_;
  int height_;
  vector<Cell> grid_;
};

#endif  // __FIELD_H
