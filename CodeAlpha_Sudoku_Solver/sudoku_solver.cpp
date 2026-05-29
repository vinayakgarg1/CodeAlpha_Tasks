#include <iostream>
#include <limits>
using namespace std;
const int N = 9;

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        if (row % 3 == 0 && row != 0) {
            cout << "------+-------+------\n";
        }
        for (int col = 0; col < N; col++) {
            if (col % 3 == 0 && col != 0) cout << "| ";
            if (grid[row][col] == 0) cout << ". ";
            else cout << grid[row][col] << " ";
        }
        cout << "\n";
    }
}

// Check constraints (row, column, and 3x3 box)
bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num) return false;
    }
    for (int x = 0; x < N; x++) {
        if (grid[x][col] == num) return false;
    }
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) return false;
        }
    }
    return true;
}

// Backtracking Solver
bool solveSudoku(int grid[N][N], int row, int col) {
    if (row == N - 1 && col == N) return true;
    if (col == N) {
        row++;
        col = 0;
    }
    if (grid[row][col] != 0) return solveSudoku(grid, row, col + 1);
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid, row, col + 1)) return true;
            grid[row][col] = 0; // Backtrack
        }
    }
    return false;
}

int main() {
    int grid[N][N];
    cout << "===================================================\n";
    cout << "                  SUDOKU SOLVER                    \n";
    cout << "===================================================\n";
    cout << "Enter your Sudoku puzzle row by row.\n";
    cout << "Enter 9 numbers per row separated by spaces (use 0 for empty cells):\n\n";
    // Getting grid input from user
    for (int i = 0; i < N; i++) {
        cout << "Row " << (i + 1) << ": ";
        for (int j = 0; j < N; j++) {
            while (!(cin >> grid[i][j]) || grid[i][j] < 0 || grid[i][j] > 9) {
                cout << "Invalid input! Please enter digits between 0 and 9: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    cout << "\n---------------------------------------------------\n";
    cout << "Your Entered Puzzle:\n";
    printGrid(grid);
    cout << "---------------------------------------------------\n\n";
    if (solveSudoku(grid, 0, 0)) {
        cout << "Puzzle Solved Successfully:\n";
        printGrid(grid);
    } else cout << "[ERROR] No solution exists for this Sudoku puzzle.\n";
    cout << "===================================================\n";
    return 0;
}