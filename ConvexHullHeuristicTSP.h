#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <math.h>
#include <stack>


std::vector<int> computeConvexHullHeuristicNearestInsertionTSP(std::vector<std::tuple<int,int>> coord);
std::vector<int> computeConvexHullHeuristicRandomInsertionTSP(std::vector<std::tuple<int,int>> coord);
std::vector<int> computeConvexHullHeuristicFarthestInsertionTSP(std::vector<std::tuple<int,int>> coord);
std::vector<int> computeConvexHullHeuristicCheapestInsertionTSP(std::vector<std::tuple<int,int>> coord);
