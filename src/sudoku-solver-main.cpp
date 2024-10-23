// https://github.com/a22Dv/sudoku-solver-cpp

#include "sudoku-solver-header.h"

int main(int argc, char* argv[]) {
    Main m = Main();
    Utils u = Utils();
    Display d = Display();
    std::string_view validChars = "123456789.-";

    // Main loop.
    while (true) {
        d.clearConsole();
        std::cout << "sudoku-solver-cpp [1.0.0]\n";
        std::string sudokuInput = "";
        bool willDisplayRealTime = true;

        // Get user input.
        while (true) {
            sudokuInput = m.getSudokuBoard(validChars); 
            willDisplayRealTime = m.getRTUpdateStatus(); 

            // Validate user input, break if valid, else continue.
            if (m.validateInputs(sudokuInput, validChars)) {
                break;
            } else {
                d.clearConsole();
                continue;
            }
        }

        // index acts as cell ID -> number stored in cell.
        std::vector<int> grid = {}; 

        // Stores row/col/subgrid number -> numbers in corresponding row/column/subgrid.
        std::map<int, std::unordered_set<int>> rows = {}, columns = {}, subGrids = {}; 

        // Fill in vectors/maps/sets.
        m.initialize(validChars, sudokuInput, grid, rows, columns, subGrids);
        
        // Solve sudoku board.
        m.solveSudoku(d, willDisplayRealTime, grid, rows, columns, subGrids);

        // Ask if user wants to exit application.
        if (u.exitConfirmation()) {
            break;
        }
    }
    return 0;
}

