// Christos Savvopoulos <savvopoulos@gmail.com>
// Elias Sprengel <blockbattle@webagent.eu>

#ifndef __SHAPE_H
#define __SHAPE_H

#include <memory>
#include <vector>
#include <string>

#include "cell.h"
#include "field.h"

using namespace std;

/**
 * Represents the shapes that appear in the field.
 * Some basic methods have already been implemented, but
 * actual move actions, etc. should still be created.
 */
class Shape {
 public:
  // Enum for all possible Shape types.
  enum ShapeType { I, J, L, O, S, T, Z, NONE };

  Shape(ShapeType type, const Field& field, int x, int y)
      : type_(type), x_(x), y_(y), field_(field) {
    SetShape();
    SetBlockLocations();
  }

  int x() const { return x_; }

  int y() const { return y_; }

  static ShapeType StringToShapeType(string name) {
    if (name == "I") {
      return ShapeType::I;
    }
    if (name == "J") {
      return ShapeType::J;
    }
    if (name == "L") {
      return ShapeType::L;
    }
    if (name == "O") {
      return ShapeType::O;
    }
    if (name == "S") {
      return ShapeType::S;
    }
    if (name == "T") {
      return ShapeType::T;
    }
    if (name == "Z") {
      return ShapeType::Z;
    }
    // Could not find a matching shape_, return NONE.
    return ShapeType::NONE;
  }

  void SetLocation(int x, int y) {
    x_ = x;
    y_ = y;
    SetBlockLocations();
  }

  const vector<Cell*> GetBlocks() const { return blocks_; }

  pair<int, int> Location() const { return make_pair(x_, y_); }

  ShapeType type() const { return type_; }

  bool IsValid() const {
    for (const Cell* cell : blocks_) {
      if (cell == nullptr) {
        return false;
      }
      const Cell& c = *cell;
      if (field_.HasCollision(c)) {
        return false;
      }
    }
    return true;
  }

  // ACTIONS (no checks for errors are performed in the actions!)

  /**
   * Rotates the shape counter-clockwise
   */
  void TurnLeft() {
    // cout << "Turning left" << endl;
    // cout << AsString() << endl;
    vector<vector<Cell>> temp = TransposeShape();
    for (size_t x = 0; x < size_; ++x) {
      for (size_t y = 0; y < size_; ++y) {
        shape_[x][y] = temp[size_ - x - 1][y];
      }
    }
    SetBlockLocations();
    RecomputeBlocks();
    // cout << AsString() << endl;
  }

  /**
   * Rotates the shape clockwise
   */
  void TurnRight() {
    vector<vector<Cell>> temp = TransposeShape();
    for (size_t x = 0; x < size_; ++x) {
      for (size_t y = 0; y < size_; ++y) {
        shape_[x][y] = temp[x][size_ - y - 1];
      }
    }
    SetBlockLocations();
    RecomputeBlocks();
  }

  void OneDown() {
    y_++;
    SetBlockLocations();
  }

  void OneRight() {
    x_++;
    SetBlockLocations();
  }

  void OneLeft() {
    x_--;
    SetBlockLocations();
  }

  size_t size() const { return size_; }

  const vector<vector<Cell>>& shape() const { return shape_; }

  bool Equals(const Shape& shape) const {
    if (shape.type() != type_) {
      return false;
    }
    if (shape.size() != size_) {
      return false;
    }
    if (shape.x() != x_) {
      return false;
    }
    if (shape.y() != y_) {
      return false;
    }
    const vector<vector<Cell>>& layout = shape.shape();
    for (size_t x = 0; x < size_; ++x) {
      for (size_t y = 0; y < size_; ++y) {
        if (!layout[x][y].Equals(shape_[x][y])) {
          return false;
        }
      }
    }
    return true;
  }

  string AsString() const {
    string output =
        "Shape at (x,y) " + to_string(x_) + "," + to_string(y_) + ":\n";
    for (size_t x = 0; x < shape_.size(); ++x) {
      for (size_t y = 0; y < shape_[x].size(); ++y) {
        output = output + shape_[x][y].AsString();
      }
      output = output + "\n";
    }
    output = output + "Blocks: ";
    for (size_t i = 0; i < blocks_.size(); ++i) {
      output = output + "(" + to_string(blocks_[i]->x()) + "," +
               to_string(blocks_[i]->y()) + "),";
    }
    return output;
  }

  unique_ptr<Shape> Copy() const {
    // cout << "Copying this shape: " << endl << AsString() << endl;
    unique_ptr<Shape> copy(new Shape(type_, field_, x_, y_));
    // We need to set the shape here manually because the shape could be
    // rotated.
    copy->size_ = size_;
    copy->shape_ = vector<vector<Cell>>(shape_.size(),
                                        vector<Cell>(shape_[0].size(), Cell()));
    for (size_t x = 0; x < shape_.size(); ++x) {
      for (size_t y = 0; y < shape_[x].size(); ++y) {
        copy->shape_[x][y].set_state(shape_[x][y].state());
        copy->shape_[x][y].SetLocation(shape_[x][y].x(), shape_[x][y].y());
      }
    }

    // Copy over the block references.
    copy->blocks_.clear();
    for (size_t i = 0; i < blocks_.size(); ++i) {
      size_t xFound, yFound;
      for (size_t x = 0; x < shape_.size(); ++x) {
        for (size_t y = 0; y < shape_[x].size(); ++y) {
          // cout << (*blocks_.at(i)).AsString() << shape_[x][y].AsString() <<
          // endl;
          if ((*blocks_.at(i)).Equals(shape_[x][y])) {
            xFound = x;
            yFound = y;
            // cout << "Found break" << endl;
            break;
          }
        }
      }
      copy->blocks_.push_back(&copy->shape_[xFound][yFound]);
    }
    // cout << "Copied to this shape: " << endl << copy->AsString() << endl;
    return copy;
  }

 private:
  /**
   * Used for rotations
   */
  vector<vector<Cell>> TransposeShape() {
    vector<vector<Cell>> temp(size_, vector<Cell>());
    for (size_t x = 0; x < size_; ++x) {
      for (size_t y = 0; y < size_; ++y) {
        temp[x].push_back(
            Cell(shape_[y][x].x(), shape_[y][x].y(), shape_[y][x].state()));
      }
    }
    return temp;
  }

  /**
   * Uses the shape's current orientation and position to
   * set the actual location of the block-type cells on the field
   */
  void SetBlockLocations() {
    for (size_t x = 0; x < size_; ++x) {
      for (size_t y = 0; y < size_; ++y) {
        if (shape_[x][y].IsShape()) {
          shape_[x][y].SetLocation(x_ + x, y_ + y);
        }
      }
    }
  }

  /**
   * Reconstructs the block array after it got broken by a rotation.
   */
  void RecomputeBlocks() {
    int counter = 0;
    for (size_t x = 0; x < size_; ++x) {
      for (size_t y = 0; y < size_; ++y) {
        if (shape_[x][y].IsShape()) {
          blocks_[counter] = &shape_[x][y];
          counter++;
        }
      }
    }
  }

  /**
   * Set shape_ in square box.
   * Creates new Cells that can be checked against the actual
     * playing field.
     * */
  void SetShape() {
    blocks_ = vector<Cell*>();
    switch (type_) {
      case ShapeType::I:
        size_ = 4;
        InitializeShape();
        blocks_.push_back(&shape_[1][0]);
        blocks_.push_back(&shape_[1][1]);
        blocks_.push_back(&shape_[1][2]);
        blocks_.push_back(&shape_[1][3]);
        break;
      case ShapeType::J:
        size_ = 3;
        InitializeShape();
        blocks_.push_back(&shape_[0][0]);
        blocks_.push_back(&shape_[1][0]);
        blocks_.push_back(&shape_[1][1]);
        blocks_.push_back(&shape_[1][2]);
        break;
      case ShapeType::L:
        size_ = 3;
        InitializeShape();
        blocks_.push_back(&shape_[0][2]);
        blocks_.push_back(&shape_[1][0]);
        blocks_.push_back(&shape_[1][1]);
        blocks_.push_back(&shape_[1][2]);
        break;
      case ShapeType::O:
        size_ = 2;
        InitializeShape();
        blocks_.push_back(&shape_[0][0]);
        blocks_.push_back(&shape_[0][1]);
        blocks_.push_back(&shape_[1][0]);
        blocks_.push_back(&shape_[1][1]);
        break;
      case ShapeType::S:
        size_ = 3;
        InitializeShape();
        blocks_.push_back(&shape_[0][1]);
        blocks_.push_back(&shape_[0][2]);
        blocks_.push_back(&shape_[1][0]);
        blocks_.push_back(&shape_[1][1]);
        break;
      case ShapeType::T:
        size_ = 3;
        InitializeShape();
        blocks_.push_back(&shape_[0][1]);
        blocks_.push_back(&shape_[1][0]);
        blocks_.push_back(&shape_[1][1]);
        blocks_.push_back(&shape_[1][2]);
        break;
      case ShapeType::Z:
        size_ = 3;
        InitializeShape();
        blocks_.push_back(&shape_[0][0]);
        blocks_.push_back(&shape_[0][1]);
        blocks_.push_back(&shape_[1][1]);
        blocks_.push_back(&shape_[1][2]);
        break;
      default:
        size_ = 0;
        InitializeShape();
    }
    // set type to SHAPE
    for (size_t i = 0; i < blocks_.size(); ++i) {
      blocks_[i]->set_state(Cell::CellState::SHAPE);
    }
  }

  /**
   * Creates the matrix for the shape_
   * @return
  */
  void InitializeShape() {
    shape_ = vector<vector<Cell>>(size_, vector<Cell>(size_, Cell()));
  }

  ShapeType type_;
  vector<vector<Cell>> shape_;
  vector<Cell*> blocks_;
  size_t size_;
  int x_;
  int y_;
  const Field& field_;
};

#endif  // __SHAPE_H
