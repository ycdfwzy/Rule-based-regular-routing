#ifndef GREEDY_H_
#define GREEDY_H_

#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

class Greedy{
	public:
		int **MAP;
		int *Q, *D;
		int maxpoints;
		int minlength;
		int row, col, K;
		int N, M;
		
		Greedy(int, int, int);
		~Greedy();
		void greedy_algorithm();
		void BFS(int, int, int);
};

#endif