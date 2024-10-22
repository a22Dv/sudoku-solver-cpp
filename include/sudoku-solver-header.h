// https://github.com/a22Dv/sudoku-solver-cpp

// std libraries.
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

#ifndef SUDOKU_SOLVER_HEADER_H
#define SUDOKU_SOLVER_HEADER_H

// Class templates.
class Main {
public:
    std::string getSudokuBoard(std::string_view &validChars);
    bool getRTUpdateStatus();
    bool validateInputs(std::string &sudokuInput, std::string_view &validChars);
};
class Display {
public:
};
class Utils {
public:
    bool exitConfirmation();
    void clearConsole();
};

#endif