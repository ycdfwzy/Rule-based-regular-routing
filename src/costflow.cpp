#pragma comment(linker,"/STACK:128000000,128000000")
#include "costflow.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>

using namespace std;
const int inf=0x3f3f3f3f;

int *H2;

CostFlow::CostFlow(Graph& g):G(g){
	H = new int[G.n];
	H2 = new int[G.n];
	Ti = new int[G.n];
	V = new bool[G.n];
	V2 = new bool[G.n];
	Q = new int[G.n*10];
	S = new int[G.n];
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
	delete[] S;
	delete[] H2;
}

static int *E;
static Edge *Er;
bool CostFlow::TotalMinCostMaxFlow(){
	E=G.E;
	Er=G.Pool;
    /*
	cout<<"S T "<<G.S<<" "<<G.T<<endl;
	for(int i=0;i<=G.N;i++){
		for(int j=0;j<=G.M;j++){
			int id=G.Number[i][j]*5;
			cout<<"i j "<<i<<" "<<j<<endl;
			for(int k=0;k<9;k+=2)
			cout<<Er[id+k].flow<<" "<<Er[id+1+k].flow<<" ";cout<<endl;
		}
	}
	cout<<endl;
	*/

	int row1,row2,col1,col2;
	row1=min((G.K+1)*G.row/2+G.K,G.N/2);
	row2=G.N-row1;
	if(row2==row1)row1--,row2++;
	col1=min((G.K+1)*G.col/2+G.K,G.M/2);
	col2=G.M-col1;
	if(col1==col2)col1--,col2++;
	//cout<<"row "<<G.N<<" "<<row1<<" "<<row2<<endl;
	//cout<<"col "<<G.M<<" "<<col1<<" "<<col2<<endl;

	for (int i = 0; i <= G.N; ++ i){			// add normal nodes
		for (int j = 0; j <= G.M; ++ j){
			int id = G.Number[i][j];
			if(0<i && i<G.N && 0<j && j<G.M && i%(G.K+1)==0 && j%(G.K+1)==0)
				if((i+j)/(G.K+1)>=G.row/2+G.col/2-1)Er[id*5].flow=0;
			if(i<=row1&&j<=col1)continue;
			Er[id*5].flow=0;
		}
	}
	
	BFS();
	MinCostMaxFlow();
	//cout<<"MaxFlow "<<maxflow<<endl;
	//cout<<"MinCost "<<mincost<<endl;
	//cout<<(G.row/2)*(G.col/2)-3<<endl;
	if(maxflow<max(0,(G.row/2)*(G.col/2)-3))return false;

	for(int i=0;i<=G.N;i++)
		for(int j=0;j<=G.M;j++){
			int id=G.Number[i][j];
			int tmp=G.Number[min(i,G.N-i)][min(j,G.M-j)];

			if((row1<i && i<row2) || (col1<j && j<col2)){
				H[id]=H[id+1]=0;
				continue;
			}
			else{
				H[id]=H[tmp];
				H[id+1]=H[tmp+1];
			}

			if(i<=row1&&j<=col1)continue;

			id*=5;
			tmp*=5;
			Er[id].flow=Er[tmp].flow;
			Er[id+1].flow=Er[tmp+1].flow;

			if(i==0 || j==0 || i==G.N || j==G.M){
				Er[id+2].flow=Er[tmp+2].flow;
				Er[id+3].flow=Er[tmp+3].flow;
				continue;
			}

			if(i>=row2){
			    Er[id+2].flow=Er[tmp+4].flow;
				Er[id+3].flow=Er[tmp+5].flow;
				Er[id+4].flow=Er[tmp+2].flow;
			    Er[id+5].flow=Er[tmp+3].flow;
			}
			else{
			    Er[id+2].flow=Er[tmp+2].flow;
				Er[id+3].flow=Er[tmp+3].flow;
				Er[id+4].flow=Er[tmp+4].flow;
			    Er[id+5].flow=Er[tmp+5].flow;
			}
			
			if(j>=col2){
			    Er[id+6].flow=Er[tmp+8].flow;
				Er[id+7].flow=Er[tmp+9].flow;
				Er[id+8].flow=Er[tmp+6].flow;
			    Er[id+9].flow=Er[tmp+7].flow;
			}
			else{
			    Er[id+6].flow=Er[tmp+6].flow;
				Er[id+7].flow=Er[tmp+7].flow;
				Er[id+8].flow=Er[tmp+8].flow;
			    Er[id+9].flow=Er[tmp+9].flow;
			}
		}
	
	for (int i = 1; i <= G.row; ++ i){		//add internal nodes
		for (int j = 1; j <= G.col; ++ j){
			//((K+1)*i, (K+1)*j)
			int x = (G.K+1)*i, y = (G.K+1)*j;
			int id = G.Number_inter[i][j];
			int tmp = G.Number_inter[min(i,G.row+1-i)][min(j,G.col+1-j)];

			//cout<<"Step1 "<<Er[id].flow<<" "<<Er[id+1].flow<<endl;
			if(Er[id].flow+Er[id+1].flow==1)continue;
			if(row1<x && x<row2){Er[id].flow=1;continue;}
			if(col1<y && y<col2){Er[id].flow=1;continue;}
			//cout<<"OK3"<<endl;
			if(Er[tmp].flow+Er[tmp+1].flow==1)Er[id+1].flow=1;else Er[id].flow=1;
		}
	}

	maxflow*=4;
	mincost*=4;

	for (int i = 0; i <= G.N; ++ i){			// add normal nodes
		for (int j = 0; j <= G.M; ++ j){
			int id = G.Number[i][j]*5;
			if(Er[id].flow+Er[id+1].flow==0){
				Er[id].flow=1;
				//cout<<i<<" "<<j<<endl;
			}
		}
	}
	//freopen("log.txt","w",stdout);
	//cout<<"S T "<<G.S<<" "<<G.T<<endl;
	/*
	for(int i=0;i<=G.N;i++){
		for(int j=0;j<=G.M;j++){
			int id=G.Number[i][j]*5;
			cout<<"i j "<<i<<" "<<j<<endl;
			for(int k=0;k<9;k+=2)
			cout<<Er[id+k].flow<<" "<<Er[id+1+k].flow<<" ";cout<<endl;
		}
	}
	*/
	MinCostMaxFlow();
	if(maxflow<(G.row*G.col))return false;else return true;
}
void CostFlow::PartMinCostMaxFlow(){
	E=G.E;
	Er=G.Pool;
	memset(H, 0, sizeof(int)*G.n);
	memset(V, true, sizeof(bool)*G.n);
	MinCostMaxFlow();
}
void CostFlow::MinCostMaxFlow(){
	do{
		times++; t = 0;
		//cout<<" V "<<V[G.S]<<endl;
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

void CostFlow::SPFA(){
	memset(H, 63, sizeof(int)*G.n);
	memset(V, true, sizeof(bool)*G.n);
	memset(S, 0 ,sizeof(int)*G.n);

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
	
	if(tmp>=inf){
		for(int i=1;i<=t;i++)V[Q[i]]=true;
		return false;
	}
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
