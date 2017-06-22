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
	Q = new int[G.n<<1];
	memset(Ti, 0, sizeof(int)*G.n);
	memset(H, 63, sizeof(int)*G.n);
	memset(V, true, sizeof(bool)*G.n);
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

void CostFlow::MinCostMaxFlow(){
	BFS();
	cnt = 0;
	do{
		times++; t = 0;
		aug(G.S, inf);
		//cout << maxflow << endl;
	} while (Judge());
}

void CostFlow::BFS(){
	int u,bot;
	H[Q[bot=1]=G.T]=0;V[G.T]=false;
	for(int top=1;top<=bot;top++){
		u=Q[top];
		for(Edge *P=G.E[u];P;P=P->next)
		    if(P->opp->flow&&H[u]-P->cost<H[P->y]){
				H[P->y]=H[u]-P->cost;
				if(V[P->y]){Q[++bot]=P->y;V[P->y]=false;}
		    }
		V[u]=true;
    }
	/*Q[t = 1] = G.T; V[G.T] = 1;
	for (int i = 1; i <= t; ++i){
		int x = Q[i];
		for (Edge *e = G.E[x]; e != NULL; e = e->next)
		if (e->opp->flow > 0 && D[e->y]-e->cost >= D[x]){
			D[e->y] = D[x]+e->cost;
			if (V[e->y] == 0){
				Q[++t] = e->y;
				V[e->y] = 1;
			}
		}
		V[x] = 0;
	}*/
	//memset(V, 0, sizeof(int)*G.n);
}

bool CostFlow::Judge(){
	/*if (V[G.T] == times) return true;
	int delta = inf;
	for (int k = 0; k < t; ++ k){
		int i = Q[k];
		for (Edge* e = G.E[i]; e != NULL; e = e->next)
		if (e->flow > 0 && V[e->y] < times){
			delta = min(delta, D[i]-D[e->y]+e->cost);
		}
	}
	if (delta == inf) return false;
	for (int k = 0; k < t; ++ k)
		D[Q[k]] -= delta;
	return true;*/
	int u,tmp=inf;
	for(int i=1;i<=t;i++){
		u=Q[i];
		for(Edge *P=G.E[u];P;P=P->next)
		    if(P->flow&&V[P->y])tmp=min(tmp,H[P->y]+P->cost-H[u]);
	}
	if(tmp>=inf)return false;
	for(int i=1;i<=t;i++){
		u=Q[i];H[u]+=tmp;V[u]=true;
	}
	return true;
}

int CostFlow::aug(int u,int lefts){
	//cout << u << " " << lefts << endl;
	if(u==G.T){mincost+=H[G.S]*lefts;maxflow+=lefts;return lefts;}
	int ret=0,tmp;
	//cout << u << " " << lefts << endl;
	if(V[u]){Q[++t]=u;V[u]=false;}
	V2[u]=false;
	for(Edge *P=G.E[u];P&&ret<lefts;P=P->next)
	    if(P->flow&&V2[P->y]&&Ti[P->y]!=times && H[u]==H[P->y]+P->cost){
			tmp=aug(P->y,min(lefts-ret,(int)P->flow));
			ret+=tmp;P->flow-=tmp;P->opp->flow+=tmp;
	    }
	V2[u]=true;
	if(ret<lefts)Ti[u]=times;
    return ret;
}
/*
int CostFlow::aug(int cur, int f){
	if (V[cur] < times) Q[t++] = cur;
	V[cur] = times;
	if (cur == G.T){
		maxflow += f;
		mincost -= D[G.S]*f;
		return f;
	}
	int ret = 0;
	for (Edge* e = G.E[cur]; e != NULL && f > ret; e = e->next)
	if (e->flow > 0 && V[e->y] < times && D[cur]+e->cost == D[e->y]){
		int tmp = aug(e->y, min(f-ret, e->flow));
		e->flow -= tmp;
		e->opp->flow += tmp;
		ret += tmp;
	}
	return ret;
}*/