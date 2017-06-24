#pragma comment(linker,"/STACK:128000000,128000000")
#include "costflow.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
#define inf 0x3f3f3f3f

CostFlow::CostFlow(Graph& g):G(g){
	H = new int[G.n];
	Ti = new int[G.n];
	V = new bool[G.n];
	V2 = new bool[G.n];
	Q = new int[G.n*5];
	memset(Ti, 0, sizeof(int)*G.n);
	memset(V2, true, sizeof(bool)*G.n);
	times = 0;
	maxflow = 0;
	mincost = 0;
	t = 0;
}

CostFlow::~CostFlow(){
	delete[] H;
	delete[] Ti;
	delete[] V;
	delete[] V2;
	delete[] Q;
}

static int *E;
static Edge *Er;
void CostFlow::MinCostMaxFlow(){
	E=G.E;
	Er=G.Pool;
	BFS();
	cnt = 0;
	do{
		times++; t = 0;
		aug(G.S, inf);
		//cout << "Times = "<< times <<" "<<t<< " " << maxflow << endl;
	} while (Judge());
}

inline int Opposite(int x){return x^1;}
void CostFlow::BFS(){
	memset(H, 63, sizeof(int)*G.n);
	memset(V, true, sizeof(bool)*G.n);

	int u,v,bot;
	H[Q[bot=1]=G.T]=0;V[G.T]=false;
	for(int top=1;top<=bot;top++){
		u=Q[top];
		for(int P=E[u];P;P=Er[P].next){
			v=Er[P].to;
		    if(Er[Opposite(P)].flow && H[u]-Er[P].cost < H[v]){
				H[v]=H[u]-Er[P].cost;
				if(V[v]){Q[++bot]=v;V[v]=false;}
		    }
		}
		V[u]=true;
    }
}

bool CostFlow::Judge(){
	int u,v,tmp=inf;
	for(int i=1;i<=t;i++){
		u=Q[i];
		for(int P=E[u];P;P=Er[P].next){
			v=Er[P].to;
		    if(Er[P].flow && V[v])tmp=min(tmp,H[v]+Er[P].cost-H[u]);
		}
	}
	if(tmp>=inf)return false;
	for(int i=1;i<=t;i++){
		u=Q[i];H[u]+=tmp;V[u]=true;
	}
	return true;
}

int CostFlow::aug(int u,int lefts){
	if(u==G.T){
		mincost+=H[G.S];
		maxflow++;
		return lefts;
    }
	int v,ret=0,tmp;
	if(V[u]){Q[++t]=u;V[u]=false;}
	V2[u]=false;
	for(int P=E[u];P && ret<lefts;P=Er[P].next){
		v=Er[P].to;
	    if(Er[P].flow && V2[v] && Ti[v]!=times && H[u]==H[v]+Er[P].cost){
			tmp=aug(v,min(lefts-ret,(int)Er[P].flow));
			ret+=tmp;Er[P].flow-=tmp;Er[Opposite(P)].flow+=tmp;
	    }
	}
	V2[u]=true;
	if(ret<lefts)Ti[u]=times;
    return ret;
}
