#include "common.hpp"

#include "nonogram.hpp"

int main() {
    try {
        Nonogram nonogram("first");
    } catch (const char* exc) {
        cerr << exc << endl;
        return 1;
    }
}
