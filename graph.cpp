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

void Edge::init(int y_, int flow_, int cost_, Edge* opp_, Edge* next_){
	y = y_;
	flow = flow_;
	cost = cost_;
	opp = opp_;
	next = next_;
}

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
	E = new Edge*[n];
	for (int i = 0; i < n; ++i)
		E[i] = NULL;
	
	//cout << node.size() << endl;
	//cout << node[0].size() << endl;
	for (int i = 1; i <= row; ++ i){		//add internal nodes
		for (int j = 1; j <= col; ++ j){
			//((K+1)*i, (K+1)*j)
			int x = (K+1)*i, y = (K+1)*j;
			//if (x > y || y+y > M) continue;
			int id = x*M+y;
			//S link to internal nodes
			add_edge(S, id, 1, 0);
			add_edge(id, id+(N*M), 1, 0);
			
			for (int d = 0; d < 4; ++ d){
				int id1 = (x+dx[d])*M+y+dy[d];
				add_edge(id+(N*M), id1, 1, 1);
			}
		}
	}
	
	for (int i = 0; i < N; ++ i){			// add normal nodes
		for (int j = 0; j < M; ++ j){
			//if (i > j || j+j > M) continue;
			int id = i*M+j;
			// boundary nodes
			if (i == 0 || j == 0 || i == N-1 || j == M-1){
				add_edge(id, id+(N*M), 1, 0);
				add_edge(id+(N*M), T, 1, 0);
			} else
			// others
			if (i%(K+1) != 0 || j%(K+1) != 0){
				add_edge(id, id+(N*M), 1, 0);
				for (int d = 0; d < 4; ++ d){
					int id1 = (i+dx[d])*M+j+dy[d];
					add_edge(id+(N*M), id1, 1, 1);
				}
			}
		}
	}
	
	
	
}

void Graph::add_edge(int x, int y, int f, int c){
	/*node[x].push_back(y);
	node[y].push_back(x);
	mate[x].push_back(node[y].size()-1);
	mate[y].push_back(node[x].size()-1);
	flow[x].push_back(f);
	flow[y].push_back(0);
	cost[x].push_back(c);
	cost[y].push_back(-c);*/
	Edge *t1 = new Edge(), *t2 = new Edge();
	t1->init(y, f, c, t2, E[x]);
	t2->init(x, 0, -c, t1, E[y]);
	E[x] = t1; E[y] = t2;
}

Graph::~Graph(){
	//cout << "begin ~Graph" << endl;
	/*for (int i = 0; i < n; i++)
	{
		node[i].assign(0, 0);
		mate[i].assign(0, 0);
		flow[i].assign(0, 0);
		cost[i].assign(0, 0);
	}
	node.assign(0, vector<int>(0));
	mate.assign(0, vector<int>(0));
	flow.assign(0, vector<int>(0));
	cost.assign(0, vector<int>(0));*/
	//cout << "end ~Graph" << endl;
	delete[] E;
}