// Christos Savvopoulos <savvopoulos@gmail.com>
// Elias Sprengel <blockbattle@webagent.eu>

#ifndef __BOT_STATE_H
#define __BOT_STATE_H

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "util.h"
#include "player.h"
#include "shape.h"

using namespace std;

typedef pair<int, int> Point;

/**
 * In this class all the information about the game is stored.
 */
class BotState {
 public:
  BotState() { round_ = 0; }

  void UpdateSettings(string key, string value) {
    if (key == "timebank") {
      max_timebank_ = stoi(value);
      timebank_ = max_timebank_;
    } else if (key == "time_per_move") {
      time_per_move_ = stoi(value);
    } else if (key == "player_names") {
      vector<string> playerNames = Split(value, ',');
      for (string name : playerNames) {
        players_[name] = unique_ptr<Player>(new Player(name));
      }
    } else if (key == "your_bot") {
      own_name_ = value;
    } else if (key == "field_width") {
      field_width_ = stoi(value);
    } else if (key == "field_height") {
      field_height_ = stoi(value);
    } else {
      cerr << "Cannot parse settings with key: " << key << endl;
    }
  }

  void UpdateState(string player, string key, string value) {
    if (key == "round") {
      round_ = stoi(value);
    } else if (key == "this_piece_type") {
      current_shape_ = Shape::StringToShapeType(value);
    } else if (key == "next_piece_type") {
      next_shape_ = Shape::StringToShapeType(value);
    } else if (key == "row_points") {
      players_[player]->set_points(stoi(value));
    } else if (key == "combo") {
      players_[player]->set_combo(stoi(value));
    } else if (key == "field") {
      players_[player]->set_field(
          unique_ptr<Field>(new Field(field_width_, field_height_, value)));
    } else if (key == "this_piece_position") {
      vector<string> split_value = Split(value, ',');
      shape_location_ = make_pair(stoi(split_value[0]), stoi(split_value[1]));
    } else {
      cerr << "Cannot parse updates with key: " << key << endl;
    }
  }

  const Player& Opponent() const {
    for (auto const& playerEntry : players_) {
      if (playerEntry.first != players_.at(own_name_)->name()) {
        return *playerEntry.second;
      }
    }
    cerr << "Error: No Opponent found, returning yourself" << endl;
    return *players_.at(own_name_);
  }

  const Field& MyField() const { return players_.at(own_name_)->field(); }

  const Field& OpponentField() const { return Opponent().field(); }

  Shape::ShapeType CurrentShape() const { return current_shape_; }

  Shape::ShapeType NextShape() const { return next_shape_; }

  Point ShapeLocation() const { return shape_location_; }

  int Round() const { return round_; }

 private:
  int round_;
  int timebank_;
  map<string, unique_ptr<Player>> players_;
  string own_name_;
  Shape::ShapeType current_shape_;
  Shape::ShapeType next_shape_;
  Point shape_location_;

  int max_timebank_;
  int time_per_move_;
  int field_width_;
  int field_height_;
};

#endif  //__BOT_STATE_H
