// Christos Savvopoulos <savvopoulos@gmail.com>
// Elias Sprengel <blockbattle@webagent.eu>

#ifndef __UTIL_H
#define __UTIL_H

#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<string> Split(const string& s, char delim) {
  vector<string> elems;
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

#endif  //__UTIL_H
