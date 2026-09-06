#include "acutest.h"

#include "commandparser.h"
#include "robot.h"
#include "tabletop.h"

constexpr tabletop::Tabletop const c_tabletop{5, 5};

void checkPosDir(robot::Robot const& a_robot, std::int32_t const& a_xPos, std::int32_t const& a_yPos, robot::Direction const& a_direction)
{
    TEST_CHECK(a_robot.getPosition().xPos == a_xPos);
    TEST_CHECK(a_robot.getPosition().yPos == a_yPos);
    TEST_CHECK(a_robot.getPosition().direction == a_direction);
}

void testParsePlaceCommandValid(void)
{
    robot::Position pos;

    TEST_CHECK(commandparser::parsePlaceCommand("PLACE,0,0,NORTH", pos));
    TEST_CHECK(pos.xPos == 0);
    TEST_CHECK(pos.yPos == 0);
    TEST_CHECK(pos.direction == robot::Direction::NORTH);

    TEST_CHECK(commandparser::parsePlaceCommand("PLACE,4,4,SOUTH", pos));
    TEST_CHECK(pos.xPos == 4);
    TEST_CHECK(pos.yPos == 4);
    TEST_CHECK(pos.direction == robot::Direction::SOUTH);

    TEST_CHECK(commandparser::parsePlaceCommand("PLACE,2,3,WEST", pos));
    TEST_CHECK(pos.xPos == 2);
    TEST_CHECK(pos.yPos == 3);
    TEST_CHECK(pos.direction == robot::Direction::WEST);

    TEST_CHECK(commandparser::parsePlaceCommand("PLACE,1,2,EAST", pos));
    TEST_CHECK(pos.xPos == 1);
    TEST_CHECK(pos.yPos == 2);
    TEST_CHECK(pos.direction == robot::Direction::EAST);
}

void testParsePlaceCommandTooFewTokens(void)
{
    robot::Position pos;

    TEST_CHECK(!commandparser::parsePlaceCommand("PLACE", pos));
    TEST_CHECK(!commandparser::parsePlaceCommand("PLACE,0", pos));
    TEST_CHECK(!commandparser::parsePlaceCommand("PLACE,0,0", pos));
}

void testParsePlaceCommandTooManyTokens(void)
{
    robot::Position pos;

    TEST_CHECK(!commandparser::parsePlaceCommand("PLACE,0,0,NORTH,WEST", pos));
}

void testParsePlaceCommandEmptyString(void)
{
    robot::Position pos;

    TEST_CHECK(!commandparser::parsePlaceCommand("", pos));
}

void testParsePlaceCommandNotPlaceCommand(void)
{
    robot::Position pos;

    TEST_CHECK(!commandparser::parsePlaceCommand("MOVE,0,0,NORTH", pos));
    TEST_CHECK(!commandparser::parsePlaceCommand("PLAY,0,0,NORTH", pos));
}

void testParsePlaceCommandInvalidCoordinates(void)
{
    robot::Position pos;

    TEST_CHECK(!commandparser::parsePlaceCommand("PLACE,A,0,NORTH", pos));
    TEST_CHECK(!commandparser::parsePlaceCommand("PLACE,0,B,NORTH", pos));
}

void testParsePlaceCommandInvalidDirection(void)
{
    robot::Position pos;

    TEST_CHECK(!commandparser::parsePlaceCommand("PLACE,0,0,UP", pos));
    TEST_CHECK(!commandparser::parsePlaceCommand("PLACE,0,0,North", pos));
    TEST_CHECK(!commandparser::parsePlaceCommand("PLACE,0,0,NORTHEAST", pos));
}

void testParsePlaceCommandNegativeCoordinates(void)
{
    robot::Position pos;

    TEST_CHECK(commandparser::parsePlaceCommand("PLACE,-1,0,NORTH", pos));
    TEST_CHECK(pos.xPos == -1);
    TEST_CHECK(pos.yPos == 0);

    TEST_CHECK(commandparser::parsePlaceCommand("PLACE,0,-1,NORTH", pos));
    TEST_CHECK(pos.xPos == 0);
    TEST_CHECK(pos.yPos == -1);
}

void testHandlePlaceCommandValidPlacement(void)
{
    robot::Robot robot{};

    TEST_CHECK(commandparser::handlePlaceCommand("PLACE,2,2,NORTH", robot, c_tabletop));
    checkPosDir(robot, 2, 2, robot::Direction::NORTH);

    TEST_CHECK(commandparser::handlePlaceCommand("PLACE,4,0,EAST", robot, c_tabletop));
    checkPosDir(robot, 4, 0, robot::Direction::EAST);
}

void testHandlePlaceCommandOutOfBounds(void)
{
    robot::Robot robot{};

    TEST_CHECK(commandparser::handlePlaceCommand("PLACE,2,2,NORTH", robot, c_tabletop));

    TEST_CHECK(!commandparser::handlePlaceCommand("PLACE,9,9,NORTH", robot, c_tabletop));
    checkPosDir(robot, 2, 2, robot::Direction::NORTH);

    TEST_CHECK(!commandparser::handlePlaceCommand("PLACE,5,0,EAST", robot, c_tabletop));
    checkPosDir(robot, 2, 2, robot::Direction::NORTH);

    TEST_CHECK(!commandparser::handlePlaceCommand("PLACE,0,5,SOUTH", robot, c_tabletop));
    checkPosDir(robot, 2, 2, robot::Direction::NORTH);

    TEST_CHECK(!commandparser::handlePlaceCommand("PLACE,-1,0,WEST", robot, c_tabletop));
    checkPosDir(robot, 2, 2, robot::Direction::NORTH);

    TEST_CHECK(!commandparser::handlePlaceCommand("PLACE,-5,-5,NORTH", robot, c_tabletop));
    checkPosDir(robot, 2, 2, robot::Direction::NORTH);
}

void testHandlePlaceCommandRejectsMalformedInput(void)
{
    robot::Robot robot{};

    TEST_CHECK(commandparser::handlePlaceCommand("PLACE,2,2,NORTH", robot, c_tabletop));

    TEST_CHECK(!commandparser::handlePlaceCommand("PLACE", robot, c_tabletop));
    TEST_CHECK(!commandparser::handlePlaceCommand("PLACE,0", robot, c_tabletop));
    TEST_CHECK(!commandparser::handlePlaceCommand("MOVE", robot, c_tabletop));
    checkPosDir(robot, 2, 2, robot::Direction::NORTH);
}

TEST_LIST = {
    {"testParsePlaceCommandValid", testParsePlaceCommandValid},
    {"testParsePlaceCommandTooFewTokens", testParsePlaceCommandTooFewTokens},
    {"testParsePlaceCommandTooManyTokens", testParsePlaceCommandTooManyTokens},
    {"testParsePlaceCommandEmptyString", testParsePlaceCommandEmptyString},
    {"testParsePlaceCommandNotPlaceCommand", testParsePlaceCommandNotPlaceCommand},
    {"testParsePlaceCommandInvalidCoordinates", testParsePlaceCommandInvalidCoordinates},
    {"testParsePlaceCommandInvalidDirection", testParsePlaceCommandInvalidDirection},
    {"testParsePlaceCommandNegativeCoordinates", testParsePlaceCommandNegativeCoordinates},
    {"testHandlePlaceCommandValidPlacement", testHandlePlaceCommandValidPlacement},
    {"testHandlePlaceCommandOutOfBounds", testHandlePlaceCommandOutOfBounds},
    {"testHandlePlaceCommandRejectsMalformedInput", testHandlePlaceCommandRejectsMalformedInput},
    {NULL, NULL}
};