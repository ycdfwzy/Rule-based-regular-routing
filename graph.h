#ifndef GRAPH_H_
#define GRAPH_H_

#define Temp short
#define Maxn 2000

#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Edge{
	public:
		int to, next;
		Temp flow, cost;
		
		Edge(){}
		~Edge(){}
		inline void init(int to_, Temp flow_, Temp cost_, int next_){
			to = to_;
			flow = flow_;
			cost = cost_;
			next = next_;
		}
};

class Graph{
	public:
		Graph(int row, int col, int K);
		~Graph();
		void add_edge(int, int, Temp, Temp);
		
		int n, N, M;
		int S, T;
		int row, col, K,extra;
		int Number[Maxn][Maxn];
		int* E;
		Edge* Pool;int Pool_cnt;

};

#endif
