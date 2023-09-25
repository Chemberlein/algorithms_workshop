#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <math.h>
#include <stack>
#include "ChristofidesHeuristicTSP.h"
#include "../MinimumSpanningTree/MST.h"

using namespace std;

vector<int> computeChristofidesHeuristicTSP(vector<tuple<int,int>> coord){
	vector<tuple<int,int>> mst = computeKruskalMST(coord);
	int n = coord.size();
	vector<int> ans;
	return ans;
}
