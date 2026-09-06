CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -pedantic
APP_SRCS = main.cpp robot.cpp
TEST_SRCS = robot.ut.cpp robot.cpp
PARSER_TEST_SRCS = commandparser.ut.cpp robot.cpp

APP_OBJS = $(APP_SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
PARSER_TEST_OBJS = $(PARSER_TEST_SRCS:.cpp=.o)

RobotApp: $(APP_OBJS)
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

RobotAppTest: $(TEST_OBJS)
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

CommandParserTest: $(PARSER_TEST_OBJS)
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all build-test run-test clean

all: RobotApp

build-tests: RobotAppTest CommandParserTest

run-tests: build-tests
	./RobotAppTest
	./CommandParserTest


clean:
	rm -f RobotApp RobotAppTest CommandParserTest $(APP_OBJS) $(TEST_OBJS) $(PARSER_TEST_OBJS)