#include "costflow.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
#define inf 1000000000

CostFlow::CostFlow(Graph& g):G(g){
	D.assign(G.n, 0);
	V.assign(G.n, 0);
	Q.assign(0, 0);
	times = 0;
	maxflow = 0;
	mincost = 0;
	
}

CostFlow::~CostFlow(){
	cout << "begin ~CostFlow" << endl;
	
	cout << "end ~CostFlow" << endl;
}

void CostFlow::MinCostMaxFlow(){
	do{
		times++;
		Q.assign(0, 0);
		aug(G.S, inf);
	} while (Judge());
}

bool CostFlow::Judge(){
	if (V[G.T] == times) return true;
	int delta = inf;
	for (int k = 0; k < Q.size(); ++ k){
		int i = Q[k];
	//for (int i = 0; i < G.n; ++ i)
	//if (V[i] == times){
		for (int j = 0; j < G.node[i].size(); ++j)
		if (G.flow[i][j] > 0 && V[G.node[i][j]] < times){
			delta = min(delta, D[i]-D[G.node[i][j]]+G.cost[i][j]);
		}
	}
	if (delta == inf) return false;
	//for (int i = 0; i < G.n; ++i)
		//if (V[i] == times) D[i] -= delta;
	for (int k = 0; k < Q.size(); ++ k)
		D[Q[k]] -= delta;
	return true;
}

int CostFlow::aug(int cur, int f){
	if (V[cur] < times)
		Q.push_back(cur);
	V[cur] = times;
	if (cur == G.T){
		maxflow += f;
		mincost -= D[G.S]*f;
		return f;
	}
	int ret = 0;
	for (int i = 0, nxt; i < G.node[cur].size(); ++i)
	if (G.flow[cur][i] > 0 && V[nxt=G.node[cur][i]] < times){
		if (D[cur]+G.cost[cur][i] == D[nxt]){
			int tmp = aug(nxt, min(f-ret, G.flow[cur][i]));
			G.flow[cur][i] -= tmp;
			G.flow[nxt][G.mate[cur][i]] += tmp;
			ret += tmp;
		}
	}
	return ret;
}