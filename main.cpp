#include "commandparser.h"
#include "robot.h"
#include "tabletop.h"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

int main() 
{
  std::string filePath{"input.txt"};
  std::ifstream file{filePath};

  if (!file.is_open()) 
  {
    std::cerr << "Error: Could not open file" << std::endl;
    return -1;
  }

  constexpr std::int32_t tabletopWidth  = 5;
  constexpr std::int32_t tabletopHeight = 5;

  robot::Robot robot{};
  constexpr tabletop::Tabletop tabletop{tabletopWidth, tabletopHeight};

  bool foundFirstValidCommand = false;
  for (std::string line; std::getline(file, line);) 
  {
    // Remove whitespaces from the command
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end()); 
    
    if (!foundFirstValidCommand) 
    {
        if(line[0] != 'P')
        {
            continue;
        }

        if(commandparser::handlePlaceCommand(line, robot, tabletop))
        {
            foundFirstValidCommand = true;
        }
    }
    else
    {
        if(line[0] == 'P')
        {
            commandparser::handlePlaceCommand(line, robot, tabletop);
            continue;
        }

        // Check if command is valid
        if(commandparser::commands.find(line) == commandparser::commands.end())
        {
            std::cerr << "Command " << line << " is not valid!" << std::endl;
            continue;
        }

        if(line == "MOVE")
        {
            robot.move(tabletop);
        }
        else if(line == "LEFT")
        {
            robot.rotateLeft();
        }
        else if(line == "RIGHT")
        {
            robot.rotateRight();
        }
        else if(line == "REPORT")
        {
            robot.report();
        }
        else 
        {
            std::cerr << "Command " << line << " not handled!" << std::endl;
        }
    }
  }

  if(!foundFirstValidCommand)
  {
    std::cerr << "Did not find a valid first command!" << std::endl;
    return -1;
  }

  return 0;
}