#include "input.cpp"
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

struct Location {
    int row;
    int col;

    Location(int r, int c) : row(r), col(c) {}
};

int calculateSequenceLength(Masukan input, int idx) {
    int length = 0;
    for (int i = 0; i < input.maxSequenceSize; i++) {
        if (input.sequences[idx][i] != "") {
            length++;
        }
    }
    return length;
}

int calculateScore(Masukan input, vector<string> tempRoute) {
    int score = 0;
    int size = tempRoute.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < input.numberOfSequences; j++) {
            int seqLength = calculateSequenceLength(input, j);
            if (size - i >= seqLength) {
                int count = 0;
                for (int k = 0; k < seqLength; k++) {
                    if (tempRoute[i + k] == input.sequences[j][k]) {
                        count++;
                    }
                }
                if (count == seqLength) {
                    score += input.rewards[j];
                }
            }
        }
    }

    if (score == 0) {
        score = -1;
    }

    return score;
}

bool isSameSequence(vector<string> route, vector<string> correctRoute) {
    if (route.size() != correctRoute.size()) {
        return false;
    } else {
        bool isCorrect = true;
        for (int i = 0; i < correctRoute.size(); ++i) {
            if (route[i] != correctRoute[i]) {
                isCorrect = false;
                break;
            }
        }
        return isCorrect;
    }
}

// Global variables to store the maximum reward and corresponding route
int maxReward = 0;
vector<string> maxRoute;
vector<Location> maxRouteLocations; // Store the locations of the max route

void exploreRoutes(Masukan input, vector<vector<string>> &matrix, int row, int col, vector<string> &route, vector<Location> &routeLocations, vector<vector<bool>> &visited, int bufferSize, bool isVertical) {
    // Add current point to the route
    route.push_back(matrix[row][col]);
    routeLocations.push_back(Location(row, col));
    visited[row][col] = true;
    int tempReward = calculateScore(input, route);
    if (tempReward > maxReward) {
        maxReward = tempReward;
        maxRoute = route;
        maxRouteLocations = routeLocations; // Update the max route locations
    }

    // Base case: if the route size equals buffer
    if (route.size() == bufferSize) {
        // Backtrack
        route.pop_back();
        routeLocations.pop_back();
        visited[row][col] = false;
        return;
    }

    // Explore vertically
    if (isVertical) {
        for (int i = 0; i < input.matrixHeight; ++i) {
            if (!visited[i][col]) {
                exploreRoutes(input, matrix, i, col, route, routeLocations, visited, bufferSize, !isVertical);
            }
        }
    }

    // Explore horizontally
    else {
        for (int j = 0; j < input.matrixWidth; ++j) {
            if (!visited[row][j]) {
                exploreRoutes(input, matrix, row, j, route, routeLocations, visited, bufferSize, !isVertical);
            }
        }
    }

    // Backtrack
    route.pop_back();
    routeLocations.pop_back();
    visited[row][col] = false;
}
