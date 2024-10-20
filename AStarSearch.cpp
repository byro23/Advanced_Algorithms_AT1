//
// Created by byroj on 30/09/2024.
//

#include "AStarSearch.h"

#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>


// Cell Data Structure
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

// Checks if the given coordinates are within the grid boundaries
bool isValid(int row, int col, int rowLength, int colLength) {
    return (row >= 0) && (row < rowLength) && (col >= 0) && (col < colLength);
}

// Checks if a cell is walkable (i.e, not blocked by an obstacle)
auto isUnblocked(const std::vector<std::vector<int> > &grid, const int row, const int col) -> bool {
    return grid[row][col] == 1;
}

// Returns true if the current cell is the destination cell
bool isDestination(const std::pair<int, int> &source, const std::pair<int, int> &destination) {
    return source.first == destination.first && source.second == destination.second;
}

// Diagonal Distance Heuristic
// D = 1.0: Cost for orthogonal movement (N, S, E, W)
// D_diagonal = 1.414: Cost for diagonal movement (NE, NW, SE, SW)
double calculateHValue(const int row, const int col, const std::pair<int, int> &dest) {
    int dx = std::abs(row - dest.first); // Horizontal distance
    int dy = std::abs(col - dest.second); // Vertical distance

    double D = 1.0;           // Cost for orthogonal movement
    double D_diagonal = 1.414; // Cost for diagonal movement

    return D * std::max(dx, dy) + (D_diagonal - D) * std::min(dx, dy);
}

// Traces the path from the destination to the source using parent coordinates
// and returns the path as a vector of (row, col) pairs
std::vector<std::pair<int, int>> tracePath(const std::vector<std::vector<Cell>>& cellDetails, const std::pair<int, int> &dest) {
    std::vector<std::pair<int, int>> path;
    int row = dest.first;
    int col = dest.second;

    // Trace the path backward from the destination to the source
    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
        path.emplace_back(row, col); // Add the current cell to the path
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    path.emplace_back(row, col);  // Add the starting point

    std::reverse(path.begin(), path.end()); // Reverse to get the correct order
    return path;
}

// A* Search Algorithm to find the shortest path between src and dest on the grid
std::vector<std::pair<int, int>> aStarSearch(const std::vector<std::vector<int>>& grid, const std::pair<int, int>& src,
                                             const std::pair<int, int>& dest) {

    // Grid Dimensions
    const int rowSize  = static_cast<int>(grid.size());
    const int colSize = static_cast<int>(grid[0].size());

    // Check if the source and destination are within grid bounds
    if(!isValid(src.first, src.second, rowSize, colSize) || !isValid(dest.first, dest.second, rowSize, colSize)) {
        std::cout << "Source or destination is invalid\n";
        return {};
    }

    // Check if the source and destination are not blocked
    if(!isUnblocked(grid, src.first, src.second) || !isUnblocked(grid, dest.first, dest.second)) {
        std::cout << "Source or destination is blocked.";
        return {};
    }

    // Check if the source and destination are the same
    if(isDestination(src, dest)) {
        std::cout << "Already at the destination.";
        return {};
    }

    // Initialise closed list to track visited cells
    std::vector closedList(rowSize, std::vector<bool>(colSize, false));

    // Initialise cell details for all grid cells
    std::vector cellDetails(rowSize, std::vector<Cell>(colSize));

    int i, j;

    // Initialise the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    // Open list with cells to explore, prioritized by their f-value
    std::priority_queue<std::pair<double, std::pair<int, int>>, std::vector<std::pair<double, std::pair<int, int>>>, std::greater<>> openList;
    // Push the starting cell onto the open list
    openList.push({0.0, {i, j}});

    // Possible moves in 8 directions (N, S, E, W, NE, NW, SE, SW)
    int rowDir[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int colDir[] = {0, 0, 1, -1, 1, -1, 1, -1};

    while(!openList.empty()) {
        auto current = openList.top();
        openList.pop();

        i = current.second.first;
        j = current.second.second;
        closedList[i][j] = true; // Mark the cell as visited

        // Explore all 8 possible moves
        for(int dir = 0; dir < 8; dir++) {
            int newRow = i + rowDir[dir];
            int newCol = j + colDir[dir];

            // Check if the move is within bounds
            if(isValid(newRow, newCol, rowSize, colSize)) {
                // Check if destination cell is reached
                if(isDestination({newRow, newCol}, dest)) {
                    cellDetails[newRow][newCol].parent_i = i;
                    cellDetails[newRow][newCol].parent_j = j;
                    std::cout << "The destination cell is found.\n";
                    return tracePath(cellDetails, dest);
                }

                // Process the cell if it is unblocked and not yet visited
                if(!closedList[newRow][newCol] && isUnblocked(grid, newRow, newCol))  {
                    double gNew = cellDetails[i][j].g + (dir < 4 ? 1.0 : 1.414);
                    double hNew = calculateHValue(newRow, newCol, dest);
                    double fNew = gNew + hNew;

                    // Update the cell details if a better path is found
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