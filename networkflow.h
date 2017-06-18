#ifndef NETWORKFLOW_H_
#define NETWORKFLOW_H_

#include "graph.h"
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

class NetworkFlow{
	public:
		NetworkFlow(Graph&);
		~NetworkFlow();
		void MaxFlow();
		Graph& G;
		
		vector<int> id, d, Min, cnt, path;
		int minx, maxflow;
		bool flag;
};

#endif