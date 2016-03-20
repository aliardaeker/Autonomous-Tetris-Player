// Christos Savvopoulos <savvopoulos@gmail.com>
// Elias Sprengel <blockbattle@webagent.eu>

#ifndef __BOT_PARSER_H
#define __BOT_PARSER_H

#include <iostream>
#include <string>
#include <vector>

#include "move.h"
#include "bot-starter.h"

using namespace std;

/**
 * Main class that will keep reading output from the engine.
 * Will either update the bot state or get actions.
 */
class BotParser {
 public:
  BotParser(const BotStarter& bot) : bot_(bot) {}

  void Run() {
    BotState currentState;

    while (true) {
      string command;
      cin >> command;
      if (command == "settings") {
        string part1, part2;
        cin >> part1 >> part2;
        currentState.UpdateSettings(part1, part2);
      } else if (command == "update") {
        string part1, part2, part3;
        cin >> part1 >> part2 >> part3;
        currentState.UpdateState(part1, part2, part3);
      } else if (command == "action") {
        string output, moveJoin, part1;
        long long part2;
        cin >> part1 >> part2;

        vector<Move::MoveType> moves = bot_.GetMoves(currentState, part2);

        if (moves.size() > 0) {
          for (Move::MoveType move : moves) {
            output += moveJoin;
            output += Move::MoveToString(move);
            moveJoin = ",";
          }
        } else {
          output += "no_moves";
        }

        cout << output << endl;
      } else if (command.size() == 0) {
        // no more commands, exit.
        break;
      } else {
        cerr << "Unable to parse command: " << command << endl;
      }
    }
  }

 private:
  const BotStarter& bot_;
};

#endif  //__BOT_PARSER_H
