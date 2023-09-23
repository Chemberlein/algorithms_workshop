#pragma once
#include <iostream> 
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <math.h>
#include <stack>

class DSU{
	public:
		DSU(int n);
		~DSU();
		int find(int i);
		void unite(int x,int y);
	private:
		int* parent=NULL;
		int* rank=NULL;
};
