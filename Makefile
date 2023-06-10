.PHONY: clean

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -Wpedantic -g

HEADERS = $(wildcard src/*.hpp)
SOURCES = $(wildcard src/*.cpp)

OUTPUT = main

all: $(OUTPUT)

$(OUTPUT): $(HEADERS) $(SOURCES)
	mkdir build
	$(CXX) $(CXXFLAGS) $^ -o build/$@

run: $(OUTPUT)
	build/$(OUTPUT)

clean:
	rm -rf build $(OUTPUT)
