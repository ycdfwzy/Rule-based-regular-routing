#include "networkflow.h"
#include "graph.h"
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

#define inf 1000000000;

NetworkFlow::NetworkFlow(Graph& g) : G(g){
	id.assign(G.n, 0);
	d.assign(G.n, 0);
	cnt.assign(G.n, 0);
	Min.assign(G.n, 0);
	path.assign(G.n, 0);
	cnt[0] = G.n;
	minx = inf;
	maxflow = 0;
	flag = false;
}

NetworkFlow::~NetworkFlow(){
	cout << "begin ~NetworkFlow" << endl;
	/*id.assign(0, 0);
	d.assign(0, 0);
	cnt.assign(0, 0);
	Min.assign(0, 0);
	path.assign(0, 0);*/
	cout << "end ~NetworkFlow" << endl;
}

void NetworkFlow::MaxFlow(){	// SAP+GAP
	int cur = G.S;
	while (cnt[G.S] < G.n){
		flag = false;
		Min[cur] = minx;
		for (int i = d[cur]; i < G.node[cur].size(); ++i){
			if (G.flow[cur][i] > 0 && id[cur] == id[G.node[cur][i]]+1){
				flag = true;
				d[cur] = i;
				if (G.flow[cur][i] < minx)
					minx = G.flow[cur][i];
				path[G.node[cur][i]] = G.mate[cur][i];
				cur = G.node[cur][i];
				if (cur == G.T){
					maxflow += minx;
					//cout << maxflow << endl;
					while (cur != G.S){
						int pre = G.node[cur][path[cur]];
						G.flow[cur][path[cur]] += minx;
						G.flow[pre][G.mate[cur][path[cur]]] -= minx;
						cur = pre;
					}
					//cout << maxflow << endl;
					minx = inf;
				}
				break;
			}
		}
		if (flag == false){
			int m = G.n-1, k = G.node[cur].size();
			for (int i = 0; i < G.node[cur].size(); ++i){
				if (G.flow[cur][i] > 0 && id[G.node[cur][i]] < m){
					m = id[G.node[cur][i]];
					k = i;
				}
			}
			d[cur] = k;
			if (--cnt[id[cur]] == 0)
				break;
			id[cur] = m+1;
			++cnt[id[cur]];
			
			if (cur != G.S){
				cur = G.node[cur][path[cur]];
				minx = Min[cur];
			}
			
		}
	}
}