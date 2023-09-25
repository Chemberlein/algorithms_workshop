#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <math.h>
#include <stack>
std::vector<int> computeNearestNeighborTSP(std::vector<std::tuple<int,int>> coord){
	int sp = 0;
	int hash[coord.size()] = {};
	hash[0]=1;	
	std::vector<int> ans={sp};
	while(ans.size()<coord.size()){
		int ch = -1;
		sp = ans.back();
		hash[sp]=1;
		for(int i = 0;i<coord.size();i++){
			if(hash[i]==0){
				if(ch==-1){
					ch = i;
				}else if(std::sqrt(pow(std::get<0>(coord[i])-std::get<0>(coord[sp]),2)+pow(std::get<1>(coord[i])-std::get<1>(coord[sp]),2))<std::sqrt(pow(std::get<0>(coord[ch])-std::get<0>(coord[sp]),2)+pow(std::get<1>(coord[ch])-std::get<1>(coord[sp]),2))){
					ch=i;
				}
			}
		}
		ans.push_back(ch);
	}
	ans.push_back(0);

	return ans;
}

