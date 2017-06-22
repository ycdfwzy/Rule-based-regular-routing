#ifndef COSTFLOW_H_
#define COSTFLOW_H_

#include "graph.h"
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

class CostFlow{
	public:
		CostFlow(Graph&);
		~CostFlow();
		
		int aug(int, int);
		bool Judge();
		void MinCostMaxFlow();
		
		
		Graph& G;
		vector<int> D, V, Q;
		int maxflow, mincost, times;
};

#endif
