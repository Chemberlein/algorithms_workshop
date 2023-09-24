#pragma once
#include <vector>
#include <tuple>

std::vector<int> computeNearestInsertionHeuristicTSP(std::vector<std::tuple<int,int>> coord);
std::vector<int> computeRandomInsertionHeuristicTSP(std::vector<std::tuple<int,int>> coord);
std::vector<int> computeFarthestInsertionHeuristicTSP(std::vector<std::tuple<int,int>> coord);
std::vector<int> computeCheapestInsertionHeuristicTSP(std::vector<std::tuple<int,int>> coord);


int chosePositionToInsert(std::vector<int> cycle,std::vector<std::tuple<int,int>> coord,int k);
int choseNearestPoint(std::vector<std::tuple<int,int,int>> dist,bool hash[]);
int choseRandomPoint(bool hash[],int n);
int choseFarthestPoint(std::vector<std::tuple<int,int,int>> dist,bool hash[]);
std::tuple<int,int> choseCheapestPoint(std::vector<std::tuple<int,int>> coord,std::vector<int> cycle,bool hash[]);