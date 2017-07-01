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
		void BFS();
		//int dinic_dfs(int, int);
		//bool dinic_bfs();
		Graph& G;
		
		int *id, *Min, *cnt, *Q, *level;
		int *d, *path;
		int minx, maxflow;
		bool flag;
};

#endif