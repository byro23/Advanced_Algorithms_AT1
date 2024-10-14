#include "AStarSearch.h"
#include <gtest/gtest.h>
#include <vector>
#include <utility>

// Test case for finding a valid path for a small grid with only one valid path
TEST(AStarSearchTest, OneValidPathSmallGridTest) {
    std::vector<std::vector<int>> grid = {
        {1, 1, 1, 1},
        {1, 0, 0, 1},
        {1, 1, 1, 1},
        {0, 0, 1, 1}
    };

    std::pair<int, int> src = {0, 0};
    std::pair<int, int> dest = {3, 2};

    std::vector<std::pair<int, int>> expected_path = {{0, 0}, {1, 0}, {2, 1}, {3, 2} };

    EXPECT_EQ(aStarSearch(grid, src, dest), expected_path);
}

TEST(AStarSearchTest, SmallGridTest2) {
    std::vector<std::vector<int>> grid = {
        {0,1,1,1,1,1},
        {1,1,0,0,0,0},
        {0,1,0,0,1,0},
        {0,0,1,1,1,0}
    };

    std::pair<int, int> src = {0, 5};
    std::pair<int, int> dest = {3, 4};

    std::vector<std::pair<int, int>> expected_path = {
        {0,5}, {0,4}, {0,3}, {0,2}, {1,1}, {2,1},
        {3,2}, {3,3}, {3,4}
    };

    EXPECT_EQ(aStarSearch(grid, src, dest), expected_path);
}

TEST(AStarSearchTest, OneValidPathLargeGridTest) {
    std::vector<std::vector<int>> grid = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    std::pair<int, int> src = {0, 0};
    std::pair<int, int> dest = {14, 11};

    std::vector<std::pair<int, int>> expected_path = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4,0}, {5,1},
    {6,2}, {7,3}, {7,4}, {8,5}, {9,6}, {10,7}, {11,8}, {12,9}, {13,9}, {14,10}, {14,11}};

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
        {0, 0, 0},
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
