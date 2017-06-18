#include "graph.h"
#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

Graph::Graph(int row, int col, int K){
	if (K <= 0){
		cout << "K must be greater than 0" << endl;
		return;
	}
	this->row = row;
	this->col = col;
	this->K = K;
	N = (K+1)*(row+1)+1;
	M = (K+1)*(col+1)+1;
	n = N*M*2+2;
	S = N*M*2;
	T = N*M*2+1;
	node.assign(n, vector<int>(0));
	mate.assign(n, vector<int>(0));
	flow.assign(n, vector<int>(0));
	cost.assign(n, vector<int>(0));
	
	for (int i = 1; i <= row; ++ i){		//add internal nodes
		for (int j = 1; j <= col; ++ j){
			//((K+1)*i, (K+1)*j)
			int x = (K+1)*i, y = (K+1)*j;
			int id = x*M+y;
			//S link to internal nodes
			add_edge(S, id, 1, 1);
			
			for (int d = 0; d < 4; ++ d){
				int id1 = (x+dx[d])*M+y+dy[d];
				add_edge(id, id1, 1, 1);
			}
		}
	}
	
	for (int i = 0; i < N; ++ i){			// add normal nodes
		for (int j = 0; j < M; ++ j){
			int id = i*M+j;
			// boundary nodes
			if (i == 0 || j == 0 || i == N-1 || j == M-1){
				add_edge(id, T, 1, 1);
			} else
			// others
			if (i%(K+1) != 0 || j%(K+1) != 0){
				add_edge(id, id+(N*M), 1, 0);
				for (int d = 0; d < 4; ++ d){
					if ((i+dx[d])%(K+1) == 0 && (j+dy[d])%(K+1) == 0)
						continue;
					int id1 = (i+dx[d])*M+j+dy[d];
					add_edge(id+(N*M), id1, 1, 1);
				}
			}
		}
	}
	
}

void Graph::add_edge(int x, int y, int f, int c){
	node[x].push_back(y);
	node[y].push_back(x);
	mate[x].push_back(node[y].size()-1);
	mate[y].push_back(node[x].size()-1);
	flow[x].push_back(f);
	flow[y].push_back(0);
	cost[x].push_back(c);
	cost[y].push_back(-c);
}

Graph::~Graph(){
	node.assign(0, vector<int>(0));
	mate.assign(0, vector<int>(0));
	flow.assign(0, vector<int>(0));
	cost.assign(0, vector<int>(0));
}