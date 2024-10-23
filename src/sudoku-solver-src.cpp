// https://github.com/a22Dv/sudoku-solver-cpp
// Test input: 53..7....-6..195...-.98....6.-8...6...3-4..8.3..1-7...2...6-.6....28.-...419..5-....8..79

#include "sudoku-solver-header.h"

/// @brief Gets the string that represents a sudoku board through console.
/// @param validChars An `std::string_view` for valid input characters, only used to display specified formatting within the function.
/// @return `std::string` (User input string)
std::string Main::getSudokuBoard(std::string_view &validChars) {
    std::string input = "";
    std::cout << "Format: Separate grid into rows from top to bottom, left to right.\n"
    << "[Empty Grid(" 
    << validChars[9] << ") Row Separator(" 
    << validChars[10] << ")].\n\n";
    std::cout << "Input sudoku board: ";
    std::getline(std::cin, input);
    return input;
}

/// @brief Gets whether the user prefers to display real-time updates of the solving process to console.
/// @return - `true` (default behavior, when user input != 'N' or 'n')
///
/// - `false` (if user input == 'N' or 'n')
bool Main::getRTUpdateStatus() {
    std::string input = "";
    std::cout << "(Enabling real-time updates will slow down solving and adds roughly 5s-10s to time taken)\n";
    std::cout << "Will the solver display real-time updates? [Y/N] (default = Y): ";
    std::getline(std::cin, input);
    if (input == "N" || input == "n") {
        return false;
    } else {
        return true;
    }
}

/// @brief Checks if input string is valid when checked against another string of valid characters.
/// @param sudokuInput Input string that represents a sudoku board.
/// @param validChars String of valid characters that can represent a sudoku board.
/// @return - `true` (if valid)
///
/// - `false` (if invalid)
bool Main::validateInputs(std::string &sudokuInput, std::string_view &validChars) {
    if (sudokuInput.length() != validInputLength) {
        return false;
    }
    for (char c : sudokuInput) {
        if (validChars.find(c) == std::string_view::npos) {
            return false;
        }
    }
    return true;
}

/// @brief Initializes all passed `std::map` and `std::unordered_set` with input `std::string` against `std::string_view`.
/// @param validChars `std::string_view` that holds the valid characters that can represent a sudoku board.
/// @param sudokuInput `std::string` that has the string representation of a sudoku board.
/// @param grid `std::vector` that holds the number representation of the sudoku board with indices as cell numbers.
/// @param rows `std::map` that holds an `std::unordered_set` of numbers per row number in the sudoku board.
/// @param columns `std::map` that holds an `std::unordered_set` of numbers per column number in the sudoku board.
/// @param subgrids `std::map` that holds an `std::unordered_set` of numbers per subgrid number in the sudoku board.
void Main::initialize(
        std::string_view &validChars,
        std::string &sudokuInput,
        std::vector<int> &grid, 
        std::map<int, std::unordered_set<int>> &rows,
        std::map<int, std::unordered_set<int>> &columns, 
        std::map<int, std::unordered_set<int>> &subGrids
) {
    // Create the sets within the maps.
    for (int i = 0; i < boardSideLength; ++i) {
        rows[i] = std::unordered_set<int>();
        columns[i] = std::unordered_set<int>();
        subGrids[i] = std::unordered_set<int>();
    }

    // Initialize grid with input string.
    for (int i = 0, len = sudokuInput.length(); i < len; ++i) {
        if (sudokuInput[i] == validChars[9]) { // Empty cell.
            grid.push_back(-1);
        } else if (sudokuInput[i] != validChars[10]) { // Number.
            grid.push_back(sudokuInput[i] - '0');
        }
    }

    // Initialize rows/columns/subgrids with grid.
    for(int i = 0, len = grid.size(); i < len; ++i) {
        int rowNumber = i / boardSideLength;
        int columnNumber = i % boardSideLength;
        int subGridNumber = (rowNumber / sqrtBoardSideLength) * sqrtBoardSideLength + columnNumber / sqrtBoardSideLength;
        rows[rowNumber].insert(grid[i]);
        columns[columnNumber].insert(grid[i]);
        subGrids[subGridNumber].insert(grid[i]);
    }
}

/// @brief Solves the passed `std::vector` that represents a sudoku board grid. 
/// @param d `Display` object for real-time updates.
/// @param willDisplayRealTime `bool` that enables real-time updates to console.
/// @param grid `std::vector` that holds the number representation of the sudoku board with indices as cell numbers.
/// @param rows `std::map` that holds an `std::unordered_set` of numbers per row number in the sudoku board.
/// @param columns `std::map` that holds an `std::unordered_set` of numbers per column number in the sudoku board.
/// @param subGrids `std::map` that holds an `std::unordered_set` of numbers per subgrid number in the sudoku board.
void Main::solveSudoku(
    Display &d,
    bool willDisplayRealTime,
    std::vector<int> &grid, 
    std::map<int, std::unordered_set<int>> &rows,
    std::map<int, std::unordered_set<int>> &columns, 
    std::map<int, std::unordered_set<int>> &subGrids
) {
    if (DFS(d, willDisplayRealTime, getNextEmptyCell(grid, -1),  grid, rows, columns, subGrids)) {
        d.clearConsole();
        d.displayBoard(grid);
        std::cout << "\nSolution found.\n";
    } else {
        d.displayBoard(grid);
        std::cout << "\nSolution cannot be found.\n";
    }
}

/// @brief Solves a passed sudoku board.
/// @param d `Display` object for real-time updates.
/// @param willDisplayRealTime `bool` that enables real-time updates to console.
/// @param currentIndex `int` that holds the current index where the function was called.
/// @param grid `std::vector` that holds the number representation of the sudoku board with indices as cell numbers.
/// @param rows `std::map` that holds an `std::unordered_set` of numbers per row number in the sudoku board.
/// @param columns `std::map` that holds an `std::unordered_set` of numbers per column number in the sudoku board.
/// @param subGrids `std::map` that holds an `std::unordered_set` of numbers per subgrid number in the sudoku board.
/// @return `true` (if successful)
///
/// `false` (if unsuccessful)
bool Main::DFS(
    Display &d,
    bool willDisplayRealTime,
    int currentIndex,
    std::vector<int> &grid, 
    std::map<int, std::unordered_set<int>> &rows,
    std::map<int, std::unordered_set<int>> &columns, 
    std::map<int, std::unordered_set<int>> &subGrids
) {
    // Base case. Check if board is full.
    if (currentIndex == -1) {
        return true;
    } else {
        // Get row/col/sub-grid numbers.
        int rowNumber = currentIndex / boardSideLength;
        int columnNumber = currentIndex % boardSideLength;
        int subGridNumber = (rowNumber / sqrtBoardSideLength) * sqrtBoardSideLength + columnNumber / sqrtBoardSideLength;

        // Check through all digits.
        for (int i = 1; i < 10; ++i) {
            // Check for digit in rows/columns/subGrids if valid.
            if (rows[rowNumber].find(i) == rows[rowNumber].end() &&
                columns[columnNumber].find(i) == columns[columnNumber].end() &&
                subGrids[subGridNumber].find(i) == subGrids[subGridNumber].end()
            ) {
                // Insert digit into sudoku board.
                grid[currentIndex] = i;
                rows[rowNumber].insert(i);
                columns[columnNumber].insert(i);
                subGrids[subGridNumber].insert(i);

                // Real-time update to console.
                if (willDisplayRealTime) {
                    d.clearConsole();
                    d.displayBoard(grid);
                }

                // Call DFS on next cell.
                if (DFS(d, willDisplayRealTime, getNextEmptyCell(grid, currentIndex), grid, rows, columns, subGrids)) {

                    // Call is a success.
                    return true;
                }

                // Erase current digit in current index to prepare for backtracking.
                grid[currentIndex] = -1;
                rows[rowNumber].erase(i);
                columns[columnNumber].erase(i);
                subGrids[subGridNumber].erase(i);
            }
        }

        // Backtrack.
        return false;
    }
}
/// @brief Gets the next empty cell in the passed grid.
/// @param grid `std::vector` that holds the number representation of the sudoku board with indices as cell numbers.
/// @param currentIndex `int` that has the current index that the function is called in.
/// @return - `int` that contains the index of the next empty cell if found.
///
/// - `-1` if an empty cell cannot be found.
int Main::getNextEmptyCell(std::vector<int> &grid, int currentIndex) {
    currentIndex += 1;
    for (int len = grid.size(); currentIndex < len; ++currentIndex) {
        if (grid[currentIndex] == -1) {
            return currentIndex;
        }
    }
    return -1;
}
/// @brief Displays the passed `std::vector` to console.
/// @param grid `std::vector` that holds the number representation of the sudoku board with indices as cell numbers.
void Display::displayBoard(std::vector<int> &grid) {
    std::string rowDisplaySeparator = "+———+———+———+———+———+———+———+———+———+";
    std::stringstream board;
    std::cout << rowDisplaySeparator << '\n';
    for (int i = 0; i < boardSideLength; ++i) {
        for (int j = 0; j < boardSideLength; ++j) {
            if (grid[i * boardSideLength + j] != -1) {
                board << "| " << grid[i * boardSideLength + j] << ' ';
            } else {
                board << "|   ";
            }
        }
        board << "|\n" << rowDisplaySeparator << '\n';
    }
    std::cout << board.str();
}
/// @brief Asks user if they want to exit the application.
/// @return - `true` (if input is 'Y' or 'y')
///
/// - `false` (default behavior, if input is not 'N' or 'n')
bool Utils::exitConfirmation() {
        std::string input = "";
        std::cout << "Exit solver? [Y/N] (default = N): ";
        std::getline(std::cin, input);
        if (input == "Y" || input == "y") {
            return true;
        }
        return false;
}
/// @brief Clears console if `system(cls)` does not work as intended.
void Display::clearConsole() {
    std::cout << "\e[2J\e[1;1H"; //ANSI escape code to clear screen, move cursor to top-left.
}