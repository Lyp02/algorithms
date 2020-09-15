/*
NetFlow
*/
#include<iostream>
#include<vector>
#include<climits>
#include<cstring>
#include<cstdlib>
#include<queue>
using namespace std;
#define maxn 100


struct Edge{
 int from,to,cap,flow;
 Edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f){}
};

struct EdmondsKarp{
 int n,m;
 vector<Edge> edges; //边数的两倍
 vector<int> G[maxn]; //邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
 int a[maxn];// 当起点到i的可改进量
 int p[maxn];// 最短路上的p的入弧编号

 void init(int n){
  for(int i=0;i<n;i++) G[i].clear();
  edges.clear();
 }

 void AddEdge(int from,int to,int cap){
  edges.push_back(Edge(from,to,cap,0));
  edges.push_back(Edge(to,from,0,0));
  m =edges.size();
  G[from].push_back(m-2);
  G[to].push_back(m-1);
 }

 int Maxflow(int s,int t){
  int flow =0;
  for(;;){
   memset(a,0,sizeof(a));
   queue<int> Q;
   Q.push(s);
   a[s]=INT_MAX;
   while(!Q.empty()){
    int x =Q.front();Q.pop();
    for(int i=0;i<G[x].size();i++){
     Edge& e =edges[G[x][i]];
     if(!a[e.to] && e.cap>e.flow){
      p[e.to]=G[x][i];
      a[e.to]=min(a[x],e.cap -e.flow);
      Q.push(e.to);
     }
    }
    if(a[t]) break;
   }
   if(!a[t]) break;
   for(int u=t;u!=s;u=edges[p[u]].from){
    edges[p[u]].flow +=a[t];               //最短路树上p的入弧编号
    edges[p[u]^1].flow -=a[t];
   }
   flow +=a[t];
  }
  return flow;
 }

};

struct Edge2{
 int from,to,cap,flow,cost;
 Edge2(int u,int v,int c,int f,int w):from(u),to(v),cap(c),flow(f),cost(w){}
};

struct MCMF{
 int n,m;
 vector<Edge2> edges;
 vector<int> G[maxn];
 int inq[maxn];  //是否在队列中
 int d[maxn];    //Bellman-Ford
 int p[maxn];   //上一条弧
 int a[maxn];   //可改进量

 void init(int n){
  this->n =n;
  for(int i=0;i<n;i++) G[i].clear();
  edges.clear();
 }

 void AddEdge(int from,int to,int cap,int cost){
  edges.push_back(Edge2(from,to,cap,0,cost));
  edges.push_back(Edge2(to,from,0,0,-cost));
  m =edges.size();
  G[from].push_back(m-2);
  G[to].push_back(m-1);
 }

 bool BellmanFord(int s,int t,int& flow,long long &cost ){
  for(int i=0;i<n;i++) d[i]=INT_MAX;
  memset(inq,0,sizeof(inq));
  d[s]=0;inq[s]=1;p[s]=0;a[s]=INT_MAX;
  queue<int>Q;
  Q.push(s);
  while(!Q.empty()){
   int u =Q.front();Q.pop();
   inq[u]=0;
   for(int i=0;i<G[u].size();i++){
    Edge2& e =edges[G[u][i]];
    if(e.cap>e.flow && d[u]!=INT_MAX && d[e.to]>(d[u]+e.cost)){
     d[e.to] =d[u]+e.cost;
     p[e.to] =G[u][i];
     a[e.to] =min(a[u],e.cap-e.flow);
     if(!inq[e.to]){
      Q.push(e.to);inq[e.to]=1;
     }
    }
   }

  }
  if(d[t]==INT_MAX) return false;
  flow +=a[t];
  cost +=(long long)(d[t]*(long long)a[t]);
  for(int u=t;u!=s;u=edges[p[u]].from){
   edges[p[u]].flow +=a[t];
   edges[p[u]^1].flow -=a[t];
  }
  return true;
 }

 int MincostMaxflow(int s,int t,long long & cost){
  int flow =0;cost =0;
  while(BellmanFord(s,t,flow,cost));
  return flow;
 }

};

int main(){
 /*
 vector<pair<int,int>> edges={{0,1},{1,3},{3,5},{4,5},{4,3},{3,2},{2,4},{2,1},{0,2}};
 vector<int>caps ={16,12,20,4,7,9,14,4,13};
 EdmondsKarp edm;
 edm.init(6);
 for(int i=0;i<edges.size();i++){
  edm.AddEdge(edges[i].first,edges[i].second,caps[i]);
 }
 int flow=edm.Maxflow(0,5);
 cout<<"flow is "<<flow<<endl;
*/
 vector<pair<int,int>> edges={{0,1},{0,2},{0,3},{0,4},{0,5},{1,8},{2,10},{2,9},{3,9},{3,8},{4,9},{4,8},{5,8},
 {5,7},{5,6},{10,11},{9,11},{8,11},{7,11},{6,11}};
 vector<int> caps(20,1);
 EdmondsKarp edm;
 edm.init(12);
 for(int i=0;i<edges.size();i++){
  edm.AddEdge(edges[i].first,edges[i].second,caps[i]);
 }
 int flow =edm.Maxflow(0,11);
 cout<<"matching is "<<flow<<endl;
 return 0;
}
