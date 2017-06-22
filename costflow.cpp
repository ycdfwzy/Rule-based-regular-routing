#include "costflow.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
#define inf 1000000000

CostFlow::CostFlow(Graph& g):G(g){
	/*D.assign(G.n, 0);
	V.assign(G.n, 0);
	Q.assign(0, 0);*/
	D = new int[G.n];
	V = new int[G.n];
	Q = new int[G.n];
	memset(D, 0, sizeof(int)*G.n);
	memset(V, 0, sizeof(int)*G.n);
	times = 0;
	maxflow = 0;
	mincost = 0;
	t = 0;
}

CostFlow::~CostFlow(){
	//cout << "begin ~CostFlow" << endl;
	//D.assign(0, 0);
	//V.assign(0, 0);
	//Q.assign(0, 0);
	//cout << "end ~CostFlow" << endl;
	delete[] D;
	delete[] V;
	delete[] Q;
}

void CostFlow::MinCostMaxFlow(){
	do{
		times++; t = 0;
		aug(G.S, inf);
	} while (Judge());
}

bool CostFlow::Judge(){
	if (V[G.T] == times) return true;
	int delta = inf;
	for (int k = 0; k < t; ++ k){
		int i = Q[k];
		for (Edge* e = G.E[i]; e != NULL; e = e->next)
		//for (int j = 0; j < G.node[i].size(); ++j)
		if (e->flow > 0 && V[e->y] < times){
			delta = min(delta, D[i]-D[e->y]+e->cost);
		}
	}
	if (delta == inf) return false;
	//for (int i = 0; i < G.n; ++i)
		//if (V[i] == times) D[i] -= delta;
	for (int k = 0; k < t; ++ k)
		D[Q[k]] -= delta;
	return true;
}

int CostFlow::aug(int cur, int f){
	if (V[cur] < times) Q[t++] = cur;
	V[cur] = times;
	if (cur == G.T){
		maxflow += f;
		mincost -= D[G.S]*f;
		return f;
	}
	int ret = 0;
	for (Edge* e = G.E[cur]; e != NULL; e = e->next)
	if (e->flow > 0 && V[e->y] < times && D[cur]+e->cost == D[e->y]){
		int tmp = aug(e->y, min(f-ret, e->flow));
		e->flow -= tmp;
		e->opp->flow += tmp;
		ret += tmp;
	}
	return ret;
}