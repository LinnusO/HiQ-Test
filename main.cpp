#include "robot.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace {
enum class Commands 
{ 
    PLACE = 0,
    MOVE,
    LEFT,
    RIGHT,
    REPORT 
};

enum class Direction
{
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
};
}

int main() 
{
  std::string filePath{"input.txt"};
  std::ifstream file{filePath};

  if (!file.is_open()) 
  {
    std::cerr << "Error: Could not open file" << std::endl;
    return -1;
  }

  bool foundFirstValidPlace = false;
  for (std::string line; std::getline(file, line);) 
  {
    if (!foundFirstValidPlace) 
    {
        std::stringstream ss{line};

        // Get every word seperated by comma
        for(std::string word; getline(ss, word, ',');) 
        {
            results.push_back(str);
        }
      std::size_t start = line.find("PLACE,");
      std::size_t end = line.find(",", start);
      std::string str = line.substr(start + 5, end - (start + 3));
    }
  }

  return 0;
}