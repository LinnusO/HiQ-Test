#include "robot.h"
#include "tabletop.h"

#include <iostream>

namespace robot
{
Robot::Robot() : m_position{}
{}

bool Robot::place(Position const& a_position, tabletop::Tabletop const& a_tabletop)
{
    // Verify that the x position is valid
    if(a_position.xPos < 0 || a_position.xPos > a_tabletop.width - 1)
    {
        return false;
    }

    // Verify that the y position is valid
    if(a_position.yPos < 0 || a_position.yPos > a_tabletop.height - 1)
    {
        return false;
    }

    // Verify that direction is valid
    if(a_position.direction >= Direction::MAX_NUM)
    {
        return false;
    }

    m_position = a_position;
    return true;
}

void Robot::rotateLeft()
{
    int32_t direction = static_cast<int32_t>(m_position.direction);

    direction = direction - 1;
    if (direction < 0)
    {
        direction = static_cast<int32_t>(Direction::MAX_NUM) - 1;
    }

    m_position.direction = static_cast<Direction>(direction);
}

void Robot::rotateRight()
{
    int32_t direction = static_cast<int32_t>(m_position.direction);

    direction = direction + 1;
    if (direction == static_cast<int32_t>(Direction::MAX_NUM))
    {
        direction = 0;
    }

    m_position.direction = static_cast<Direction>(direction);
}

bool Robot::move(tabletop::Tabletop const& a_tabletop)
{
    switch (m_position.direction)
    {
        case Direction::NORTH:
        {
            auto newPos = m_position.yPos + 1;
            if(newPos > a_tabletop.height - 1)
            {
                return false;
            }

            m_position.yPos = newPos;
        }
        break;
        case Direction::EAST:
        {
            auto newPos = m_position.xPos + 1;
            if(newPos > a_tabletop.width - 1)
            {
                return false;
            }

            m_position.xPos = newPos;
        }
        break;
        case Direction::SOUTH:
        {
            auto newPos = m_position.yPos - 1;
            if(newPos < 0)
            {
                return false;
            }

            m_position.yPos = newPos;
        }
        break;
        case Direction::WEST:
        {
            auto newPos = m_position.xPos - 1;
            if(newPos < 0)
            {
                return false;
            }

            m_position.xPos = newPos;
        }
        break;
        default:
        {
            // Do nothing
            std::cerr << "Direction not handled!" << std::endl;
            return false;
        }
        break;
    }
    return true;
}

void Robot::report()
{
    std::cout << m_position.xPos << "," << m_position.yPos << "," << toString(m_position.direction) << std::endl;
}
}