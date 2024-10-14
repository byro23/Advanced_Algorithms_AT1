//
// Created by byroj on 30/09/2024.
//

#include "AStarSearch.h"

#include <cfloat>
#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>


struct Cell {
    int parent_i, parent_j;
    double f,g,h;

    Cell() {
        f = g = h = std::numeric_limits<double>::max();
        // F: Total Cost | G: Cost from source to current cell | H: Estimated cost from current cell to destination using heuristic
        // Keeps track of current most efficient path to the cell

        parent_i = parent_j = -1; // Coordinates of the parent cell in the path
    }

};

// Checks if the cell is valid
bool isValid(int row, int col, int rowLength, int colLength) {
    return (row >= 0) && (row < rowLength) && (col >= 0) && (col < colLength);
}

// Checks if a cell is walkable
bool isUnblocked(std::vector<std::vector<int>>& grid, int row, int col) {
    return grid[row][col] == 1;
}

// Checks if the destination cell has been reached
bool isDestination(std::pair<int, int> source, std::pair<int, int> destination) {
    return source.first == destination.first && source.second == destination.second;
}

// Euclidean Distance heuristic
double calculateHValue(int row, int col, std::pair<int, int> dest) {
    // Using Euclidean distance as a heuristic (can switch to Manhattan distance if diagonal moves aren't allowed)
    // Chosen due to suitability for diagonal movements
    return std::sqrt((row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second));
}

// Traces the path from the source to destination by using the parent cell values
std::vector<std::pair<int,int>> tracePath(const std::vector<std::vector<Cell>>& cellDetails, std::pair<int, int> dest) {
    std::vector<std::pair<int, int>> path;
    int row = dest.first;
    int col = dest.second;
    std::stack<std::pair<int, int>> pathStack;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
        pathStack.emplace(row, col);
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    pathStack.emplace(row, col);

    while (!pathStack.empty()) {
        path.push_back(pathStack.top());
        pathStack.pop();
    }

    return path;
}


std::vector<std::pair<int, int>> aStarSearch(std::vector<std::vector<int>>& grid, std::pair<int, int>& src,
                                             std::pair<int, int>& dest) {
    int rowSize  = grid.size();
    int colSize = grid[0].size(); // Guaranteed each row has the same number of columns

    if(!isValid(src.first, src.second, rowSize, colSize) || !isValid(dest.first, dest.second, rowSize, colSize)) {
        std::cout << "Source or destination is invalid\n";
        return {};
    }

    if(!isUnblocked(grid, src.first, src.second) || !isUnblocked(grid, dest.first, dest.second)) {
        std::cout << "Source or destination is blocked.";
        return {};
    }

    if(isDestination(src, dest)) {
        std::cout << "Already at the destination.";
        return {};
    }

    // 2d array used to store the details of each cell
    std::vector<std::vector<bool>> closedList(rowSize, std::vector<bool>(colSize, false));

    // Cell Details for each cell
    std::vector<std::vector<Cell>> cellDetails(rowSize, std::vector<Cell>(colSize));

    int i, j;

    // Initialise the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    // Priority queue storing f-value and cell coordinates. Configured for cell with smallest f-value to be processed first
    std::priority_queue<std::pair<double, std::pair<int, int>>, std::vector<std::pair<double, std::pair<int, int>>>, std::greater<>> openList;
    // Push the starting cell onto the open list
    openList.push({0.0, {i, j}});

    // Directions for all 8 moves (N, S, E, W, NE, NW, SE, SW)
    int rowDir[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int colDir[] = {0, 0, 1, -1, 1, -1, 1, -1};

    while(!openList.empty()) {
        auto current = openList.top();
        openList.pop();

        i = current.second.first;
        j = current.second.second;
        closedList[i][j] = true;

        for(int dir = 0; dir < 8; dir++) {

            int newRow = i + rowDir[dir];
            int newCol = j + colDir[dir];

            if(isValid(newRow, newCol, rowSize, colSize)) {
                // If destination cell is reached
                if(isDestination({newRow, newCol}, dest)) {
                    cellDetails[newRow][newCol].parent_i = i;
                    cellDetails[newRow][newCol].parent_j = j;
                    std::cout << "The destination cell is found.\n";
                    return tracePath(cellDetails, dest);
                }

                // Only process unblocked and unvisited cells
                if(!closedList[newRow][newCol] && isUnblocked(grid, newRow, newCol))  {
                    double gNew = cellDetails[i][j].g + (dir < 4 ? 1.0 : 1.414);
                    double hNew = calculateHValue(newRow, newCol, dest);
                    double fNew = gNew + hNew;

                    // If the new path is better, update cell details
                    if(cellDetails[newRow][newCol].f > fNew) {
                        openList.push({fNew, {newRow, newCol}});
                        cellDetails[newRow][newCol].f = fNew;
                        cellDetails[newRow][newCol].g = gNew;
                        cellDetails[newRow][newCol].h = hNew;
                        cellDetails[newRow][newCol].parent_i = i;
                        cellDetails[newRow][newCol].parent_j = j;
                    }
                }
            }

        }


    }

    std::cerr << "Failed to find the destination cell";
    return {};

}