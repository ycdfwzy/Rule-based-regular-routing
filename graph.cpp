#include "graph.h"
#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>

#define CHECK //
using namespace std;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
const int COST1=1;
const int COST2=0;


Edge Pool2[4000000*10+20];
Graph::Graph(int row, int col, int K){
	if (K <= 0){
		cout << "K must be greater than 0" << endl;
		return;
	}
	this->row = row;
	this->col = col;
	this->K = K;
	this->extra = 0;
	N = (K+1)*(row+1)+1;
	M = (K+1)*(col+1)+1;
	Pool = Pool2;
	Pool_cnt=2;
	
	n = 0;

	for (int i = 0; i < N; ++ i){			// add normal nodes
		for (int j = 0; j < M; ++ j){
			//CHECK if (i >= N/2 || j >= M/2) continue;
			Number[i][j] = n; n+=2;
		}
	}
	
	S = n;
	T = n+1;
	n += 2;
	E = new int[n];
	memset(E, 0 ,n*4);
	//cout<<"n "<<n<<endl;
	
	for (int i = 1; i <= row; ++ i){		//add internal nodes
		for (int j = 1; j <= col; ++ j){
			//((K+1)*i, (K+1)*j)
			int x = (K+1)*i, y = (K+1)*j;
			
			//CHECK if (x >= N/2 || y >= M/2) continue;
			
			int id = Number[x][y];
			//S link to internal nodes
			add_edge(S, id, 1, 0);
			//extra += (N+M)*2-min(x,y)-x-y; 
			add_edge(id, id+1, 1, COST2);
			
			for (int d = 0; d < 4; ++ d){
				//CHECK if (x+dx[d] >= N/2 || y+dy[d] >= M/2) continue;
				int id1 = Number[x+dx[d]][y+dy[d]];
				add_edge(id+1, id1, 1, COST1);
			}
		}
	}
	
	for (int i = 0; i < N; ++ i){			// add normal nodes
		for (int j = 0; j < M; ++ j){
			//CHECK if (i >= N/2 || j >= M/2) continue;
			int id = Number[i][j];
			// boundary nodes
			if (i == 0 || j == 0 || i == N-1 || j == M-1){
				add_edge(id, id+1, 1, COST2);
				add_edge(id+1, T, 1, COST2);
			} else
			// others
			if (i%(K+1) != 0 || j%(K+1) != 0){
				add_edge(id, id+1, 1, COST2);
				for (int d = 0; d < 4; ++ d){
					//CHECK if (i+dx[d] >= N/2 || j+dy[d] >= M/2) continue;
					int id1 = Number[i+dx[d]][j+dy[d]];
					add_edge(id+1, id1, 1, COST1);
				}
			}
		}
	}
}

void Graph::add_edge(int from, int to, Temp flow, Temp cost){
	static int P1,P2;
    P1 = Pool_cnt++;
	P2 = Pool_cnt++;
	Pool[P1].init(to, flow, cost, E[from]);
	Pool[P2].init(from, 0, -cost, E[to]);
	E[from] = P1; E[to] = P2;
}

Graph::~Graph(){
	delete[] E;
	delete[] Pool;
}
