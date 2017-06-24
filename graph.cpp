#include "graph.h"
#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

Edge::Edge(int y_, int flow_, int cost_, Edge* opp_){
	y = y_;
	flow = flow_;
	cost = cost_;
	opp = opp_;
	next = NULL;
}

Edge::~Edge(){}
/*
void Edge::init(int y_, int flow_, int cost_, Edge* opp_, Edge* next_){
	y = y_;
	flow = flow_;
	cost = cost_;
	opp = opp_;
	next = next_;
}
*/
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
	
	n = 0;
	for (int i = 0; i < N; ++ i){			// add normal nodes
		for (int j = 0; j < M; ++ j){
			//if (i+i > N || j+j > M) continue;
			Number[i][j] = n; n+=2;
		}
	}
	Er = new Edge[n*6];
	s = 0;
	S = n;
	T = n+1;
	n += 2;
	E = new Edge*[n];
	for (int i = 0; i < n; ++i)
		E[i] = NULL;
	
	//cout << node.size() << endl;
	//cout << node[0].size() << endl;
	for (int i = 1; i <= row; ++ i){		//add internal nodes
		for (int j = 1; j <= col; ++ j){
			//((K+1)*i, (K+1)*j)
			int x = (K+1)*i, y = (K+1)*j;
			
			//if (x+x > N || y+y > M) continue;
			
			int id = Number[x][y];
			//S link to internal nodes
			add_edge(S, id, 1, 0);
			add_edge(id, id+1, 1, 0);
			
			for (int d = 0; d < 4; ++ d){
				//if (x+x+dx[d]+dx[d] > N || y+y+dy[d]+dy[d] > M)
					//continue;
				int id1 = Number[x+dx[d]][y+dy[d]];
				add_edge(id+1, id1, 1, 1);
			}
		}
	}
	
	for (int i = 0; i < N; ++ i){			// add normal nodes
		for (int j = 0; j < M; ++ j){
			//if (i+i > N || j+j > M) continue;
			int id = Number[i][j];
			// boundary nodes
			if (i == 0 || j == 0 || i == N-1 || j == M-1){
				add_edge(id, id+1, 1, 0);
				add_edge(id+1, T, 1, 0);
			} else
			// others
			if (i%(K+1) != 0 || j%(K+1) != 0){
				add_edge(id, id+1, 1, 0);
				for (int d = 0; d < 4; ++ d){
					//if (i+i+dx[d]+dx[d] > N || j+j+dy[d]+dy[d] > M)
						//continue;
					int id1 = Number[i+dx[d]][j+dy[d]];
					add_edge(id+1, id1, 1, 1);
				}
			}
		}
	}
}

void Graph::add_edge(int x, int y, int f, int c){
	Edge *t1 = &Er[s++], *t2 = &Er[s++];
	t1->init(y, f, c, t2, E[x]);
	t2->init(x, 0, -c, t1, E[y]);
	E[x] = t1; E[y] = t2;
}

Graph::~Graph(){
	delete[] Er;
	//for (int i = 0; i < n; i++)
	//	delete E[i];
	//delete[] E;
}