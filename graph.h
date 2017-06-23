#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Edge{
	public:
		int y, flow, cost;
		Edge *opp, *next;
		
		Edge(){}
		Edge(int, int, int, Edge*);
		~Edge();
		inline void init(int y_, int flow_, int cost_, Edge* opp_, Edge* next_){
			y = y_;
			flow = flow_;
			cost = cost_;
			opp = opp_;
			next = next_;
		}
};

class Graph{
	public:
		Graph(int row, int col, int K);
		~Graph();
		void add_edge(int, int, int, int);
		
		int n, N, M;
		int S, T;
		int row, col, K;
		int Number[3400][3400];
		Edge** E;
};

#endif