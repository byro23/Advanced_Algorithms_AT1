//
// Created by byroj on 30/09/2024.
//

#ifndef ASTARSEARCH_H
#define ASTARSEARCH_H
#include <vector>

struct Cell;

bool isValid(int row, int col, int rowLength, int colLength);

bool isUnblocked(const std::vector<std::vector<int>>& grid, int row, int col);

bool isDestination(const std::pair<int, int> &source, const std::pair<int, int> &destination);

double calculateHValue(int row, int col, const std::pair<int, int> &dest);

std::vector<std::pair<int,int>> tracePath(const std::vector<std::vector<Cell>>& cellDetails, const std::pair<int, int> &dest);

std::vector<std::pair<int, int>> aStarSearch(const std::vector<std::vector<int>>& grid, const std::pair<int, int>& src,
                                             const std::pair<int, int>& dest);

#endif //ASTARSEARCH_H
