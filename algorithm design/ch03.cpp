/*
Graph
*/
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

void BFS(vector<vector<int>>&Adj,int s){
 int n=Adj.size();
 vector<int> Discovered(n,0);
 vector<vector<int>>L;
 Discovered[s]=1;
 vector<int> temp;
 L.push_back(temp);
 L[0].push_back(s);
 int i=0;
 while(L[i].size()>0){
  L.push_back(temp);
  for(int k=0;k<L[i].size();k++){
   for(int w=0;w<Adj[L[i][k]].size();w++){
    if(Discovered[Adj[L[i][k]][w]]==0){
      Discovered[Adj[L[i][k]][w]]=1;
      L[i+1].push_back(Adj[L[i][k]][w]);
    }
   }
  }
  i++;
 }
 /*
 for(int j=0;j<i;j++){
  cout<<"dist "<<(j)<<endl;
  cout<<"Nodes: "<<endl;
  for(int k=0;k<L[j].size();k++) cout<<" "<<L[j][k];
  cout<<endl;
 }
 */
}

void DFS(vector<vector<int>>&Adj,int s){
 int n=Adj.size();
 vector<int>Explored(n,0);
 stack<int> st;
// cout<<endl;
 st.push(s);
 while(st.size()>0){
  int cur =st.top();

  st.pop();
  if(Explored[cur]==0){
  // cout<<" "<<cur;
   Explored[cur]=1;
   for(int k=0;k<Adj[cur].size();k++){
     if(Explored[Adj[cur][k]]==0){
      st.push(Adj[cur][k]);
     }
   }
  }
 }
 //cout<<endl;
}
void AllConnectedComponents(vector<vector<int>>&Adj){
  int n=Adj.size();
  vector<int> Explored(n,0);
  stack<int> st;
  for(int i=0;i<n;i++){

    if(Explored[i]==0){
    cout<<"Connected: "<<endl;
     st.push(i);
     while(st.size()>0){
      int cur =st.top();
      st.pop();
      if(Explored[cur]==0){
       cout<<" "<<cur;
        Explored[cur]=1;
        for(int k=0;k<Adj[cur].size();k++){
          if(Explored[Adj[cur][k]]==0){
           st.push(Adj[cur][k]);
          }
        }
      }
     }
     cout<<endl;
    }

  }

}
void IsBipartiteness(vector<vector<int>>& Adj){
 /*
 If a graph G is biparitite ,then it cannot contain an odd cycle
 */
 int n =Adj.size();
 vector<int> Discovered(n,0);
 vector<int> Color(n,-1);
 for(int i=0;i<n;i++){
  if(Discovered[i]==0){
   vector<vector<int>> L;
   vector<int> temp;
   L.push_back(temp);
   int k=0;

   L[k].push_back(i);
   while(L[k].size()>0){
    L.push_back(temp);
    for(int w=0;w<L[k].size();w++){
     if(Discovered[L[k][w]]==0){
       Discovered[L[k][w]]=1;
       Color[L[k][w]]=k%2;
       for(int m=0;m<Adj[L[k][w]].size();m++){
        if(Discovered[Adj[L[k][w]][m]]==0){
         L[k+1].push_back(Adj[L[k][w]][m]);
        }
       }
     }
    }
    k++;
   }

  }
 }
 bool res =true;
 for(int i=0;i<n;i++){
  if(res==false) break;
  for(int j=0;j<Adj[i].size();j++){
   if(Color[i]==Color[j]){
    res =false;
    break;
   }
  }
 }
 if(res==true) cout<<"Is Bipartiteness"<<endl;
 else cout<<"Not Bipartiteness"<<endl;
}

void DFS(int v,vector<vector<int>>&From,vector<vector<int>>&To,vector<int>& order,vector<int>&Explored){
  Explored[v]=1;
  for(int i=0;i<To[v].size();i++){
    if(Explored[To[v][i]]==0){
      DFS(To[v][i],From,To,order,Explored);
    }
  }
  order.push_back(v);
}
void DirectedStrongConnectivity(vector<vector<int>>&From,vector<vector<int>>&To){
 int n=From.size();
 stack<int>st;
 /*
 first DFS obtain topological order,(for StronglyConnectedComponent graph ,the original graph may be not DAG)
 */
 vector<int> order;
 vector<int>Explored(n,0);
 for(int i=0;i<n;i++){
   if(Explored[i]==0){
     DFS(i,From,To,order,Explored);
   }
   }
   for(int i=0;i<n;i++) Explored[i]=0;
   while(order.size()>0){
     int i =order.back();
     //cout<<" "<<i<<endl;
     order.pop_back();
     if(Explored[i]==0){
     cout<<"StronglyConnected:"<<endl;
      st.push(i);
      while(st.size()>0){
       int cur =st.top();
       cout<<" "<<cur;
       st.pop();
       if(Explored[cur]==0){
         Explored[cur]=1;
         for(int k=0;k<From[cur].size();k++){
           if(Explored[From[cur][k]]==0){
             st.push(From[cur][k]);
           }
         }
       }
      // if(st.size()==0) cout<<endl;
      }
     cout<<endl;
     }
   }
 }

 void TopologicalOrdering(vector<vector<int>>&From,vector<vector<int>>&To){
  /*
  topological sort <-> DAG indegree=0
  or dfs to ouput in fininsh time order
  */
  int n =From.size();
  vector<int> active(n,0);
  vector<int> order;
  int start =0;
  for(int i=0;i<n;i++){
    active[i]=From[i].size();
    if(active[i]==0) start=i;
  }
  int counts=n;
  stack<int> points;
  points.push(start);
  while(counts>0){
   start =points.top();
   points.pop();
   order.push_back(start);
   int last =start;
   for(int i=0;i<To[last].size();i++){
    active[To[last][i]]--;
    if(active[To[last][i]]==0){
     points.push(To[last][i]);
    }
   }
   counts--;
  }
  cout<<endl;
  for(int i=0;i<order.size();i++) cout<<" "<<order[i];
  cout<<endl;
 }

 void eulers(int v,vector<vector<int>>& edges,vector<vector<int>>&Explored){
   for(int i=0;i<edges.size();i++){
     if(Explored[v][i]==0 && edges[v][i]==1){
      Explored[v][i]=Explored[i][v]=1;
      eulers(i,edges,Explored);
      cout<<""<<v<<"--"<<i<<endl;
     }
   }
 }
 void eulers2(vector<vector<int>>&Adj){
 int n=Adj.size();
 vector<vector<int>> edges(Adj.size(),vector<int>(Adj.size(),0));
 for(int i=0;i<Adj.size();i++){
 //undirected  edge should be symmetric
  for(int j=0;j<Adj[i].size();j++) {edges[i][Adj[i][j]]=1;edges[Adj[i][j]][i]=1;}
 }
 int start=5;
 vector<vector<int>>Explored(n,vector<int>(n,0));
 eulers(start,edges,Explored);

 }
int main(){

 int n =13;
 vector<vector<int>>Adj={{1,2},{0,2,3,4},{0,1,4,6,7},{1,4},{2,3,5},{4},{2,7},{2,6},{9},{8},{11},{10,12},{11}};
 vector<vector<int>>From={{4},{0},{1,3},{2},{1},{1,4,6},{2,5},{3,6,7}};
 vector<vector<int>>To={{1},{2,4,5},{3,6},{2,7},{0,5},{6},{5,7},{7}};

 vector<vector<int>>From2={{},{0},{1},{2},{1},{1,4,6},{2},{3,6}};
 vector<vector<int>>To2={{1},{2,4,5},{3,6},{7},{5},{0},{5,7},{}};
 vector<vector<int>>Adj2={{1,2},{0,2,3,4},{0,1,4,6,7},{1,4},{2,3,5},{4},{2,7},{2,6}};



// BFS(Adj,0);
// DFS(Adj,0);
// AllConnectedComponents(Adj);

 //IsBipartiteness(Adj);
// DirectedStrongConnectivity(From,To);
 //TopologicalOrdering(From2,To2);

 //eulers2(Adj2);
 return 0;
}
