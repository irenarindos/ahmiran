#ifndef GAMEDATA__H
#define GAMEDATA__H
#include <string>
#include <sstream>
#include <map>
using std::string;
#include "parseXML.h"

class Gamedata {
public:
  static Gamedata& getInstance();

  void displayData() const;
  bool getXmlBool(const string&) const;
  const string& getXmlStr(const string&) const;
  
  float getXmlFloat(const string&) const;
  int getXmlInt(const string&) const;

  int getFrames() const { return frames; }
  void incrFrames() { frames++; }
  void incrFrames(int num) { frames += num; }
  int getScore() const { return score; }
  void incrScore() { score++; }
  void decrScore() { score--; }
  void incrScore(int num) { score += num; }
private:
  ParseXML parser;
  const map<string, string> gameData;
  int frames;
  int score;

  Gamedata(const string& fn = "xmlSpec/rpggame.xml");
  Gamedata(const Gamedata&);
  Gamedata& operator=(const Gamedata&);
};
#endif
