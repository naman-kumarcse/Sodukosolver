#include <iostream>
#include <vector>

using namespace std;

void printGrid(const vector<vector<int>>& grid) {
    for (int row = 0; row < 9; row++) {
        if (row % 3 == 0 && row != 0) {
            cout << "---------------------\n";
        }
        for (int col = 0; col < 9; col++) {
            if (col % 3 == 0 && col != 0) {
                cout << " | ";
            }
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if a number is valid in the row
bool isRowSafe(const vector<vector<int>>& grid, int row, int num) {
    for (int col = 0; col < 9; col++) {
        if (grid[row][col] == num) {
            return false;
        }
    }
    return true;
}

// Function to check if a number is valid in the column
bool isColSafe(const vector<vector<int>>& grid, int col, int num) {
    for (int row = 0; row < 9; row++) {
        if (grid[row][col] == num) {
            return false;
        }
    }
    return true;
}

// Function to check if a number is valid in the 3x3 box
bool isBoxSafe(const vector<vector<int>>& grid, int startRow, int startCol, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (grid[row + startRow][col + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

// Function to check if it's safe to place a number in a given cell
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
    return isRowSafe(grid, row, num) &&
           isColSafe(grid, col, num) &&
           isBoxSafe(grid, row - row % 3, col - col % 3, num);
}

// Backtracking function to solve the Sudoku
bool solveSudoku(vector<vector<int>>& grid) {
    int row = -1, col = -1;
    bool isEmpty = true;
    
    // Find an empty cell
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                isEmpty = false;
                break;
            }
        }
        if (!isEmpty) {
            break;
        }
    }
    
    // If there is no empty cell, the Sudoku is solved
    if (isEmpty) {
        return true;
    }

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) {
                return true;
            }
            grid[row][col] = 0; // Backtrack
        }
    }
    
    return false;
}

int main() {
    vector<vector<int>> grid = {
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

    cout << "Initial Sudoku Puzzle: " << endl;
    printGrid(grid);

    if (solveSudoku(grid)) {
        cout << "Solved Sudoku Puzzle: " << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists for the given Sudoku puzzle." << endl;
    }

    return 0;
}
