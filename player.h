// Christos Savvopoulos <savvopoulos@gmail.com>
// Elias Sprengel <blockbattle@webagent.eu>

#ifndef __PLAYER_H
#define __PLAYER_H

#include <memory>
#include <string>
#include <vector>

#include "field.h"

using namespace std;

/**
 * Represents one of the players.
 */
class Player {
 public:
  Player(const string& name) : name_(name) {}

  const Field& field() const { return *field_; }

  void set_field(unique_ptr<const Field> field) { field_ = std::move(field); }

  const string& name() const { return name_; }

  int points() const { return points_; }

  void set_points(int p) { points_ = p; }

  int combo() const { return combo_; }

  void set_combo(int c) { combo_ = c; }

 private:
  unique_ptr<const Field> field_;
  const string name_;
  int points_;
  int combo_;
};

#endif  //__PLAYER_H
