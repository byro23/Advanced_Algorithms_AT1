#include "AStarSearch.h"
#include <gtest/gtest.h>
#include <vector>
#include <utility>

// Test case for finding a valid path
TEST(AStarSearchTest, ValidPathTest) {
    std::vector<std::vector<int>> grid = {
        {1, 1, 1, 1},
        {1, 0, 0, 1},
        {1, 1, 1, 1},
        {0, 0, 1, 1}
    };

    std::pair<int, int> src = {0, 0};
    std::pair<int, int> dest = {3, 3};

    std::vector<std::pair<int, int>> expected_path = {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {3, 3}};

    EXPECT_EQ(aStarSearch(grid, src, dest), expected_path);
}

// Test case when source is already the destination
TEST(AStarSearchTest, AlreadyAtDestinationTest) {
    std::vector<std::vector<int>> grid = {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}
    };

    std::pair<int, int> src = {1, 1};
    std::pair<int, int> dest = {1, 1};

    // Construct an empty vector explicitly
    std::vector<std::pair<int, int>> expected_path;

    EXPECT_EQ(aStarSearch(grid, src, dest), expected_path);
}

// Test case where source or destination is blocked
TEST(AStarSearchTest, BlockedPathTest) {
    std::vector<std::vector<int>> grid = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };

    std::pair<int, int> src = {0, 0};
    std::pair<int, int> dest = {1, 1}; // Destination is blocked

    // Construct an empty vector explicitly
    std::vector<std::pair<int, int>> expected_path;

    EXPECT_EQ(aStarSearch(grid, src, dest), expected_path);
}

// Test case for invalid source or destination
TEST(AStarSearchTest, InvalidSourceOrDestinationTest) {
    std::vector<std::vector<int>> grid = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    std::pair<int, int> src = {-1, -1}; // Invalid source
    std::pair<int, int> dest = {2, 2};  // Valid destination

    // Construct an empty vector explicitly
    std::vector<std::pair<int, int>> expected_path;

    EXPECT_EQ(aStarSearch(grid, src, dest), expected_path);

    src = {0, 0};  // Valid source
    dest = {5, 5}; // Invalid destination

    EXPECT_EQ(aStarSearch(grid, src, dest), expected_path);
}

// Test case for a grid with no valid path
TEST(AStarSearchTest, NoValidPathTest) {
    std::vector<std::vector<int>> grid = {
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1}
    };

    std::pair<int, int> src = {0, 0};
    std::pair<int, int> dest = {2, 0}; // No valid path

    // Construct an empty vector explicitly
    std::vector<std::pair<int, int>> expected_path;

    EXPECT_EQ(aStarSearch(grid, src, dest), expected_path);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
