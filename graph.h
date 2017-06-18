#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Graph{
	public:
		Graph(int row, int col, int K);
		~Graph();
		void add_edge(int, int, int, int);
		
		int n, N, M;
		int S, T;
		int row, col, K;
		vector< vector<int> > node;
		vector< vector<int> > mate;
		vector< vector<int> > flow;
		vector< vector<int> > cost;
		/*inline int getS(){
			return S;
		}
		inline int getT(){
			return T;
		}
		inline int getn(){
			return n;
		}*/
};

#endif