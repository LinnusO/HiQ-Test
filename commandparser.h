#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#pragma once

#include "robot.h"

#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace commandparser
{
// Set for all valid commands, used for quick verification
inline const std::unordered_set<std::string> commands 
{ 
    "PLACE",
    "MOVE",
    "LEFT",
    "RIGHT",
    "REPORT" 
};

// Maps string to robot direction enum
inline const std::unordered_map<std::string, robot::Direction> directionMapping
{
    {"NORTH", robot::Direction::NORTH},
    {"EAST", robot::Direction::EAST},
    {"SOUTH", robot::Direction::SOUTH},
    {"WEST", robot::Direction::WEST}
};

inline bool parsePlaceCommand(std::string const& a_placeCommandString, robot::Position& r_position)
{
    std::stringstream ss{a_placeCommandString};
    std::vector<std::string> placeCommandVector;

    for(std::string word; getline(ss, word, ',');) 
    {
        placeCommandVector.push_back(word);
    }

    if(placeCommandVector.size() != 4)
    {
        std::cerr << "Command " << a_placeCommandString << " is not valid!" << std::endl;
        return false;
    }

    std::string const& command = placeCommandVector[0];
    if(command != "PLACE")
    {
        std::cerr << "Command " << command << " is not valid!" << std::endl;
        return false;
    }

    std::int32_t xPos{};
    try
    {
        xPos = std::stoi(placeCommandVector[1]);
    }
    catch(std::exception const& e)
    {
        std::cerr << "X position " << xPos << " is not valid!" << std::endl;
        return false;
    }

    r_position.xPos = xPos;

    std::int32_t yPos{};
    try
    {
        yPos = std::stoi(placeCommandVector[2]);
    }
    catch(std::exception const& e)
    {
        std::cerr << "Y position " << " is not valid!" << std::endl;
        return false;
    }

    r_position.yPos = yPos;

    // Check if direction is valid
    std::string const& direction = placeCommandVector[3];
    auto dir = directionMapping.find(direction);
    if(dir == directionMapping.end())
    {
        std::cerr << "Direction " << direction << "is invalid!" << std::endl;
        return false;
    }

    r_position.direction = dir->second;

    return true;
}

inline bool handlePlaceCommand(std::string const& a_command, robot::Robot& ar_robot, tabletop::Tabletop const& a_tabletop)
{
    robot::Position position;
    if(!parsePlaceCommand(a_command, position))
    {
        return false;
    }

    return ar_robot.place(position, a_tabletop);
}
} // namespace commandparser
#endif