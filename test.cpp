#include "graph.h"
#include "networkflow.h"
#include "costflow.h"
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void TEST(){
	Graph G(4, 4, 1);
	NetworkFlow ntf(G);
	ntf.MaxFlow();
	cout << ntf.maxflow << endl;
}

int main(int argc, char* argv[]){
	TEST();
	return 0;
}