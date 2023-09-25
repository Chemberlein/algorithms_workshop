#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <math.h>
#include <stack>
#include "ConvexHullHeuristicTSP.h"
#include "InsertionHeuristicTSP.h"
#include "../ConvexHull/ConvexHull.h"
#include "../MinimumSpanningTree/MST.h"

using namespace std;

vector<int> computeConvexHullHeuristicNearestInsertionTSP(vector<tuple<int,int>> coord){
    vector<int> ans = computeConvexHullGrahamScan(coord);

	vector<tuple<int,int,int>> distances;
	for(int i=0;i<coord.size();i++){
		for(int j=i+1;j<coord.size();j++){
			distances.push_back(make_tuple(i,j,sqrt(pow(get<0>(coord[i])-get<0>(coord[j]),2)+pow(get<1>(coord[i])-get<1>(coord[j]),2))));
		}
	}
	sort(distances.begin(),distances.end(),[](tuple<int,int,int> a,tuple<int,int,int> b){return	get<2>(a)<get<2>(b);});
	int n =coord.size();
    bool hash[n];
    for(int i =0;i<n;i++)
        hash[i]=false;
    for(auto i:ans)
        hash[i]=true;
    while(true){
        int u = choseNearestPoint(distances,hash);
        if(u==-1){
            break;
        }
        hash[u]=true;
        int np = chosePositionToInsert(ans,coord,u);
        ans.insert(ans.begin()+np,u);
    }
    return ans;
}

std::vector<int> computeConvexHullHeuristicRandomInsertionTSP(std::vector<std::tuple<int,int>> coord){
    vector<int> ans = computeConvexHullGrahamScan(coord);

	vector<tuple<int,int,int>> distances;
	for(int i=0;i<coord.size();i++){
		for(int j=i+1;j<coord.size();j++){
			distances.push_back(make_tuple(i,j,sqrt(pow(get<0>(coord[i])-get<0>(coord[j]),2)+pow(get<1>(coord[i])-get<1>(coord[j]),2))));
		}
	}
	sort(distances.begin(),distances.end(),[](tuple<int,int,int> a,tuple<int,int,int> b){return	get<2>(a)<get<2>(b);});
	int n =coord.size();
    bool hash[n];
    for(int i =0;i<n;i++)
        hash[i]=false;
    int k  = 0;
    for(auto i:ans){
        if(!hash[i])
            k++;
        hash[i]=true;
    }
    while(k<n){
        k++;
        int u = choseRandomPoint(hash,n);
        if(u==-1){
            break;
        }
        hash[u]=true;
        int np = chosePositionToInsert(ans,coord,u);
        ans.insert(ans.begin()+np,u);
    }
    return ans;
}
std::vector<int> computeConvexHullHeuristicFarthestInsertionTSP(std::vector<std::tuple<int,int>> coord){
    vector<int> ans = computeConvexHullGrahamScan(coord);

	vector<tuple<int,int,int>> distances;
	for(int i=0;i<coord.size();i++){
		for(int j=i+1;j<coord.size();j++){
			distances.push_back(make_tuple(i,j,sqrt(pow(get<0>(coord[i])-get<0>(coord[j]),2)+pow(get<1>(coord[i])-get<1>(coord[j]),2))));
		}
	}
	sort(distances.begin(),distances.end(),[](tuple<int,int,int> a,tuple<int,int,int> b){return	get<2>(a)>get<2>(b);});
	int n =coord.size();
    bool hash[n];
    for(int i =0;i<n;i++)
        hash[i]=false;
    for(auto i:ans)
        hash[i]=true;
    while(true){
        int u = choseFarthestPoint(distances,hash);
        if(u==-1){
            break;
        }
        hash[u]=true;
        int np = chosePositionToInsert(ans,coord,u);
        ans.insert(ans.begin()+np,u);
    }
    return ans;
}
std::vector<int> computeConvexHullHeuristicCheapestInsertionTSP(std::vector<std::tuple<int,int>> coord){
    vector<int> ans = computeConvexHullGrahamScan(coord);
	int n =coord.size();
    bool hash[n];
    for(int i =0;i<n;i++)
        hash[i]=false;
    for(auto i:ans)
        hash[i]=true;
    while(true){
        tuple<int,int> unp = choseCheapestPoint(coord,ans,hash);
        int u = get<0>(unp);
        int np = get<1>(unp);
        if(u==-1){
            break;
        }
        hash[u]=true;
        ans.insert(ans.begin()+np,u);
    }
    return ans;
}
