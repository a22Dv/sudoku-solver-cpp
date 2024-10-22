// https://github.com/a22Dv/sudoku-solver-cpp

#include "sudoku-solver-header.h"

/// @brief Gets the string that represents a sudoku board through console.
/// @param validChars A string for valid input characters, only used to display specified formatting within the function.
/// @return `std::string` User input string.
std::string Main::getSudokuBoard(std::string_view &validChars) {
    // &validChars = "123456789.-".
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
/// @return - true (default behavior, when user input != 'N' or 'n')
///
/// - false (if user input == 'N' or 'n')
bool Main::getRTUpdateStatus() {
    std::string input = "";
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
/// @return - true (if valid)
///
/// - false (if invalid)
bool Main::validateInputs(std::string &sudokuInput, std::string_view &validChars) {
    if (sudokuInput.length() != 89) {
        return false;
    }
    for (char c : sudokuInput) {
        if (validChars.find(c) == std::string_view::npos) {
            return false;
        }
    }
    return true;
}
/// @brief Asks user if they want to exit the application.
/// @return - true (if input is 'Y' or 'y')
///
/// - false (default behavior, if input is not 'N' or 'n')
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
void Utils::clearConsole() {
    std::cout << "\e[2J\e[1;1H"; //ANSI escape code to clear screen, move cursor to top-left.
}