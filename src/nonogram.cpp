#include "nonogram.hpp"

/**
 * Nonogram file description:
 *  First line: dimensions (rows, then collumns)
 *  Following lines: Rows from top to bottom followed by collums from left to right
 *  Separate numbers are delimited by any number of ws characters (except newline characters, which are used to delimit lines)
 *  Empty line symbolises a row/collumn of only crosses
 *  Initial ws characters are allowed (for formatting)
 *  Trailing ws characters are forbidden
 *  The file must ONLY CONTAIN NUMBERS between 1 and MAX_SIZE inclusive
 *  Everything has to abide by nonogram rules (for example is row count is 10, there can't be a collumn like "12" or "5 3 3")
 */

Nonogram::Nonogram(string ngf_name) {
    ifstream ngf(ngf_name);
    if (!ngf.is_open()) {
        throw "Could not open file";
    }

    string s; // temporary store for one line before conversion to istringstream

    getline(ngf, s);
    istringstream first_line(s);
    if (!(first_line >> this->row_cnt)) {
        throw "Invalid row count";
    }
    if (!(first_line >> this->col_cnt)) {
        throw "Invalid collumn count";
    }
    if (!first_line.eof()) {
        throw "Characters detected following dimensions";
    }
    cout << this->row_cnt << " " << this->col_cnt << endl;

    while (getline(ngf, s)) {
        istringstream line(s);
        int n;
        while (line >> n) {
            // ...
        }
    }

    ngf.close(); // HAS TO BE CLOSED ON EXCEPTION !!!
}
