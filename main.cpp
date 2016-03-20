// Christos Savvopoulos <savvopoulos@gmail.com>
// Elias Sprengel <blockbattle@webagent.eu>

#include <cstdlib>

#include "bot-starter.h"
#include "bot-parser.h"

using namespace std;

/**
 * Main File, starts the whole process.
**/

int main() {
  // initialize random seed for our results to be reproducable
  srand(17);
  BotStarter botStarter;
  BotParser parser(botStarter);
  parser.Run();
}
