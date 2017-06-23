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

Graph G(80, 80, 24);

void TEST(){
	//cout << G.n << endl;
	/*NetworkFlow *ntf = new NetworkFlow(G);
	ntf->MaxFlow();
	cout << "MaxFlow: " << ntf->maxflow << endl;*/
	CostFlow *cf = new CostFlow(G);
	cf->MinCostMaxFlow();
	cout << "MaxFlow: " << cf->maxflow << endl;
	cout << "MinCost: " << cf->mincost << endl;
}

void Paint(){
	Visual *vis = new Visual;
	vis->Paint(G);
}

int main(int argc, char* argv[]){
	int size = 64 << 20; // 64MB  
    char *p = (char*)malloc(size) + size;  
    __asm__("movl %0, %%esp\n" :: "r"(p));  
	TEST();
	Paint();
	return 0;
}