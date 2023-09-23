#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <math.h>
#include <stack>
#include "MSTTSP.h"
#include "MST.h"

/*
 * Implementation of algorithm to solve tsp based on Kruscal MST 
 * vector<int> computeKruscalMSTTSP(vector<tuple<int,int>> coord)
 * Take vector of tuples of cordinates as an input 
 * Return  vector integers that sescribe traversal that visit each point just once
 * Algorithm :
 *	1) Construct a minimum spanning tree 
 *	2) Then chouse some vertex to be root 
 *	3) Traverse all the vertices by depth-first search, record the sequence of vertices
 *  4) Use shortcut strategy to generate a feasible tour
 * Implementation of algorithm to solve tsp based on Prim MST  
 * vector<int> computePrimMSTTSP(vector<tuple<int,int>> coord)
 * Take vector of tuples of cordinates as an input 
 * Return  vector integers that sescribe traversal that visit each point just once
 * Algorithm :
 *	1) Let 1 be the starting and ending point for salesman.
 *  2) Construct MST from with 1 as root using Prim’s Algorithm.
 *  3) List vertices visited in preorder walk of the constructed MST and add 1 at the end.
*/

using namespace std;


vector<vector<int>> graphFormatVectorOfTuplesToTable(int n,vector<tuple<int,int>> vot){
	vector<vector<int>> table;
	for(int i=0;i<n;i++){
		vector<int> tmp;
		for(int j=0;j<n;j++)
			tmp.push_back(0);
		table.push_back(tmp);
	}
	
	for(int i=0;i<vot.size();i++){
		table[get<0>(vot[i])][get<1>(vot[i])]=1;
		table[get<1>(vot[i])][get<0>(vot[i])]=1;
	}
	return table;
}

vector<int> depthFirstSearchTraverse(vector<vector<int>> graph){
	vector<int> traverse;
	int n = graph.size();
	int hash[n];
	for(int i =0;i<n;i++){
		hash[i]=0;
	}
	stack<int> s;
	traverse.push_back(0);
	hash[0]=1;
	s.push(0);
	int curr = 0;
	bool finish = false;
	while(!finish){
		traverse.push_back(curr);
		finish = true;
		for(int i = 0;i<graph.size();i++){
			if(graph[curr][i]==1 && hash[i]==0){
                hash[i]=1;
				s.push(i);
				curr=i;
				finish=false;
				break;
			}
		}
		if(finish){
			s.pop();
			if(s.empty())
				finish = true;
			else{
				finish=false;
				curr=s.top();
			}
		}
	}
	return traverse;
}

vector<int> getShortCut(vector<int> trav, int n){
	int hash[n];
	vector<int> shortCut;
	for(int i =0;i<n;i++){
		hash[i]=0;
	}
	for(auto i:trav){
		if(hash[i]==0){
			shortCut.push_back(i);
			hash[i]=1;
		}
	}
	return shortCut;
}
vector<int> computeKruscalMSTTSP(vector<tuple<int,int>> coord){
	vector<tuple<int,int>> mst = computeKruskalMST(coord);
	int n = coord.size();
	vector<int> ans;
	ans = getShortCut(depthFirstSearchTraverse(graphFormatVectorOfTuplesToTable(n,mst)),n);
    ans.push_back(ans[0]);
	return ans;
}
vector<int> computePrimMSTTSP(vector<tuple<int,int>> coord){
	vector<tuple<int,int>> mst = computePrimMST(coord);
	int n = coord.size();
	vector<int> ans;
	ans = getShortCut(depthFirstSearchTraverse(graphFormatVectorOfTuplesToTable(n,mst)),n);
    ans.push_back(ans[0]);
	return ans;
}
