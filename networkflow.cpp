#include "networkflow.h"
#include "graph.h"
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

#define inf 1000000000;

NetworkFlow::NetworkFlow(Graph& g) : G(g){
	/*id.assign(G.n, 0);
	d.assign(G.n, 0);
	cnt.assign(G.n, 0);
	Min.assign(G.n, 0);
	path.assign(G.n, 0);*/
	id = new int[G.n];
	cnt = new int[G.n];
	Min = new int[G.n];
	d = new Edge*[G.n];
	path = new Edge*[G.n];
	memset(id, 0, sizeof(int)*G.n);
	memset(cnt, 0, sizeof(int)*G.n);
	memset(Min, 0, sizeof(int)*G.n);
	for (int i = 0; i < G.n; ++i)
		d[i] = G.E[i];
	//memset(path, 0, sizeof(int)*G.n);
	cnt[0] = G.n;
	minx = inf;
	maxflow = 0;
	flag = false;
}

NetworkFlow::~NetworkFlow(){
	//cout << "begin ~NetworkFlow" << endl;
	/*id.assign(0, 0);
	d.assign(0, 0);
	cnt.assign(0, 0);
	Min.assign(0, 0);
	path.assign(0, 0);*/
	//cout << "end ~NetworkFlow" << endl;
	delete[] id;
	delete[] d;
	delete[] cnt;
	delete[] Min;
	delete[] path;
}

void NetworkFlow::MaxFlow(){	// SAP+GAP
	int cur = G.S;
	while (cnt[G.S] < G.n){
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
					//cout << maxflow << endl;
					while (cur != G.S){
						path[cur]->flow += minx;
						path[cur]->opp->flow -= minx;
						cur = path[cur]->y;
					}
					//cout << maxflow << endl;
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