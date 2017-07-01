#include "graph.h"
#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>

#define CHECK //
using namespace std;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
const int flowcost1=1;
const int flowcost2=0;


Graph::Graph(int row, int col, int K){
	if (K < 0){
		cout << "K must be greater than 0" << endl;
		return;
	}
	this->row = row;
	this->col = col;
	this->K = K;
	this->extra = 0;
	N = (K+1)*(row+1);
	M = (K+1)*(col+1);
	Pool = new Edge[(N+1)*(M+1)*10+row*col*10];
	Pool_Cnt=10;
	
	n = 2;
	Number = new int*[N+1];
	for (int i = 0; i <= N; i++){			// add normal nodes
		Number[i] = new int[M+1];
		for (int j = 0; j <= M; j++){
			Number[i][j] = n; n+=2;
		}
	}

	S = n;
	T = n+1;
	n += 2;
	E = new int[n];
	memset(E, 0 ,n*4);
	
	for (int i = 0; i <= N; ++ i){			// add normal nodes
		for (int j = 0; j <= M; ++ j){
			int id = Number[i][j];
			//cout<<i<<" "<<j<<" "<<Pool_Cnt<<endl;
			// boundary nodes
			if (i == 0 || j == 0 || i == N || j == M){
				add_edge(id, id+1, 1, flowcost2);
				add_edge(id+1, T, 1, flowcost2);
				Pool_Cnt+=6;
			} 
			// others
			else{
				//cout<<"Step1 "<<Pool_Cnt<<endl;
				add_edge(id, id+1, 1, flowcost2);
				
				//cout<<"Step2 "<<Pool_Cnt<<endl;
				for (int d = 0; d < 4; ++ d){
					int id1 = Number[i+dx[d]][j+dy[d]];
					add_edge(id+1, id1, 1, flowcost1);
				}
				
				//cout<<"Step3 "<<Pool_Cnt<<endl;
			}
		}
	}

	for (int i = 1; i <= row; ++ i){		//add internal nodes
		for (int j = 1; j <= col; ++ j){
			//((K+1)*i, (K+1)*j)
			int x = (K+1)*i, y = (K+1)*j;
			int id = Number[x][y];
			//S link to internal nodes
			Number_inter[i][j]=Pool_Cnt;
			add_edge(S, id, 1, 0);
			//extra += (N+M)*2-min(x,y)-x-y; 
		}
	}
}

void Graph::add_edge(int from, int to, Temp flow, Temp cost){
	static int P1,P2;
    P1 = Pool_Cnt++;
	P2 = Pool_Cnt++;
	Pool[P1].init(to, flow, cost, E[from]);
	Pool[P2].init(from, 0, -cost, E[to]);
	E[from] = P1; E[to] = P2;
}

Graph::~Graph(){
	delete[] E;
	delete[] Pool;
}
