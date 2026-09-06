#include "acutest.h"

#include "robot.h"
#include "tabletop.h"

constexpr tabletop::Tabletop const c_tabletop{5, 5};

void checkPosDir(robot::Robot const& a_robot, std::int32_t const& a_xPos, std::int32_t const& a_yPos, robot::Direction const& a_direction)
{
    TEST_CHECK(a_robot.getPosition().xPos == a_xPos);
    TEST_CHECK(a_robot.getPosition().yPos == a_yPos);
    TEST_CHECK(a_robot.getPosition().direction == a_direction);
}

void testRobotPlace(void)
{
    robot::Robot robot{};

    TEST_CHECK(robot.place({0, 0, robot::Direction::NORTH}, c_tabletop));
    checkPosDir(robot, 0, 0, robot::Direction::NORTH);

    TEST_CHECK(robot.place({4, 4, robot::Direction::EAST}, c_tabletop));
    checkPosDir(robot, 4, 4, robot::Direction::EAST);

    TEST_CHECK(!robot.place({-1, 0, robot::Direction::NORTH}, c_tabletop));
    checkPosDir(robot, 4, 4, robot::Direction::EAST);
    
    TEST_CHECK(!robot.place({0, -1, robot::Direction::NORTH}, c_tabletop));
    checkPosDir(robot, 4, 4, robot::Direction::EAST);

    TEST_CHECK(!robot.place({5, 0, robot::Direction::NORTH}, c_tabletop));
    checkPosDir(robot, 4, 4, robot::Direction::EAST);

    TEST_CHECK(!robot.place({0, 5, robot::Direction::NORTH}, c_tabletop));
    checkPosDir(robot, 4, 4, robot::Direction::EAST);

    TEST_CHECK(!robot.place({-5, 5, robot::Direction::NORTH}, c_tabletop));
    checkPosDir(robot, 4, 4, robot::Direction::EAST);
}

void testRobotRotateRight(void)
{
    robot::Robot robot{};

    robot.place({2, 2, robot::Direction::NORTH}, c_tabletop);
    robot.rotateRight();
    checkPosDir(robot, 2, 2, robot::Direction::EAST);
    robot.rotateRight();
    checkPosDir(robot, 2, 2, robot::Direction::SOUTH);
    robot.rotateRight();
    checkPosDir(robot, 2, 2, robot::Direction::WEST);
    robot.rotateRight();
    checkPosDir(robot, 2, 2, robot::Direction::NORTH);
}

void testRobotRotateLeft(void)
{
    robot::Robot robot{};

    robot.place({2, 2, robot::Direction::NORTH}, c_tabletop);
    robot.rotateLeft();
    checkPosDir(robot, 2, 2, robot::Direction::WEST);
    robot.rotateLeft();
    checkPosDir(robot, 2, 2, robot::Direction::SOUTH);
    robot.rotateLeft();
    checkPosDir(robot, 2, 2, robot::Direction::EAST);
    robot.rotateLeft();
    checkPosDir(robot, 2, 2, robot::Direction::NORTH);
}

void testRobotMoveNorth(void)
{
    robot::Robot robot{};
    robot.place({2, 2, robot::Direction::NORTH}, c_tabletop);

    TEST_CHECK(robot.move(c_tabletop));
    checkPosDir(robot, 2, 3, robot::Direction::NORTH);

    TEST_CHECK(robot.move(c_tabletop));
    checkPosDir(robot, 2, 4, robot::Direction::NORTH);

    TEST_CHECK(!robot.move(c_tabletop));
    checkPosDir(robot, 2, 4, robot::Direction::NORTH);
}

void testRobotMoveEast(void)
{
    robot::Robot robot{};
    robot.place({2, 2, robot::Direction::EAST}, c_tabletop);

    TEST_CHECK(robot.move(c_tabletop));
    checkPosDir(robot, 3, 2, robot::Direction::EAST);

    TEST_CHECK(robot.move(c_tabletop));
    checkPosDir(robot, 4, 2, robot::Direction::EAST);

    TEST_CHECK(!robot.move(c_tabletop));
    checkPosDir(robot, 4, 2, robot::Direction::EAST);
}

void testRobotMoveSouth(void)
{
    robot::Robot robot{};
    robot.place({2, 2, robot::Direction::SOUTH}, c_tabletop);

    TEST_CHECK(robot.move(c_tabletop));
    checkPosDir(robot, 2, 1, robot::Direction::SOUTH);

    TEST_CHECK(robot.move(c_tabletop));
    checkPosDir(robot, 2, 0, robot::Direction::SOUTH);

    TEST_CHECK(!robot.move(c_tabletop));
    checkPosDir(robot, 2, 0, robot::Direction::SOUTH);
}

void testRobotMoveWest(void)
{
    robot::Robot robot{};
    robot.place({2, 2, robot::Direction::WEST}, c_tabletop);

    TEST_CHECK(robot.move(c_tabletop));
    checkPosDir(robot, 1, 2, robot::Direction::WEST);

    TEST_CHECK(robot.move(c_tabletop));
    checkPosDir(robot, 0, 2, robot::Direction::WEST);

    TEST_CHECK(!robot.move(c_tabletop));
    checkPosDir(robot, 0, 2, robot::Direction::WEST);
}

void testRotationAffectsMovement(void)
{
    robot::Robot robot{};

    robot.place({2, 2, robot::Direction::NORTH}, c_tabletop);
    robot.rotateRight();
    TEST_CHECK(robot.move(c_tabletop));
    checkPosDir(robot, 3, 2, robot::Direction::EAST);

    robot.rotateRight();
    TEST_CHECK(robot.move(c_tabletop));
    checkPosDir(robot, 3, 1, robot::Direction::SOUTH);

    robot.rotateRight();
    TEST_CHECK(robot.move(c_tabletop));
    checkPosDir(robot, 2, 1, robot::Direction::WEST);
}

void testToString(void)
{
    TEST_CHECK(robot::toString(robot::Direction::NORTH) == "NORTH");
    TEST_CHECK(robot::toString(robot::Direction::EAST) == "EAST");
    TEST_CHECK(robot::toString(robot::Direction::SOUTH) == "SOUTH");
    TEST_CHECK(robot::toString(robot::Direction::WEST) == "WEST");
}

TEST_LIST = {
    {"testRobotPlace", testRobotPlace},
    {"testRobotRotateRight", testRobotRotateRight},
    {"testRobotRotateLeft", testRobotRotateLeft},
    {"testRobotMoveNorth", testRobotMoveNorth},
    {"testRobotMoveEast", testRobotMoveEast},
    {"testRobotMoveSouth", testRobotMoveSouth},
    {"testRobotMoveWest", testRobotMoveWest},
    {"testRotationAffectsMovement", testRotationAffectsMovement},
    {"testToString", testToString},
    {NULL, NULL}
};