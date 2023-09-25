#pragma once
#include <vector>
#include <algorithm>
#include <tuple>
#include <math.h>
#include <stack>

/*Jarvis O(n*m)<=O(n^2) where n is number of input points and m (m<=n) is a number of hull points */
std::vector<int> computeConvexHullJarvis(std::vector<std::tuple<int,int>> coord);

/*GrahamScan O(n log(n)) where n is number of input points*/
std::vector<int> computeConvexHullGrahamScan(std::vector<std::tuple<int,int>> coord);


