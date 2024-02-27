#include <iostream>
#include <vector>

const int SIZE = 9;

// Function to print the Sudoku grid
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to check if a number can be placed at a given position
bool isSafe(const std::vector<std::vector<int>>& grid, int row, int col, int num) {
    // Check if 'num' is not present in the current row and column
    for (int x = 0; x < SIZE; ++x) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    // Check if 'num' is not present in the current 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to find an empty position in the Sudoku grid
bool findEmptyPosition(const std::vector<std::vector<int>>& grid, int& row, int& col) {
    for (row = 0; row < SIZE; ++row) {
        for (col = 0; col < SIZE; ++col) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(std::vector<std::vector<int>>& grid) {
    int row, col;

    if (!findEmptyPosition(grid, row, col)) {
        // If there are no empty positions, the puzzle is solved
        return true;
    }

    // Try placing numbers from 1 to 9
    for (int num = 1; num <= SIZE; ++num) {
        if (isSafe(grid, row, col, num)) {
            // If it's safe to place 'num' at the current position
            grid[row][col] = num;

            // Recur to fill the rest of the grid
            if (solveSudoku(grid)) {
                return true; // Puzzle solved successfully
            }

            // If placing 'num' at the current position doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    return false; // No number can be placed at the current position
}

int main() {
    // Original Sudoku puzzle
    std::vector<std::vector<int>> originalGrid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    // Copy the original puzzle for user input
    std::vector<std::vector<int>> userGrid = originalGrid;

    std::cout << "Original Sudoku Puzzle:\n";
    printGrid(originalGrid);

    std::cout << "\nEnter your solution (0 for empty cells):\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << "Row " << i + 1 << ", Column " << j + 1 << ": ";
            std::cin >> userGrid[i][j];
        }
    }

    std::cout << "\nYour Solution:\n";
    printGrid(userGrid);

    if (userGrid == originalGrid) {
        std::cout << "\nCongratulations! Your solution is correct.\n";
    } else {
        std::cout << "\nSorry, your solution is incorrect.\n";
    }

    return 0;
}
