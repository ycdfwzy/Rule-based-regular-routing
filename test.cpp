#pragma comment(linker,"/STACK:128000000,128000000")
#include "greedy.h"
#include "graph.h"
#include "visual.h"
#include "networkflow.h"
#include "costflow.h"
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;


void TEST_FLOW(){
	Graph *G = new Graph(80, 80, 23);
	/*NetworkFlow *ntf = new NetworkFlow(*G);
	ntf->MaxFlow();
	cout << "MaxFlow: " << ntf->maxflow << endl;*/
	CostFlow *cf = new CostFlow(*G);
	cf->MinCostMaxFlow();
	cout << "MaxFlow: " << cf->maxflow << endl;
	cout << "MinCost: " << cf->mincost << endl;
	delete cf;
	Visual *vis = new Visual;
	vis->Paint(*G);
	delete G;
	delete vis;
}

void TEST_GREEDY(){
	Greedy *grd = new Greedy(80, 80, 23);
	grd->greedy_algorithm();
	cout << "maxpoints: " << grd->maxpoints << endl;
	cout << "minlength: " << grd->minlength << endl;
	Visual *vis = new Visual;
	vis->Paint(*grd);
	delete grd;
	delete vis;
}

int main(int argc, char* argv[]){
	int size = 64 << 20; // 64MB  
    char *p = (char*)malloc(size) + size;  
    __asm__("movl %0, %%esp\n" :: "r"(p));  
	TEST_FLOW();
	TEST_GREEDY();
	return 0;
}