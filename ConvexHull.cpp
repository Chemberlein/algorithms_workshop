#include "ConvexHull.h"
#include <vector>
#include <tuple>

using namespace std;
int findLeftMostPoint(vector<tuple<int,int>> coord){
	int ans = -1;
	for(int i =0;i<coord.size();i++){
		if(ans == -1 || get<0>(coord[ans])>get<0>(coord[i])){
			ans = i;
		}
	}
	return ans;
}

int orentation(int p,int q,int i,vector<tuple<int,int>> coord){
	int val  = (get<1>(coord[q])-get<1>(coord[p]))*(get<0>(coord[i])-get<0>(coord[q])) - (get<0>(coord[q])-get<0>(coord[p]))*(get<1>(coord[i])-get<1>(coord[q]));
	if (val ==0)return 0;
	return (val>0)?1:2;
}

vector<int> computeConvexHullJarvis(vector<tuple<int,int>> coord){
	int n = coord.size();
	if (n<3){
		if(n==1)return{0};
        else if(n==2)return{0,1,0};
        else if(n==1)return{0,1,2,0};
		return {-1};
	}
	vector<int> ans;
	int l = findLeftMostPoint(coord);
	int p = l,q;
	do{
		ans.push_back(p);
		q=(p+1)%n;
		for(int i=0;i<n;i++){
			if(orentation(p,q,i,coord)==2)
				q=i;
		}
		p=q;
	}while(p!=l);
    ans.push_back(l);
	return ans;
}
