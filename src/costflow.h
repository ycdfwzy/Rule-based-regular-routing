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
		void BFS();
		void SPFA();
		bool Judge();
		void MinCostMaxFlow();
		void PartMinCostMaxFlow();
		bool TotalMinCostMaxFlow();
		
		
		Graph& G;
		int *H, *Ti, *Q, *S;
		bool *V, *V2;
		int maxflow, mincost, times, t;
};

#endif
