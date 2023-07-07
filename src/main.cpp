#include "common.hpp"

#include "nonogram.hpp"

int main() {
    try {
        Nonogram nonogram("first");
    } catch (const char* exception) {
        cerr << "ERROR: " << exception << endl;
        return 1;
    }
}
