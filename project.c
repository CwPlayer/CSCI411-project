#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int currentSize = 0;
vector<vector<int>> grid;  // changes grid size based on input

// print grid
void printGrid() {
    for(int r = 0; r < currentSize; r++) {
        for(int c = 0; c < currentSize; c++)
            cout << grid[r][c] << " ";
        cout << endl;
    }
}

// check if num is valid
bool isValid(int row, int col, int num) {
    // row
    for(int c = 0; c < currentSize; c++)
        if(grid[row][c] == num) return false;
    // column
    for(int r = 0; r < currentSize; r++)
        if(grid[r][col] == num) return false;

    // box size depends on grid size
    // this is to determine the size of the "3x3 box". each grid sizes have different box size
    int boxR, boxC;
    if(currentSize == 4) { // 4x4 grid
        boxR = 2; boxC = 2; 
    }
    else if(currentSize == 6) { // 6x6 grid
        boxR = 2; boxC = 3; 
    }
    else if(currentSize == 9) { // 9x9 grid
        boxR = 3; boxC = 3; 
    }
    else if(currentSize == 16) { // 16x16 grid
        boxR = 4; boxC = 4; 
    }
    else boxR = 1; boxC = 1; // 1x1 grid wont use this ever. dummy for if on 16x16 grid
    
    //finds the start of the box 
    int startRow = row - (row % boxR);
    int startCol = col - (col % boxC);
    
    //check every cell to find if a num already exists
    for(int r = startRow; r < startRow + boxR; r++)
        for(int c = startCol; c < startCol + boxC; c++)
            if(grid[r][c] == num) return false; 

    return true;
}

// backtracking 
bool solveSudoku() {
    for(int row = 0; row < currentSize; row++) {
        for(int col = 0; col < currentSize; col++) {
            if(grid[row][col] == 0) {
                for(int num = 1; num <= currentSize; num++) {
                    if(isValid(row, col, num)) {
                        grid[row][col] = num;
                        if (solveSudoku()) return true; //dfs
                        grid[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

int main() {
    string line;
    vector<vector<int>> tempGrid;
    int rowCount = 0, maxCol = 0;
    // reads input from file
    while(getline(cin, line)) {
        if(line.empty()) continue;
        vector<int> row;
        int num;
        istringstream ss(line);
        while(ss >> num) { // gets the grid size from input
            row.push_back(num);
        }
        if(row.size() > maxCol) maxCol = row.size();
        tempGrid.push_back(row);
        rowCount++;
    }

    currentSize = max(rowCount, maxCol);

    // resize grid to currentSize
    grid.assign(currentSize, vector<int>(currentSize, 0));
    for(int r = 0; r < tempGrid.size(); r++)
        for(int c = 0; c < tempGrid[r].size(); c++)
            grid[r][c] = tempGrid[r][c];

    if(solveSudoku()) {
        cout << "Solved Sudoku:\n";
        printGrid();
    } else {
        cout << "Can't solve!\n";
    }

    return 0;
}
