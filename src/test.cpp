#pragma comment(linker,"/STACK:128000000,128000000")
#include "greedy.h"
#include "graph.h"
#include "costflow.h"
#include "networkflow.h"
#include "maxflow.h"
#include "visual.h"
#include <cstring>
#include <algorithm>
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

//Graph *G_ = NULL;
//CostFlow *cf_ = NULL;

bool TEST_MAXFLOW(int N, int M, int K){
	clock_t start,finish;
	start = clock();
	Graph *G = new Graph(N, M, K);
	MaxFlow *nf = new MaxFlow(*G);
	nf->TotalMaxFlow();
	cout << "N = " << N << " M = " << M << " K = " << K << endl;
	if(nf->maxflow==N*M)cout << "MaxFlow: " <<N*M<< endl;else cout<<"Can't find maxflow!"<<endl;
	int tmp = nf->maxflow;
	delete nf;
	delete G;
	finish=clock();
    cout << "Time: " << (finish-start)/CLOCKS_PER_SEC << "s" << endl;
	return (tmp == N*M);
}

bool TEST_COSTFLOW(int N, int M, int K){
	clock_t start,finish;
	start = clock();
	Graph *G = new Graph(N, M, K);
	CostFlow *cf = new CostFlow(*G);
	bool flag=cf->TotalMinCostMaxFlow();
	if(!flag){
		cout << "N = " << N << " M = " << M << " K = " << K << endl;
		cout<<"Can't find full flow!"<<endl;
		delete cf;
		delete G;
		finish=clock();
		cout << "Time: " << (finish-start)/CLOCKS_PER_SEC << "s" << endl;
		return false;
	}
	cout << "N = " << N << " M = " << M << " K = " << K << endl;
	cout << "MaxFlow: " << cf->maxflow << endl;
	cout << "MinCost: " << cf->mincost << endl;
	//G_ = G; cf_ = cf;
	int tmp = cf->maxflow;
	finish=clock();
    cout << "Time: " << (finish-start)/CLOCKS_PER_SEC << "s" << endl;
	if (tmp == N*M){
		Visual *vis = new Visual;
		G->N++;G->M++;
		vis->Paint(*G);
		//delete G;
		delete vis;
	}
	delete cf;
	delete G;
	return (tmp == N*M);
	/**/
}

void TEST_GREEDY(int N, int M, int K){
	clock_t start,finish;
	start = clock();
	Greedy *grd = new Greedy(N, M, K);
	grd->greedy_algorithm();
	cout << "points: " << grd->maxpoints << endl;
	cout << "minlength: " << grd->minlength << endl;
	Visual *vis = new Visual;
	vis->Paint(*grd);
	delete grd;
	delete vis;
	finish=clock();
    cout << "Time: " << (finish-start)/CLOCKS_PER_SEC << "s" << endl;
}

void TEST(int N, int M, int K = 0){
	cout << "Costflow:" << endl;
	int ans;
	if (K > 0){
		//TEST_MAXFLOW(N, M, K);
		TEST_COSTFLOW(N, M, K);
	} else
	{
		int l = N*M/(N+M+2)/2, r = 24, mid;
		while (l <= r){
			mid = (l+r)/2;
			if (TEST_MAXFLOW(N, M, mid)){
				ans = mid;
				r = mid-1;
			} else
				l = mid+1;
		}
		cout << ans << endl;
	}
	TEST_COSTFLOW(N,M,ans);
	cout << "Greedy:" << endl;
	TEST_GREEDY(N, M, ans);
}


int main(int argc, char* argv[]){
	int size = 64 << 20; // 64MB
    char *p = (char*)malloc(size) + size;
    __asm__("movl %0, %%esp\n" :: "r"(p));
	if (argc == 3){
		TEST(atoi(argv[1]), atoi(argv[2]));
	} else
	if (argc == 4){
		TEST(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	}
	
	/*
	cout<<"Test MaxFlow"<<endl;
	TEST_MAXFLOW(80,80,21);
	TEST_MAXFLOW(80,80,22);
	TEST_MAXFLOW(80,80,23);
	TEST_MAXFLOW(80,80,24);
	*/
	
	//TEST_GREEDY();
	return 0;
}
