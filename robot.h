#ifndef ROBOT_H
#define ROBOT_H
#pragma once

#include <cstdint>
#include <iostream>
#include <string>

#include "tabletop.h"

namespace robot
{
enum class Direction
{
    NORTH = 0,
    EAST,
    SOUTH,
    WEST,
    MAX_NUM
};

inline std::string toString(Direction a_direction)
{
    switch(a_direction)
    {
        case Direction::NORTH:
        {
            return "NORTH";
        }
        break;
        case Direction::EAST:
        {
            return "EAST";
        }
        break;
        case Direction::SOUTH:
        {
            return "SOUTH";
        }
        break;
        case Direction::WEST:
        {
            return "WEST";
        }
        break;
        default:
        {
            std::cerr << "direction not handled" << std::endl;
            return "";
        }
        break;
    }
}

struct Position
{
    int32_t xPos;
    int32_t yPos;
    Direction direction;
};

class Robot
{
public:
    
    bool place(Position const& a_position, tabletop::Tabletop const& a_tabletop);
    void rotateLeft();
    void rotateRight();
    bool move(tabletop::Tabletop const& a_tabletop);
    void report();
    inline Position getPosition() const { return m_position; }

private:
    Position m_position;
};
    
} // namespace robot
#endif