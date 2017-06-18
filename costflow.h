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
		void MinCostMaxFlow();
		Graph& G;
};

#endif
