#pragma once
#include <vector>
#include <tuple>

std::vector<int> computeNearestInsertionHeuristicTSP(std::vector<std::tuple<int,int>> coord);
std::vector<int> computeRandomInsertionHeuristicTSP(std::vector<std::tuple<int,int>> coord);
std::vector<int> computeFarthestInsertionHeuristicTSP(std::vector<std::tuple<int,int>> coord);
std::vector<int> computeCheapestInsertionHeuristicTSP(std::vector<std::tuple<int,int>> coord);
