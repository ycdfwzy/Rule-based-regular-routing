#ifndef MAXFLOW_H_
#define MAXFLOW_H_

#include "graph.h"
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

class MaxFlow{
	public:
		MaxFlow(Graph&);
		~MaxFlow();
		
		int aug(int, int);
		bool BFS();
		bool Judge();
		void CalcMaxFlow(bool);
		bool TotalMaxFlow();
		
		
		Graph& G;
		int *H, *Ti, *Q, *S;
		bool *V, *V2;
		int maxflow, mincost, times, t;
};

#endif
