#include "robot.h"
#include "tabletop.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace 
{
std::unordered_set<std::string> commands 
{ 
    "PLACE",
    "MOVE",
    "LEFT",
    "RIGHT",
    "REPORT" 
};

std::unordered_map<std::string, robot::Direction> directionMapping
{
    {"NORTH", robot::Direction::NORTH},
    {"EAST", robot::Direction::EAST},
    {"SOUTH", robot::Direction::SOUTH},
    {"WEST", robot::Direction::WEST}
};

// Helper functions
bool parsePlaceCommand(std::string const& a_placeCommandString, robot::Position& r_placeCommand)
{
    std::stringstream ss{a_placeCommandString};
    std::vector<std::string> placeCommand;

    for(std::string word; getline(ss, word, ',');) 
    {
        placeCommand.push_back(word);
    }

    if(placeCommand[0] != "PLACE")
    {
        std::cerr << "Command is not valid!" << std::endl;
        return false;
    }

    std::int32_t xPos{};
    try
    {
        xPos = std::stoi(placeCommand[1]);
    }
    catch(std::invalid_argument const& e)
    {
        std::cerr << "X position is not valid!" << std::endl;
        return false;
    }

    r_placeCommand.xPos = xPos;

    std::int32_t yPos{};
    try
    {
        yPos = std::stoi(placeCommand[2]);
    }
    catch(std::invalid_argument const& e)
    {
        std::cerr << "Y position is not valid!" << std::endl;
        return false;
    }

    r_placeCommand.yPos = yPos;

    // Check if direction is valid
    auto it = placeCommand[3];
    if(directionMapping.find(it) == directionMapping.end())
    {
        std::cerr << "Direction " << it << "is invalid!" << std::endl;
        return false;
    }

    r_placeCommand.direction = directionMapping[it];

    return true;
}

void handlePlaceCommand(std::string const& a_command, robot::Robot& ar_robot, tabletop::Tabletop const& a_tabletop)
{
    robot::Position position;
    if(!parsePlaceCommand(a_command, position))
    {
        return;
    }

    ar_robot.place(position, a_tabletop);
}
} // namespace

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
  tabletop::Tabletop tabletop{tabletopWidth, tabletopHeight};

  bool foundFirstValidCommand = false;
  for (std::string line; std::getline(file, line);) 
  {
    if (!foundFirstValidCommand) 
    {
        if(line[0] != 'P')
        {
            continue;
        }

        handlePlaceCommand(line, robot, tabletop);
        foundFirstValidCommand = true;
    }
    else
    {
        if(line[0] == 'P')
        {
            handlePlaceCommand(line, robot, tabletop);
            continue;
        }

        // Check if command is valid
        if(commands.find(line) == commands.end())
        {
            std::cerr << "Command is not valid!" << std::endl;
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