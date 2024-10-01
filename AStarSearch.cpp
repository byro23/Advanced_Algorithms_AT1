//
// Created by byroj on 30/09/2024.
//

#include "AStarSearch.h"

#include <iostream>
#include <utility>
#include <vector>

struct Cell {
    int parent_i, parent_j;
    double f,g,h;

};

bool isValid(int row, int col, int rowLength, int colLength) {

    return (row >= 0) && (row < rowLength) && (col >= 0) && (col < colLength);
}

bool isUnblocked(std::vector<std::vector<int>>& grid, int row, int col) {
    return grid[row][col] == 1;
}


void aStarSearch(std::vector<std::vector<int>> grid, std::pair<int, int> src, std::pair<int, int> dest) {
    int rowSize  = grid.size();
    int colSize = grid[0].size(); // Guaranteed each r

    if(!isValid(src.first, src.second, rowSize, colSize) || !isValid(dest.first, dest.second, rowSize, colSize)) {
        std::cout << "Source or destination is invalid\n";
        return;
    }

    if(!isUnblocked(grid, src.first, src.second) || !isUnblocked(grid, dest.first, dest.second)) {
        std::cout << "Source or destination is blocked.";
        return;
    }

    // 1 the cell is not blocked
    // 0 the cell is blocked






}