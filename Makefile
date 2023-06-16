.PHONY = clean

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -Wpedantic -g

SOURCE_DIR = src
BUILD_DIR = build
EXEC = main

CPP = $(wildcard $(SOURCE_DIR)/*.cpp)
HPP = $(wildcard $(SOURCE_DIR)/*.hpp)

all: $(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/$(EXEC): $(CPP) $(HPP)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CPP) -o $(BUILD_DIR)/$(EXEC)

run: $(BUILD_DIR)/$(EXEC)
	$(BUILD_DIR)/$(EXEC)

clean:
	rm -rf $(BUILD_DIR)
