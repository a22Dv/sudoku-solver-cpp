// https://github.com/a22Dv/sudoku-solver-cpp

// std libraries.
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_set>
#include <vector>

#ifndef SUDOKU_SOLVER_HEADER_H
#define SUDOKU_SOLVER_HEADER_H
constexpr int boardSideLength = 9;
constexpr int validInputLength = 89;
constexpr int sqrtBoardSideLength = 3;

// Class templates.
class Display;
class Main {
public:
    std::string getSudokuBoard(std::string_view &validChars);
    bool getRTUpdateStatus();
    bool validateInputs(std::string &sudokuInput, std::string_view &validChars);
    void initialize(
        std::string_view &validChars,
        std::string &sudokuInput,
        std::vector<int> &grid, 
        std::map<int, std::unordered_set<int>> &rows,
        std::map<int, std::unordered_set<int>> &columns, 
        std::map<int, std::unordered_set<int>> &subGrids
    );
    void solveSudoku(
        Display &d,
        bool willDisplayRealTime, 
        std::vector<int> &grid, 
        std::map<int, std::unordered_set<int>> &rows,
        std::map<int, std::unordered_set<int>> &columns, 
        std::map<int, std::unordered_set<int>> &subGrids
    );
    bool DFS(
        Display &d,
        bool willDisplayRealTime,
        int currentIndex, 
        std::vector<int> &grid, 
        std::map<int, std::unordered_set<int>> &rows,
        std::map<int, std::unordered_set<int>> &columns, 
        std::map<int, std::unordered_set<int>> &subGrids
    );    
    int getNextEmptyCell(std::vector<int> &grid, int currentIndex);
};
class Display {
public:
    void displayBoard(std::vector<int> &grid);
    void clearConsole();
};
class Utils {
public:
    bool exitConfirmation();
};

#endif