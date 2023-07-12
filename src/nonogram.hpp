#ifndef _NONOGRAM_HPP
#define _NONOGRAM_HPP

#include "common.hpp"

enum class File_states {
    INIT,
    ROW_COUNT,
    DIMENSIONS_SPACE,
    COLLUMN_COUNT,
    NEW_LINE,
    STARTED_LINE,
    NUMBER,
    NUMBER_SPACE
};

enum class Tiles {
    EMPTY,
    FILLED,
    CROSSED
};

class Nonogram {
    int row_count, collumn_count;
    vector<vector<int>> rows, collumns;
    vector<vector<Tiles>> grid;
    
    void Parse_character(char current, File_states &state);
public:
    Nonogram(string file_name);

    void Draw();    
};

#endif // _NONOGRAM_HPP
