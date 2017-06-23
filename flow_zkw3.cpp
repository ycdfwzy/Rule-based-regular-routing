#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>

#define maxn 3400
#define INF  0x3f3f3f3f
#define dou  double
using namespace std;
int  Number[maxn][maxn];
bool Interval[maxn][maxn];
int  n,m,Length;
int  S,T,K=0,Times=0;
int  flow_sum=0.0,flow=0.0;

//Edge
struct Edge{
	Edge *n,*o;int v,c,w;
	void init(int _v,int _c,int _w){n=o=NULL;v=_v;c=_c;w=_w;}
};
Edge *E[maxn*maxn],Er[(int)(maxn*maxn*6.0)];int Es=0;
void addEdge(int u,int v,int c,int w){
	static Edge *P1,*P2;P1=&Er[++Es];P2=&Er[++Es];
	P1->init(v,c,w); P1->n=E[u];P1->o=P2;E[u]=P1;
	P2->init(u,0,-w);P2->n=E[v];P2->o=P1;E[v]=P2;
}
//ZKW
int  H[maxn*maxn];
int  V[maxn*maxn],V2[maxn*maxn],Ti[maxn*maxn],Q[maxn*maxn*2];
void BFS(){
	int u,bot;
	H[Q[bot=1]=T]=0;V[T]=false;
	for(int top=1;top<=bot;top++){
		u=Q[top];
		for(Edge *P=E[u];P;P=P->n)
		    if(P->o->c&&H[u]-P->w<H[P->v]){
				H[P->v]=H[u]-P->w;
				if(V[P->v]){Q[++bot]=P->v;V[P->v]=false;}
		    }
		V[u]=true;
    }
    //cout<<"BFS"<<endl;
    //for(int i=S;i<=T;i++)cout<<i<<" "<<H[i]<<endl;
}
int  aug(int u,int lefts){
	if(u==T){flow+=H[S]*lefts;flow_sum+=lefts;return lefts;}
	int ret=0,t;
	if(V[u]){Q[++K]=u;V[u]=false;}
	V2[u]=false;
	for(Edge *P=E[u];P&&ret<lefts;P=P->n)
	    if(P->c&&V2[P->v]&&Ti[P->v]!=Times && H[u]==H[P->v]+P->w){
			t=aug(P->v,min(lefts-ret,(int)P->c));
			ret+=t;P->c-=t;P->o->c+=t;
	    }
	V2[u]=true;
	if(ret<lefts)Ti[u]=Times;
    return ret;
}
bool upd(){
	int u,tmp=INF;
	for(int i=1;i<=K;i++){
		u=Q[i];
		for(Edge *P=E[u];P;P=P->n)
		    if(P->c&&V[P->v])tmp=min(tmp,H[P->v]+P->w-H[u]);
	}
	if(tmp>=INF)return false;
	for(int i=1;i<=K;i++){
		u=Q[i];H[u]+=tmp;V[u]=true;
	}
	return true;
}
void Mincost(){
	for(int i=S;i<=T;i++)H[i]=INF;
	memset(V,true,sizeof(V));
	memset(V2,true,sizeof(V2));
	BFS();
	while(true){
		Times++;K=0;
		aug(S,INF);
		//cout << flow_sum << endl;
		if(!upd())break;		
	}
	cout<<"flow "<<flow_sum<<" "<<flow<<endl;
}
void Print(){
	//cout<<flow<<endl;
	/*
	static bool Map[maxn][maxn];
	memset(Map,0,sizeof(Map));
	for(int i=1;i<=n;i++){
		for(Edge *P=E[i];P;P=P->n)
		    if(P->o->c&&P->v>n)Map[i][P->v-n]=true;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(Map[i][j])printf("1");else printf("0");
		printf("\n");
		
	}
	*/
}
void init(){
	memset(Number,0,sizeof(Number));
	memset(Interval,0,sizeof(Interval));
	scanf("%d%d",&n,&m);
	Length=m*(n+1);
	S=0;
	int sum=0;
	for(int i=0;i<=Length;i++)
	    for(int j=0;j<=Length;j++){
	    	if(i<j||i>=Length/2)continue; 
	    	sum+=2;
			Number[i][j]=sum;
			Interval[i][j]=(i%m==0 && j%m==0 && i!=0 && j!=0 && i!=Length && j!=Length);
		}
	T=sum+1;
	for(int i=0;i<=Length;i++)
	    for(int j=0;j<=Length;j++){
	    	if(i<j||i>=Length/2)continue; 
	    	addEdge(Number[i][j]-1,Number[i][j],1,0);
	    	if(Interval[i][j])addEdge(S,Number[i][j]-1,1,0);
	    	if(i==0||j==0||i==Length||j==Length)addEdge(Number[i][j],T,1,0);
	    	
			if(i>0 && !Interval[i-1][j] && Number[i-1][j])addEdge(Number[i][j],Number[i-1][j]-1,1,1);
			if(i<Length && !Interval[i+1][j] && Number[i+1][j])addEdge(Number[i][j],Number[i+1][j]-1,1,1);
			if(j>0 && !Interval[i][j-1] && Number[i][j-1])addEdge(Number[i][j],Number[i][j-1]-1,1,1);
			if(j<Length && !Interval[i][j+1] && Number[i][j+1])addEdge(Number[i][j],Number[i][j+1]-1,1,1);
		}
	cout<<T<<" "<<Es<<endl;
}
void init2(){
	memset(Number,0,sizeof(Number));
	memset(Interval,0,sizeof(Interval));
	scanf("%d%d",&n,&m);
	Length=m*(n+1);
	S=0;
	int sum=0;
	for(int i=0;i<=Length;i++)
	    for(int j=0;j<=Length;j++){
	    	if(i<=j||i>=Length/2)continue; 
	    	sum+=2;
			Number[i][j]=sum;
			Interval[i][j]=(i%m==0 && j%m==0 && i!=0 && j!=0 && i!=Length && j!=Length);
		}
	T=sum+1;
	for(int i=0;i<=Length;i++)
	    for(int j=0;j<=Length;j++){
	    	if(i<=j||i>=Length/2)continue; 
	    	addEdge(Number[i][j]-1,Number[i][j],1,0);
	    	if(Interval[i][j])addEdge(S,Number[i][j]-1,1,0);
	    	if(i==0||j==0||i==Length||j==Length)addEdge(Number[i][j],T,1,0);
	    	
			if(i>0 && !Interval[i-1][j] && Number[i-1][j])addEdge(Number[i][j],Number[i-1][j]-1,1,1);
			if(i<Length && !Interval[i+1][j] && Number[i+1][j])addEdge(Number[i][j],Number[i+1][j]-1,1,1);
			if(j>0 && !Interval[i][j-1] && Number[i][j-1])addEdge(Number[i][j],Number[i][j-1]-1,1,1);
			if(j<Length && !Interval[i][j+1] && Number[i][j+1])addEdge(Number[i][j],Number[i][j+1]-1,1,1);
		}
	cout<<T<<" "<<Es<<endl;
}
int  main(){
	//freopen("image.in","r",stdin);
	//freopen("image3.out","w",stdout);
	//init();
	init2();
	Mincost();
	Print();
	return 0;
}
