#include <iostream>
#include <vector>
#include <tuple>
#include <math.h>
#include <algorithm>
#include "InsertionHeuristicTSP.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int chosePositionToInsert(vector<int> cycle,vector<tuple<int,int>> coord,int k){
    int pos = -1;
    int min_cost = -1;
    for(int i =0;i<cycle.size()-1;i++){
        int xi,xj,xk,yi,yj,yk;
        xi = get<0>(coord[cycle[i]]);
        yi = get<1>(coord[cycle[i]]);
        xj = get<0>(coord[cycle[i+1]]);
        yj = get<1>(coord[cycle[i+1]]);
        xk = get<0>(coord[k]);
        yk = get<1>(coord[k]);
        int tmpcost = sqrt(pow(xi-xk,2)+pow(yi-yk,2)) + sqrt(pow(xj-xk,2)+pow(yj-yk,2))- sqrt(pow(xi-xj,2)+pow(yi-yj,2));
        if(min_cost==-1 || min_cost>tmpcost){
            min_cost = tmpcost;
            pos = i+1;
        }
    }
    return pos;
}
int choseNearestPoint(vector<tuple<int,int,int>> dist,bool hash[]){
    for(auto i:dist){
        if(hash[get<0>(i)]==true && hash[get<1>(i)]==false)
            return get<1>(i);
        if(hash[get<1>(i)]==true && hash[get<0>(i)]==false)
            return get<0>(i);
        //cout<<get<0>(i)<<" "<<hash[get<0>(i)]<<" "<<get<1>(i)<<" "<<hash[get<1>(i)]<<".\n";
    }
    return -1;
}
vector<int> computeNearestInsertionHeuristicTSP(vector<tuple<int,int>> coord){
    vector<int> ans;
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
    ans.push_back(0);
    ans.push_back(0);
    hash[0]=true;
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
int choseRandomPoint(bool hash[],int n){
    srand(time(nullptr));
    int u = rand()%n;
    while(hash[u]==true){
        u = rand()%n;
    }
    return u;
}
vector<int> computeRandomInsertionHeuristicTSP(vector<tuple<int,int>> coord){
    vector<int> ans;
    int n =coord.size();
    bool hash[n];
    for(int i =0;i<n;i++)
        hash[i]=false;
    ans.push_back(0);
    ans.push_back(0);
    hash[0]=true;
    int k = 1;
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

tuple<int,int> choseCheapestPoint(vector<tuple<int,int>> coord,vector<int> cycle,bool hash[]){
    int u=-1;
    int pos=-1;
    int min_cost = -1;
    int xi,xj,xk,yi,yj,yk;
    for(int i=0;i<cycle.size()-1;i++){
        for(int j =0;j<coord.size();j++){
            if(hash[j]==false){
                xi = get<0>(coord[cycle[i]]);
                yi = get<1>(coord[cycle[i]]);
                xj = get<0>(coord[cycle[i+1]]);
                yj = get<1>(coord[cycle[i+1]]);
                xk = get<0>(coord[j]);
                yk = get<1>(coord[j]); 
                int tmpcost = sqrt(pow(xi-xk,2)+pow(yi-yk,2)) + sqrt(pow(xj-xk,2)+pow(yj-yk,2))- sqrt(pow(xi-xj,2)+pow(yi-yj,2));
                if (min_cost==-1 || min_cost>tmpcost){
                    u=j;
                    pos=i+1;
                    min_cost=tmpcost;
                }
            }
        }
    }
    return make_tuple(u,pos);
}

vector<int> computeCheapestInsertionHeuristicTSP(vector<tuple<int,int>> coord){
    vector<int> ans;
    int n =coord.size();
    bool hash[n];
    for(int i =0;i<n;i++)
        hash[i]=false;
    ans.push_back(0);
    ans.push_back(0);
    hash[0]=true;
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

int choseFarthestPoint(vector<tuple<int,int,int>> dist,bool hash[]){
    for(auto i:dist){
        if(hash[get<0>(i)]==true && hash[get<1>(i)]==false)
            return get<1>(i);
        if(hash[get<1>(i)]==true && hash[get<0>(i)]==false)
            return get<0>(i);
    }
    return -1;
}

vector<int> computeFarthestInsertionHeuristicTSP(vector<tuple<int,int>> coord){
    vector<int> ans;
    vector<tuple<int,int,int>> distances;
    for(int i=0;i<coord.size();i++){
        for(int j=i+1;j<coord.size();j++){
            distances.push_back(make_tuple(i,j,sqrt(pow(get<0>(coord[i])-get<0>(coord[j]),2)+pow(get<1>(coord[i])-get<1>(coord[j]),2))));
        }
    }
    sort(distances.begin(),distances.end(),[](tuple<int,int,int> a,tuple<int,int,int> b){return get<2>(a)>get<2>(b);});
    int n =coord.size();
    bool hash[n];
    for(int i =0;i<n;i++)
        hash[i]=false;
    ans.push_back(0);
    ans.push_back(0);
    hash[0]=true;
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