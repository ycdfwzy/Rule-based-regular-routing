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
	static Graph G(80, 80, 30);
	/*NetworkFlow ntf(G);
	ntf.MaxFlow();
	cout << ntf.maxflow << endl;*/
	static CostFlow cf(G);
	cf.MinCostMaxFlow();
	cout << "MaxFlow: " << cf.maxflow << endl;
	cout << "MinCost: " << cf.mincost << endl;
	static Visual vis;
	vis.Paint(cf.G);
}

int main(int argc, char* argv[]){
	TEST();
	return 0;
}