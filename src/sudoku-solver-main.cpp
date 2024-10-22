#include "sudoku-solver-header.h"

int main(int argc, char* argv[]) {
    Main m = Main();
    Utils u = Utils();
    std::string_view validChars = "123456789.-";

    // Main loop.
    while (true) {
        std::string sudokuInput = "";
        bool willDisplayRealTime = true;

        // Get user input.
        while (true) {
            //sudokuInput = m.getSudokuBoard(validChars); // Actual Implementation.
            sudokuInput = "53..7....-6..195...-.98....6.-8...6...3-4..8.3..1-7...2...6-.6....28.-...419..5-....8..79"; // Debugging purposes only.
            willDisplayRealTime = m.getRTUpdateStatus();
            if (m.validateInputs(sudokuInput, validChars)) {
                break;
            } else {
                u.clearConsole();
                continue;
            }
        }
        // Validate user input, break if valid, else continue.
        // Initialize used vectors/maps/sets.
        // Fill in vectors/maps/sets.
        // Solve sudoku board.
        // Display real-time updates.
        // Show final result, show initial configuration if solution cannot be found. Along with a corresponding message.
        // Ask if user wants to exit application.
        if (u.exitConfirmation()) {
            break;
        }
    }
    return 0;
}

