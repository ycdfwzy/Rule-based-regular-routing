#include "graph.h"
#include "visual.h"
#include "networkflow.h"
#include "costflow.h"
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void TEST(){
	Graph G(10, 10, 5);
	NetworkFlow ntf(G);
	ntf.MaxFlow();
	cout << ntf.maxflow << endl;
	static Visual vis;
	vis.Paint(ntf.G);
}

int main(int argc, char* argv[]){
	TEST();
	return 0;
}