#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <math.h>
#include <stack>
#include "MST.h"
#include "DSU.h"
#include <limits.h>
using namespace std;

vector<tuple<int,int>> computeKruskalMST(vector<tuple<int,int>> coord){
	vector<std::tuple<int,int>> MST;
	vector<tuple<int,int,int>> distances;
	for(int i=0;i<coord.size();i++){
		for(int j=i+1;j<coord.size();j++){
			distances.push_back(make_tuple(i,j,sqrt(pow(get<0>(coord[i])-get<0>(coord[j]),2)+pow(get<1>(coord[i])-get<1>(coord[j]),2))));
		}
	}	
	sort(distances.begin(),distances.end(),[](tuple<int,int,int> a,tuple<int,int,int> b){return	get<2>(a)<get<2>(b);});
	int n =coord.size();
	DSU dsu(n);
	for(int i=0;i<distances.size();i++){
		if(dsu.find(get<0>(distances[i]))!=dsu.find(get<1>(distances[i]))){
			MST.push_back(make_tuple(get<0>(distances[i]),get<1>(distances[i])));
			dsu.unite(get<0>(distances[i]),get<1>(distances[i]));
		}
	}
	return MST;
}

int minKey(int key[], bool hash[],int n){
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++)
        if (hash[v] == false && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

vector<tuple<int,int>> computePrimMST(vector<tuple<int,int>> coord){
	vector<std::tuple<int,int>> MST;
	int n = coord.size();
	int distances[n][n]={0};
	for(int i =0;i<n;i++){
		for(int j =0;j<n;j++){
			distances[i][j]=sqrt(pow(get<0>(coord[i])-get<0>(coord[j]),2)+pow(get<1>(coord[i])-get<1>(coord[j]),2));
			distances[j][i]=sqrt(pow(get<0>(coord[i])-get<0>(coord[j]),2)+pow(get<1>(coord[i])-get<1>(coord[j]),2));
		}
	}
	int parent[n];
	int key[n];
	bool hash[n];
	for(int i = 0;i<n;i++)
		key[i]=INT_MAX,hash[i]=false;
	key[0]=0;
	parent[0]=-1;
	for(int i =0;i<n;i++){
		int u = minKey(key,hash,n);
		hash[u]=true;
		for(int j =0;j<n;j++){
			if(distances[u][j] && !hash[j] && distances[u][j]<key[j])
				parent[j] = u,key[j]=distances[u][j];
		}
	}
	for(int i =1;i<n;i++){
		MST.push_back(make_tuple(parent[i],i));
	}
	return MST;
}