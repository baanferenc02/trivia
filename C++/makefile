SRC_DIR := src
TEST_DIR := test
BUILD_DIR := out

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -I$(SRC_DIR) -Idoctest

APP_SOURCES := $(SRC_DIR)/GameRunner.cpp $(SRC_DIR)/Game.cpp
TEST_SOURCES := $(SRC_DIR)/Game.cpp $(TEST_DIR)/GameTests.cpp

APP_TARGET := $(BUILD_DIR)/trivia
TEST_TARGET := $(BUILD_DIR)/trivia_tests

.PHONY: all prod build run tests test runTest clean

all: prod

prod: build run

tests: test runTest

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

build: $(BUILD_DIR)
	$(CXX) $(APP_SOURCES) $(CXXFLAGS) -o $(APP_TARGET)

run: build
	./$(APP_TARGET)

test: $(BUILD_DIR)
	$(CXX) $(TEST_SOURCES) $(CXXFLAGS) -o $(TEST_TARGET)

runTest: test
	./$(TEST_TARGET)

clean:
	rm -rf $(BUILD_DIR)
