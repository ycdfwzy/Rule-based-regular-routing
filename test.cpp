#pragma comment(linker,"/STACK:128000000,128000000")
#include "graph.h"
#include "visual.h"
#include "networkflow.h"
#include "costflow.h"
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

Graph G(70, 70, 20);

void TEST(){
	cout << G.n << endl;
	/*NetworkFlow ntf(G);
	ntf.MaxFlow();
	cout << ntf.maxflow << endl;*/
	CostFlow *cf = new CostFlow(G);
	cf->MinCostMaxFlow();
	cout << "MaxFlow: " << cf->maxflow << endl;
	cout << "MinCost: " << cf->mincost << endl;
	/*static Visual vis;
	vis.Paint(cf.G);*/
}

int main(int argc, char* argv[]){
	TEST();
	return 0;
}