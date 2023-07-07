#include "nonogram.hpp"

/**
 * Nonogram file description:
 *  First line: dimensions (rows, then collumns)
 *  Following lines: Rows from top to bottom followed by collums from left to right
 *  Separate numbers are delimited by any number of spaces or tabs
 *  Initial zeros in numbers are not allowed
 *  Newline characters are used to delimit rows and collumns
 *  Empty line symbolises empty row/collumn (only "crosses")
 *  Initial ws characters are allowed (for formatting)
 *  Trailing ws characters are forbidden
 *  Everything has to abide by nonogram rules (i.e. if row count is 10, there can't be a collumn like "12" or "5 3 2")
 */

// TODO:
// maybe make nonogram_parser class? - probably easier
// put the switch into functions
// line variable is theoretically not needed
// make the file closing on error better (too much of the same everywhere)

Nonogram::Nonogram(string file_name) {
    ifstream file(file_name);
    if (!file.is_open()) {
        throw "Could not open given file";
    }

    char current;
    string number; // buffer for the string representation of a number to later be converted
    decltype(this->lines)::value_type line; // buffer for one row or collumn of numbers
    File_states state = File_states::INIT;

    while (file >> noskipws >> current) {
        switch (state) {
            case File_states::INIT:
                if ((isdigit(current)) && (current != '0')) {
                    number.push_back(current);
                    state = File_states::ROW_COUNT;
                } else if ((current == ' ') || (current == '\t')) {
                    // same state
                } else {
                    file.close();
                    throw "Invalid row count";
                }
                break;

            case File_states::ROW_COUNT:
                if (isdigit(current)) {
                    number.push_back(current);
                    // same state
                } else if ((current == ' ') || (current == '\t')) {
                    this->row_count = stoi(number);
                    number.clear();
                    state = File_states::DIMENSIONS_SPACE;
                } else {
                    file.close();
                    throw "Invalid row count";
                }
                break;

            case File_states::DIMENSIONS_SPACE:
                if ((isdigit(current)) && (current != '0')) {
                    number.push_back(current);
                    state = File_states::COLLUMN_COUNT;
                } else if ((current == ' ') || (current == '\t')) {
                    // same state
                } else {
                    file.close();
                    throw "Invalid collumn count";
                }
                break;

            case File_states::COLLUMN_COUNT:
                if (isdigit(current)) {
                    number.push_back(current);
                    // same state
                } else if (current == '\n') {
                    this->collumn_count = stoi(number);
                    number.clear();
                    state = File_states::NEW_LINE;
                } else {
                    file.close();
                    throw "Invalid collumn count";
                }
                break;

            case File_states::NEW_LINE:
                if ((isdigit(current)) && (current != '0')) {
                    number.push_back(current);
                    state = File_states::NUMBER;
                } else if ((current == ' ') || (current == '\t')) {
                    state = File_states::STARTED_LINE;
                } else if (current == '\n') {
                    this->lines.push_back(line);
                    line.clear();
                    // same state
                } else {
                    file.close();
                    throw "Invalid line beginning";
                }
                break;

            case File_states::STARTED_LINE:
                if ((isdigit(current)) && (current != '0')) {
                    number.push_back(current);
                    state = File_states::NUMBER;
                } else if ((current == ' ') || (current == '\t')) {
                    // same state
                } else {
                    file.close();
                    throw "Invalid number";
                }
                break;

            case File_states::NUMBER:
                if (isdigit(current)) {
                    number.push_back(current);
                    // same state
                } else if ((current == ' ') || (current == '\t')) {
                    line.push_back(stoi(number));
                    number.clear();
                    state = File_states::NUMBER_SPACE;
                } else if (current == '\n') {
                    line.push_back(stoi(number));
                    number.clear();
                    this->lines.push_back(line);
                    line.clear();
                    state = File_states::NEW_LINE;
                } else {
                    file.close();
                    throw "Invalid number";
                }
                break;

            case File_states::NUMBER_SPACE:
                if ((isdigit(current)) && (current != '0')) {
                    number.push_back(current);
                    state = File_states::NUMBER;
                } else if ((current == ' ') || (current == '\t')) {
                    // same state
                } else {
                    file.close();
                    throw "Invalid line number";
                }
                break;
        }
    }

    file.close();

    if (state != File_states::NEW_LINE) {
        throw "Unexpected EOF, not enough lines";
    }

    // VALIDITY CHECK
}
