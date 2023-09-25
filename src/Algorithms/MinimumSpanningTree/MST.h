#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <math.h>
#include <stack>

std::vector<std::tuple<int,int>> computeKruskalMST(std::vector<std::tuple<int,int>> coord);
std::vector<std::tuple<int,int>> computePrimMST(std::vector<std::tuple<int,int>> coord);
