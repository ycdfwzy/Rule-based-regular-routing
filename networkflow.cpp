#include "networkflow.h"
#include "graph.h"
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

#define inf 1000000000

static int *E;
static Edge *Er;
NetworkFlow::NetworkFlow(Graph& g) : G(g){
	id = new int[G.n];
	cnt = new int[G.n];
	Min = new int[G.n];
	d = new Edge*[G.n];
	path = new Edge*[G.n];
	memset(id, 63, sizeof(int)*G.n);
	memset(cnt, 0, sizeof(int)*G.n);
	memset(Min, 0, sizeof(int)*G.n);
	for (int i = 0; i < G.n; ++i)
		d[i] = G.E[i];
	cnt[0] = G.n;
	//level = new int[G.n];
	minx = inf;
	maxflow = 0;
	flag = false;
	E = G.E;
	Er = G.Pool;
}

NetworkFlow::~NetworkFlow(){
	delete[] id;
	delete[] d;
	delete[] cnt;
	delete[] Min;
	delete[] path;
	//delete[] level;
}

void NetworkFlow::BFS(){
	int top = 0, tail = 0;
	Q = new int[G.n];
	Q[0] = G.T; id[G.T] = 0;
	while (top <= tail){
		int x = Q[top];
		for (Edge* e = G.E[x]; e != NULL; e = e->next)
		if (e->opp->flow > 0 && id[e->y] > id[x]+1){
			Q[++tail] = e->y;
			cnt[id[e->y] = id[x]+1]++;
		}
		++top;
	}
	delete[] Q;
}
/*
int NetworkFlow::dinic_dfs(int u, int cp) {
    int tmp = cp;
    if (u == G.T) return cp;
	for 
	for (Edge* e = G.E[u]; e != NULL && tmp>0; e = e->next){
        if (level[u] + 1 == level[e->y]) {
            if (e->flow > 0) {
                int t = dinic_dfs(e->y, min(tmp, e->flow));
                e->flow -= t;
                e->opp->flow += t;
                tmp -= t;
            }
        }
    }
    return cp - tmp;
}

bool NetworkFlow::dinic_bfs(){
	Q = new int[G.n];
	memset(level, 0, sizeof(int)*G.n);
	level[Q[0]=G.S] = 1;
	int top = 0, tail = 0;
	while (top <= tail){
		int u = Q[top++];
		for (Edge *e = G.E[u]; e != NULL; e = e->next){
			if (!level[e->y] && e->flow > 0) {
				level[e->y] = level[u] + 1;
				Q[++tail] = e->y;
			}
		}
	}
	delete[] Q;
	return level[G.T] != 0;
}
*/
void NetworkFlow::MaxFlow(){
	//dinic
	/*int tmp = 0;
    while (dinic_bfs()) {
		//cout << "OK" << endl;
        while (tmp = dinic_dfs(G.S, inf))
            maxflow += tmp;
    }*/
	
	// SAP+GAP
	BFS();
	int cur = G.S;
	while (id[G.S] < G.n){
		flag = false;
		Min[cur] = minx;
		for (Edge* e = d[cur]; e != NULL; e = e->next){
			if (e->flow > 0 && id[cur] == id[e->y]+1){
				flag = true;
				d[cur] = e;
				if (e->flow < minx)
					minx = e->flow;
				path[e->y] = e->opp;
				cur = e->y;
				if (cur == G.T){
					maxflow += minx;
					while (cur != G.S){
						path[cur]->flow += minx;
						path[cur]->opp->flow -= minx;
						cur = path[cur]->y;
					}
					minx = inf;
				}
				break;
			}
		}
		if (flag == false){
			int m = G.n-1;
			Edge* k = NULL;
			for (Edge* e = G.E[cur]; e != NULL; e = e->next)
			if (e->flow > 0 && id[e->y] < m){
				m = id[e->y];
				k = e;
			}
			d[cur] = k;
			if (--cnt[id[cur]] == 0)
				break;
			id[cur] = m+1;
			++cnt[id[cur]];
			
			if (cur != G.S){
				cur = path[cur]->y;
				minx = Min[cur];
			}
			
		}
	}
}