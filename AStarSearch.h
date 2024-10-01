//
// Created by byroj on 30/09/2024.
//

#ifndef ASTARSEARCH_H
#define ASTARSEARCH_H
#include <vector>

struct Cell;

bool isValid(int row, int col, int rowLength, int colLength);

bool isUnblocked(std::vector<std::vector<int>>& grid, int row, int col);

bool isDestination(std::pair<int, int> source, std::pair<int, int> destination);

double calculateHValue(int row, int col, std::pair<int, int> dest);

std::vector<std::pair<int,int>> tracePath(const std::vector<std::vector<Cell>>& cellDetails, std::pair<int, int> dest);

std::vector<std::pair<int, int>> aStarSearch(std::vector<std::vector<int> > grid, std::pair<int, int> src,
                                             std::pair<int, int> dest);

#endif //ASTARSEARCH_H
