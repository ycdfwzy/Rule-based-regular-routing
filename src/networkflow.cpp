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
inline int Opposite(int x){return x^1;}
NetworkFlow::NetworkFlow(Graph& g) : G(g){
	E = G.E;
	Er = G.Pool;
	id = new int[G.n];
	cnt = new int[G.n];
	Min = new int[G.n];
	d = new int[G.n];
	path = new int[G.n];
	memset(id, 63, sizeof(int)*G.n);
	memset(cnt, 0, sizeof(int)*G.n);
	memset(Min, 0, sizeof(int)*G.n);
	for (int i = 0; i < G.n; ++i)
		d[i] = E[i];
	cnt[0] = G.n;
	//level = new int[G.n];
	minx = inf;
	maxflow = 0;
	flag = false;
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
		for(int P=E[x]; P; P=Er[P].next)
		//for (Edge* e = G.E[x]; e != NULL; e = e->next)
		//if (e->opp->flow > 0 && id[e->y] > id[x]+1){
		if (Er[Opposite(P)].flow && id[Er[P].to] > id[x]+1){
			Q[++tail] = Er[P].to;
			cnt[id[Er[P].to] = id[x]+1]++;
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
		for (int P = d[cur]; P; P = Er[P].next){
		//for (Edge* e = d[cur]; e != NULL; e = e->next){
			//if (e->flow > 0 && id[cur] == id[e->y]+1){
			if (Er[P].flow && id[cur] == id[Er[P].to]+1){
				flag = true;
				d[cur] = P;
				if (Er[P].flow < minx)
					minx = Er[P].flow;
				path[Er[P].to] = Opposite(P);
				cur = Er[P].to;
				if (cur == G.T){
					maxflow += minx;
					while (cur != G.S){
						Er[path[cur]].flow += minx;
						Er[Opposite(path[cur])].flow -= minx;
						cur = Er[path[cur]].to;
					}
					minx = inf;
				}
				break;
			}
		}
		if (flag == false){
			int m = G.n-1;
			int k = 0;
			for (int P = E[cur]; P; P = Er[P].next)
			//for (Edge* e = G.E[cur]; e != NULL; e = e->next)
			if (Er[P].flow > 0 && id[Er[P].to] < m){
				m = id[Er[P].to];
				k = P;
			}
			d[cur] = k;
			if (--cnt[id[cur]] == 0)
				break;
			id[cur] = m+1;
			++cnt[id[cur]];
			
			if (cur != G.S){
				cur = Er[path[cur]].to;
				minx = Min[cur];
			}
			
		}
	}
}