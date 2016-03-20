// Christos Savvopoulos <savvopoulos@gmail.com>
// Elias Sprengel <blockbattle@webagent.eu>

#ifndef __MOVE_H
#define __MOVE_H

#include <string>

using namespace std;
/**
 * A collection of valid moves that the player can perform
 */
class Move {
 public:
  // DROP will automatically performed and was not included in the original
  // version.
  // LAST is only used to get the number of elements in this enum.
  enum MoveType { DOWN, LEFT, RIGHT, TURNLEFT, TURNRIGHT, DROP, LAST };

  static string MoveToString(MoveType mt) {
    switch (mt) {
      case DOWN:
        return "DOWN";
      case LEFT:
        return "LEFT";
      case RIGHT:
        return "RIGHT";
      case TURNLEFT:
        return "TURNLEFT";
      case TURNRIGHT:
        return "TURNRIGHT";
      case DROP:
        return "DROP";
      case LAST:
        return "LAST";
    }
    return "UNKNOWN";
  }
};

#endif  //__MOVE_H
