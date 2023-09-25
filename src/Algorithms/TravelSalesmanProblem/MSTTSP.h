#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <math.h>
#include <stack>
std::vector<int> computeKruscalMSTTSP(std::vector<std::tuple<int,int>> coord);
std::vector<int> computePrimMSTTSP(std::vector<std::tuple<int,int>> coord);
