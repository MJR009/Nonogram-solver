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
 *  The file has to end with a newline character as is standard
 */

// Ideas:
// there are library functions for sums
// try using iterators
// prepare the grid better than with 2 cycles

void Nonogram::Parse_character(char current, File_states &state) {
    static int line_count = 0;

    static string number; // buffer for the string representation of a number to later be converted
    static decltype(this->rows)::value_type line; // buffer for one row or collumn of numbers

    switch (state) {
        case File_states::INIT:
            if ((isdigit(current)) && (current != '0')) {
                number.push_back(current);
                state = File_states::ROW_COUNT;
            } else if ((current == ' ') || (current == '\t')) {
                // same state
            } else {
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
                if (line_count < this->row_count) {
                    this->rows.push_back(line);
                } else {
                    this->collumns.push_back(line);
                }
                line.clear();
                line_count++;
                // same state
            } else {
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
                if (line_count < this->row_count) {
                    this->rows.push_back(line);
                } else {
                    this->collumns.push_back(line);
                }
                line.clear();
                line_count++;
                state = File_states::NEW_LINE;
            } else {
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
                throw "Invalid line number";
            }
            break;
    }
}

Nonogram::Nonogram(string file_name) {
    ifstream file(file_name);
    if (!file.is_open()) {
        throw "Could not open given file";
    }

    char current;
    File_states state = File_states::INIT;

    while (file >> noskipws >> current) {
        try {
            this->Parse_character(current, state);
        } catch (const char* exception) {
            file.close();
            throw;
        }
    }

    file.close();

    if ((this->row_count != static_cast<int>(this->rows.size())) ||
        (this->collumn_count != static_cast<int>(this->collumns.size()))) {
        throw "Incorrect amount of lines";
    }

    // VALIDITY CHECK
    // FILL GRID

    // DEBUG
    /*
    if (state != File_states::NEW_LINE) {
        throw "Unexpected EOF";
    }

    for (auto row : this->rows) {
        for (auto number : row) {
            cout << number << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (auto collumn : this->collumns) {
        for (auto number : collumn) {
            cout << number << " ";
        }
        cout << endl;
    }
    */
}
