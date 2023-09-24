#include "ConvexHull.h"
#include <vector>
#include <tuple>
#include <stack>
#include <iostream>
#include <algorithm>

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

int findMostBottomLeftPoint(vector<tuple<int,int>> coord){
	int ans = -1;
	for(int i =0;i<coord.size();i++){
		if(ans == -1 || get<1>(coord[ans])>get<1>(coord[i])||(get<1>(coord[ans])==get<1>(coord[i])&&(get<0>(coord[ans])>(get<0>(coord[i]))))){
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

int orentation(tuple<int,int> p,tuple<int,int> q,tuple<int,int> i){
	int val  = (get<1>(q)-get<1>(p))*(get<0>(i)-get<0>(q)) - (get<0>(q)-get<0>(p))*(get<1>(i)-get<1>(q));
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
int distanceSQ(tuple<int,int> a,tuple<int,int> b){
    return pow(get<0>(a)-get<0>(b),2)+pow(get<1>(a)-get<1>(b),2);
}
bool  comparePointGS(tuple<int,int> p,tuple<int,int> q,tuple<int,int> i){
    int o = orentation(p,q,i);
    if(o==0){
        return (distanceSQ(p,i)>=distanceSQ(p,q))?false:true;
    }
    return (o==2)?false:true;
}

int nextToTop(stack<int> s){
    int o = s.top();
    s.pop();
    int t = s.top();
    s.push(o);
    return t;
}
vector<int> computeConvexHullGrahamScan(vector<tuple<int,int>> coord){
	int n = coord.size();
	if (n<3){
		if(n==1)return{0};
        else if(n==2)return{0,1,0};
        else if(n==1)return{0,1,2,0};
		return {-1};
	}
	vector<int> ans;
	int bl = findMostBottomLeftPoint(coord);
    tuple<int,int> itc=coord[bl];
    ans.push_back(bl);
    vector<int> hash;
    for(int i =0;i<n;i++){
        hash.push_back(i);
    }
    hash[0]=bl;
    hash[bl]=0;
	sort(hash.begin()+1,hash.end(),[itc,coord](int a,int b){return !comparePointGS(itc,coord[a],coord[b]);});
    int m =1;
    for(int i =1;i<n;i++){
        while(i<n-1 && orentation(coord[hash[0]],coord[hash[i]],coord[hash[i+1]])==0){
            i++;
        }
        hash[m]=hash[i];
        m++;
    }
    stack<int> s;
    s.push(hash[0]);
    s.push(hash[1]);
    s.push(hash[2]);
    for(int i =3;i<m;i++){
        while(s.size()>1 && orentation(nextToTop(s),s.top(),hash[i],coord)!=2)
            s.pop();
        s.push(hash[i]);
    }
    while(!s.empty()){
        ans.push_back(s.top());
        s.pop();
    }
    return ans;
}
