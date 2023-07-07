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

class Nonogram {
    int row_count, collumn_count;
    vector<vector<int>> tmp;

public:
    Nonogram(string file_name);
private:
    
};

#endif // _NONOGRAM_HPP
