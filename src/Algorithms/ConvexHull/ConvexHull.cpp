#include "ConvexHull.h"
#include <vector>
#include <tuple>
#include <stack>
#include <iostream>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <cstdlib>
#include <ctime>
#include <map>
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
	if (n<=3){
		if(n==1)return{0};
        else if(n==2)return{0,1,0};
        else if(n==3){
        	if(orentation(0,1,2,coord)==1)
        		return{0,1,2,0};
        	else
        		return{0,2,1,0};
        }
		return {};
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

// Finding most left and most right point if there multiple wichuse one with lowest y
tuple<int,int> findeMostLeftMostRightPoints(vector<tuple<int,int>> coord){
	int min=0,max =0;
	for(int i =0;i<coord.size();i++){
		if(get<0>(coord[i])<get<0>(coord[min]))
			min = i;
		else if(get<0>(coord[i])==get<0>(coord[min]))
			min = (get<1>(coord[i])<get<1>(coord[min]))?i:min;
		if(get<0>(coord[i])>get<0>(coord[max]))
			max = i;
		else if(get<0>(coord[i])==get<0>(coord[max]))
			max = (get<1>(coord[i])<get<1>(coord[max]))?i:max;
	}
	return make_tuple(min,max);
}

vector<tuple<int,int,int>> selectPointRalativeToLine(tuple<int,int> a,tuple<int,int> b,int o, vector<tuple<int,int,int>> m){
	vector<tuple<int,int,int>> res;
	for(int i =0;i<m.size();i++){
		tuple<int,int> c = make_tuple(get<1>(m[i]),get<2>(m[i]));
		if(orentation(a,b,c)==o){
			res.push_back(m[i]);
		}
	}
	return res;
}

tuple<int,int,int> selectFarestPointFromTheLine(vector<tuple<int,int,int>> m,tuple<int,int,int> a,tuple<int,int,int> b){
	int fid = -1;
	float s = 0;
	int xa = get<1>(a);
	int xb = get<1>(b);
	int ya = get<2>(a);
	int yb = get<2>(b);
	for(int i =0;i<m.size();i++){
		tuple<int,int,int> np = m[i];
		int xp = get<1>(m[i]),yp = get<2>(m[i]);
		float ns = 0.5*(abs(xa*(yb-yp)+xb*(yp-ya)+xp*(ya-yb)));
		if(fid==-1||s<ns)
			fid=i,s=ns;
	}
	return m[fid];
}

vector<int> QuickhullRec(vector<tuple<int,int,int>> vt,int o,tuple<int,int,int> a,tuple<int,int,int> b){
	if(vt.size()<1)
		return {};
	vector<int> ans;
	tuple<int,int,int> p = selectFarestPointFromTheLine(vt,a,b);
	vector<tuple<int,int,int>> n = selectPointRalativeToLine(make_tuple(get<1>(a),get<2>(a)),make_tuple(get<1>(p),get<2>(p)),o,vt);
	vector<int> tmp = QuickhullRec(n,o,a,p);
	ans.insert(ans.end(),tmp.begin(),tmp.end());
	ans.push_back(get<0>(p));
	n=selectPointRalativeToLine(make_tuple(get<1>(p),get<2>(p)),make_tuple(get<1>(b),get<2>(b)),o,vt);
	tmp = QuickhullRec(n,o,p,b);
	ans.insert(ans.end(),tmp.begin(),tmp.end());
	return ans;
}

vector<int> computeConvexHullQuickhull(vector<tuple<int,int>> coord){
	vector<int> ans;
	vector<tuple<int,int,int>> m;
	for(int i =0;i<coord.size();i++){
		m.push_back(make_tuple(i,get<0>(coord[i]),get<1>(coord[i])));
	}
	tuple<int,int> min_max = findeMostLeftMostRightPoints(coord);
	ans.push_back(get<0>(min_max));
	vector<tuple<int,int,int>> n = selectPointRalativeToLine(coord[get<0>(min_max)],coord[get<1>(min_max)],1,m);
	vector<int> tmp = QuickhullRec(n,1,m[get<0>(min_max)],m[get<1>(min_max)]);
	ans.insert(ans.end(),tmp.begin(),tmp.end());
	ans.push_back(get<1>(min_max));
	n = selectPointRalativeToLine(coord[get<0>(min_max)],coord[get<1>(min_max)],2,m);
	tmp = QuickhullRec(n,2,m[get<0>(min_max)],m[get<1>(min_max)]);
	for(int i = tmp.size()-1;i>=0;i--)
		ans.push_back(tmp[i]);
	ans.push_back(get<0>(min_max));
	return ans;
}

// DEQ

// Todo probably replace this function somwhere else 
int getRandInt(int min, int max){
	srand(time(nullptr)); 
	return min+(rand()%(max-min));
}

float getMeanX(vector<tuple<int,int>> coord){
	float s = 0;
	for (auto i :coord){
		s+=get<0>(i);
	}
	return s/coord.size();
}

tuple<vector<tuple<int,int>>,vector<tuple<int,int>>,map<int,int>,map<int,int>> divideCoordinates(vector<tuple<int,int>> coord){
	vector<tuple<int,int>> lp,rp;
	map<int,int> mlp,mrp;
	float meanX = getMeanX(coord);
	for(int o = 0;o<coord.size();o++){
		if(get<0>(coord[o])<meanX || (get<0>(coord[o])==meanX && getRandInt(0,1))){
			lp.push_back(coord[o]);
			mlp[lp.size()-1] = o;
		}else{
			rp.push_back(coord[o]);
			mrp[rp.size()-1] = o;
		}
	}	
	return make_tuple(lp,rp,mlp,mrp);
}

vector<int> Conqure(vector<int> lp, vector<int> rp,vector<tuple<int,int>> coord){
	//find max x left part
	int p = 0;
	for(int i = 0;i<lp.size();i++){
		if(coord[lp[p]]<coord[lp[i]])
			p=i;
	}
	//find min x right part 
	int q = 0;
	for(int i = 0;i<rp.size();i++){
		if(coord[rp[q]]>coord[rp[i]])
			q=i;
	}
	int cp_p = p,cp_q = q;
	int prev_p,prev_q,o;
	while(true){
		prev_p=p;
		prev_q=q;
		if(rp.size()>1){
			o = orentation(lp[p],rp[q],rp[(rp.size()+q-1)%rp.size()],coord); 
			while (o==1){
				q=(rp.size()+q-1)%rp.size();
				o = orentation(lp[p],rp[q],rp[(rp.size()+q-1)%rp.size()],coord); 
			}
		}
		if(lp.size()>1){
			o = orentation(rp[q],lp[p],lp[(lp.size()+p+1)%lp.size()],coord); 
			while (o==2){
				p=(lp.size()+p+1)%lp.size();
				o = orentation(rp[q],lp[p],lp[(lp.size()+p+1)%lp.size()],coord); 
			}
		}
		if(prev_p==p && prev_q==q)
			break;
	};

	while(true){
		prev_p=cp_p;
		prev_q=cp_q;
		if(rp.size()>1){
			o = orentation(lp[cp_p],rp[cp_q],rp[(rp.size()+cp_q+1)%rp.size()],coord); 
			while (o==2){
				cp_q=(rp.size()+cp_q+1)%rp.size();
				o = orentation(lp[cp_p],rp[cp_q],rp[(rp.size()+cp_q+1)%rp.size()],coord);
			}
		}
		if(lp.size()>1){
			o = orentation(rp[cp_q],lp[cp_p],lp[(lp.size()+cp_p-1)%lp.size()],coord); 
			while (o == 1){
				cp_p=(lp.size()+cp_p-1)%lp.size();
				o = orentation(rp[cp_q],lp[cp_p],lp[(lp.size()+cp_p-1)%lp.size()],coord);
			}
		}
		if(prev_p==cp_p && prev_q==cp_q)
			break;	
	};
	vector<int> ans;
	while(p!=cp_p){
		ans.push_back(lp[p]);
		p=(lp.size()+p+1)%lp.size(); 
	}
	ans.push_back(lp[cp_p]);
	while(q!=cp_q){
		ans.push_back(rp[cp_q]);	 
		cp_q=(rp.size()+cp_q+1)%rp.size();
	}
	ans.push_back(rp[cp_q]);
	return ans;
}


vector<int> ConvertBack(map<int,int> m,vector<int> init){
	vector<int> result;
	for(auto o:init){
		result.push_back(m[o]);
	}
	return result;
}


vector<int> DAQRec(vector<tuple<int,int>> coord){
	vector<int> ans;
	if(coord.size()<10){
		ans =  computeConvexHullGrahamScan(coord);
		if(ans.size()>0)
			ans.erase(ans.end()-1);
		return ans;
	}
	tuple<vector<tuple<int,int>>,vector<tuple<int,int>>,map<int,int>,map<int,int>> d = divideCoordinates(coord);
	vector<int> lpa = DAQRec((get<0>(d)));
	lpa = ConvertBack((get<2>(d)),(lpa));
	vector<int> rpa = DAQRec((get<1>(d)));
	rpa = ConvertBack((get<3>(d)),rpa);
	if(lpa.size()==0)
		return rpa;
	else if(rpa.size()==0)
		return lpa;
	ans = Conqure(lpa,rpa,coord);
	return ans;
}


vector<int> computeConvexHullDivideAndConqure(vector<tuple<int,int>> coord){
	vector<int> ans;
	tuple<vector<tuple<int,int>>,vector<tuple<int,int>>,map<int,int>,map<int,int>> d = divideCoordinates(coord);
	vector<int> lpa = DAQRec((get<0>(d)));
	lpa = ConvertBack((get<2>(d)),(lpa));
	vector<int> rpa = DAQRec((get<1>(d)));
	rpa = ConvertBack((get<3>(d)),rpa);
	if(lpa.size()==0){
		rpa.push_back(rpa[0]);
		return rpa;
	}else if(rpa.size()==0){
		lpa.push_back(lpa[0]);
		return lpa;
	}
	ans = Conqure(lpa,rpa,coord);
	ans.push_back(ans[0]);
	return ans;
}
