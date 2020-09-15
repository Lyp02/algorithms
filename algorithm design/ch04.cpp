/*
Greedy Algorithm
optimal structure
*/
#include<iostream>
#include<vector>
#include<climits>
#include<cstring>
#include<algorithm>
#include<queue>
#include<set>

using namespace std;

void dp_print(vector<vector<int>>& p,int i,int j){
 if(p[i][j]==0) return;
 dp_print(p,i,p[i][j]);
 cout<<"<"<<p[i][j]<<">"<<" ";
 dp_print(p,p[i][j],j);
}
void interval_schedule_dp(vector<int>& s,vector<int>& f){
 int n=s.size();
 //cout<<"n "<<n<<endl;
 //s[0],s[n+2]=INT_MAX;
 //f[0]=0,f[n+2]
 s.insert(s.begin(),INT_MIN);
 s.push_back(INT_MAX);
 f.insert(f.begin(),0);
 f.push_back(0);
 int c[n+2][n+2];
 vector<vector<int>>p(n+2,vector<int>(n+2,0));
 memset(c,0,sizeof(c));

 int temp =0;
 int t =0;
 for(int l=1;l<=n;l++){
  for(int i=0;i<=n-l;i++){
   int j=i+l+1;
   temp =0;
   t =0;
   for( int k=i+1;k<j;k++){
     if(s[k]>=f[i] && f[k]<=s[j]){

      temp =c[i][k]+c[k][j]+1;
      if(temp>c[i][j]){
       c[i][j]=temp;
       t =k;
      }
     }
   }

   p[i][j]=t;
   //cout<<"<"<<i<<","<<j<<">"<<" size "<<c[i][j]<<" split "<<p[i][j]<<endl;
  }
 }
 cout<<"items "<<endl;
 dp_print(p,0,n+1);
 cout<<endl;

}

void interval_schedule_greedy(vector<int>& s,vector<int>& f){
 int n=s.size();
 s.insert(s.begin(),0);
 f.insert(f.begin(),0);
 vector<int> p;
 int t =f[0];
 for(int i=1;i<=n;i++){
  if(s[i]>=t){
   cout<<"i "<<i<<" "<<s[i]<<endl;
   t =f[i];
   p.push_back(i);
  }
 }
 cout<<" size "<<p.size()<<endl;
 for(int i=0;i<p.size();i++){
  cout<<" "<<p[i];
 }
 cout<<endl;
}


 bool mycmp(pair<int,int>a,pair<int,int>b){
  return a.first<b.first;
 }

 struct cmp{
  bool operator()(pair<int,int>a,pair<int,int>b){
   return a.first<b.first;
  }

 };

 bool overlap(pair<int,int> a,pair<int,int>b){
  return a.first>=b.second || a.second<=b.first;
 }
void interval_partition(vector<int>& s,vector<int>& f){
 int n =s.size();
 vector<pair<int,int>> events;
 for(int i=0;i<n;i++){
  events.push_back(make_pair(s[i],f[i]));
 }
 sort(events.begin(),events.end(),cmp());

 for(int i=0;i<n;i++){
  cout<<"s: "<<events[i].first<<" , "<<"f: "<<events[i].second<<endl;
 }
 vector<int>labels(n,0);
 int d =1;
 labels[0]=d;
 for(int i=1;i<n;i++){
  int counts =1;

  for(int j=0;j<i;j++){
   if(!overlap(events[i],events[j])){
    counts++;
   }
  }
  cout<<"counts "<<counts<<" d "<<d<<endl;
  if(counts>d){
   d++;
   labels[i]=d;
  }else{
   labels[i]=counts;
  }
 }
 cout<<" size "<<d<<endl;
}

struct ListNode{
 int val;
 ListNode* next;
 ListNode(int x):val(x),next(NULL){}
};
void insert_node(ListNode* head,ListNode* v){
 if(head!=NULL && v!=NULL){
  v->next =head->next;
  head->next =v;
 }
 return;
}
ListNode* partition_node(ListNode* head){
  if(head!=NULL){
   if(head->next==NULL){
    ListNode* v =new ListNode(head->val+1);
    head->val++;
    return v;
   }else{
    ListNode* cur =head->next;
    head->next =head->next->next;
    return cur;
   }
  }else return NULL;
}

bool mycmp2(pair<int,pair<int,int>>a,pair<int,pair<int,int>>b){
 if(a.second.first==b.second.first){
  return a.second.second>b.second.second;
 }else return a.second.first<b.second.first;
}
void interval_partition2(vector<int>&s,vector<int>&f){
 int n =s.size();
 vector<pair<int,pair<int,int>>> vecs;
 for(int i=0;i<n;i++){
  vecs.push_back(make_pair(i,make_pair(s[i],0)));
  vecs.push_back(make_pair(i,make_pair(f[i],1)));
 }
 sort(vecs.begin(),vecs.end(),mycmp2);
 /*
 for(int i=0;i<2*n;i++){
  if(vecs[i].second.second==0){
   cout<<"time "<<vecs[i].second.first<<", "<<vecs[i].first<<" "<<"Entering"<<endl;
  }else{
   cout<<"time "<<vecs[i].second.first<<", "<<vecs[i].first<<" "<<"Leaving"<<endl;
  }
 }
 */
 ListNode* head =new ListNode(0);
 vector<ListNode*>sources(n,NULL);
 ListNode* cur=NULL;
 for(int i=0;i<2*n;i++){
  if(vecs[i].second.second==0){
   cur =partition_node(head);
   sources[vecs[i].first]=cur;
   cout<<"time "<<vecs[i].second.first<<" , "<<vecs[i].first<<" Entering"<<endl;
  }else{
   cur =sources[vecs[i].first];
   insert_node(head,cur);
   cout<<"time "<<vecs[i].second.first<<" , "<<vecs[i].first<<" Leaving "<<endl;
     }
 }

 cout<<"size "<<head->val<<endl;
}


void schedule_minimize_lateness(vector<int>& t,vector<int>& d){
 //minmize maximize(di-fi) earliest deadline first
 int s =1;
 int lateness =0;
 int n =t.size();
 for(int i=0;i<n;i++){

   lateness =max(lateness,s+t[i]-1-d[i]);
   s =s +t[i];
 }
 cout<<"lateness "<<lateness<<endl;
}

void optimal_caching(string s,int k){
 //Farthest-in-Future
 int n =s.length();
 int miss=0;
 if(k>=n) return;
 vector<vector<int>> pos(26,vector<int>());
 vector<int>Next(26,0);
 vector<char>mem(k,'0');
 vector<int>exist(26,0);
 for(int i=0;i<n;i++){
   pos[s[i]-'a'].push_back(i);
 }
 for(int i=0;i<k;i++){
  mem[i]=s[i];
  exist[s[i]-'a']=1;
  Next[s[i]-'a']++;
 }

 for(int i=k;i<n;i++){
   if(exist[s[i]-'a']){
    Next[s[i]-'a']++;
    continue;
   }else{
    int val =-1;
    int far =-1;
    int mask =0;
    for(int j=0;j<k;j++){
     if(Next[mem[j]-'a']>=pos[mem[j]-'a'].size()){
      mask=1;
      far =j;
      break;
     }
     else if(val<pos[mem[j]-'a'][Next[mem[j]-'a']]){
      val =pos[mem[j]-'a'][Next[mem[j]-'a']];
      far=j;
     }
    }
     cout<<endl;
     for(int j=0;j<k;j++)cout<<" "<<mem[j];
     cout<<endl;
     miss++;
     cout<<"output "<<mem[far]<<endl;
     exist[mem[far]-'a']=0;
     mem[far]=s[i];
     cout<<"input "<<mem[far]<<endl;
     exist[mem[far]-'a']=1;
     Next[s[i]-'a']++;

   }
 }
 cout<<" miss size "<<miss<<endl;

 }

void bellman_ford(vector<vector<int>>& d,int v){
 int  n=d.size();
 vector<int> p(n,-1);
 vector<int> dist(n,INT_MAX);
 dist[v]=0;
 vector<vector<int>> edges(n,vector<int>());
 for(int i=0;i<n;i++){
  for(int j=0;j<n;j++){
   if(d[i][j]>0){
    edges[i].push_back(j);
   }
  }
 }
 for(int i=0;i<n-1;i++){
  for(int k=0;k<edges.size();k++){
   for(int w=0;w<edges[k].size();w++){
     if(dist[edges[k][w]]>(dist[k]+d[k][edges[k][w]])){
      dist[edges[k][w]]=dist[k]+d[k][edges[k][w]];
      p[edges[k][w]]=k;
     }
   }
  }
 }

 for(int k=0;k<edges.size();k++){
  for(int w=0;w<edges[k].size();w++){
   if(dist[edges[k][w]]>(dist[k]+d[k][edges[k][w]])){
    cout<<"negative circle "<<endl;
    break;
   }
  }
 }
 for(int i=0;i<n;i++){
  cout<<v<<"-->"<<i<<": "<<dist[i]<<endl;
 }
}
void dfs(vector<vector<int>>& outputs,int v,vector<int>& topo,vector<int>& colors){
  for(int i=0;i<outputs[v].size();i++){
    if(colors[outputs[v][i]]==-1){
     dfs(outputs,outputs[v][i],topo,colors);
    }
  }
  colors[v]=1;
  topo.push_back(v);
}
void dag_shortest_path(vector<vector<int>>& d,int v){
 //allow negative edges
 int  n=d.size();
 vector<vector<int>> inputs(n,vector<int>());
 vector<vector<int>> outputs(n,vector<int>());
 vector<int> dist(n,INT_MAX-1000);

 for(int i=0;i<n;i++){
  for(int j=0;j<n;j++){
   if(d[i][j]!=0){
     inputs[j].push_back(i);
     outputs[i].push_back(j);
   }
  }
 }
 vector<int> topo;
 vector<int> colors(n,-1);
 for(int i=0;i<n;i++){
   if(colors[i]==-1){
    dfs(outputs,i,topo,colors);
   }
 }
 reverse(topo.begin(),topo.end());
 cout<<endl;
 for(int i=0;i<n;i++) cout<<" "<<topo[i];
 cout<<endl;
 dist[v]=0;
 for(int i=0;i<n;i++){
  int cur =topo[i];
  for(int j=0;j<inputs[cur].size();j++){
   if(dist[cur]>(dist[inputs[cur][j]]+d[inputs[cur][j]][cur])){
    dist[cur]=dist[inputs[cur][j]]+d[inputs[cur][j]][cur];
   }
  }
 }

 for(int i=0;i<n;i++){
  cout<<topo[0]<<"-->"<<topo[i]<<" : "<<dist[i]<<endl;
 }

}
struct mycmp3{
 bool  operator()(pair<int,int>a,pair<int,int>b){
   return a.second>b.second;
 }
};
void dijkstra(vector<vector<int>>& d,int v){
 int n =d.size();
 vector<vector<int>> outputs(n,vector<int>());
 vector<int> dist(n,INT_MAX-1000);
 priority_queue< pair<int,int>,vector<pair<int,int> >,mycmp3>pq;
 vector<int> done(n,0);

 for(int i=0;i<n;i++){
  for(int j=0;j<n;j++){
   if(d[i][j]!=0){
    outputs[i].push_back(j);
   }
  }
 }
 dist[v]=0;
 for(int i=0;i<n;i++){
  if(i==v){
   pq.push(make_pair(i,0));
  }else pq.push(make_pair(i,INT_MAX-1000));
 }

 pair<int,int>cur;
 while(n>0 && pq.size()>0){
  while(pq.size()>0){
   cur =pq.top();
   if(done[cur.first]==0) break;
   else{
    pq.pop();
   }
  }
  pq.pop();
  n--;
  done[cur.first]=1;
  dist[cur.first]=cur.second;
  cout<<v<<"-->"<<cur.first<<" : "<<dist[cur.first]<<endl;
  for(int j=0;j<outputs[cur.first].size();j++){
    int from =cur.first;
    int to =outputs[cur.first][j];
    if(dist[to]>(dist[from]+d[from][to])){
     dist[to]=dist[from]+d[from][to];
     pq.push(make_pair(to,dist[to]));
    }
  }
 }

}
//路径压缩
int find_set(int x,vector<int>&p){

if(x==p[x]) return x;
else{

  p[x] =find_set(p[x],p);
 }
 return p[x];
}
//按秩合并
void union_set(int x,int y,vector<int>& ranks,vector<int>&p){
 int x_p =find_set(x,p);
 int y_p =find_set(y,p);
 if(ranks[x_p]<ranks[y_p]){
  p[x_p]=y_p;
 }else{
  p[y_p]=x_p;
  if(ranks[x_p]==ranks[y_p]) ranks[x_p]++;
 }
}


struct mycmp4{
 bool operator()(pair<int,int> a,pair<int,int> b){
   return a.second>b.second;
 }
};



void prim(vector<vector<int>>d,int v){
 int n=d.size();


 vector<vector<int>>outputs(n,vector<int>());
 priority_queue<pair<int,int>,vector<pair<int,int>>,mycmp4>pq;
 vector<int> done(n,0);
 vector<int> p(n,-1);
 vector<int> dist(n,INT_MAX-1000);
 dist[v]=0;
 for(int i=0;i<n;i++){
  if(i==v) pq.push(make_pair(i,0));
  else pq.push(make_pair(i,INT_MAX-1000));
  for(int j=0;j<n;j++){
    if(d[i][j]!=0){
     outputs[i].push_back(j);
    // outputs[j].push_back(i);
    }
  }
  }

  pair<int,int> cur;
  while(n>0 && pq.size()>0){
   while(pq.size()>0){
   cur =pq.top();
   if(done[cur.first]==0) break;
   pq.pop();
   }
   pq.pop();
   n--;
   int from =cur.first;
   done[from]=1;
   cout<<"edge "<<p[from]<<"--"<<from<<endl;
   int to=-1;
   for(int i=0;i<outputs[from].size();i++){
    to =outputs[from][i];
    if(done[to]==0 && dist[to]>d[from][to]){
     dist[to]=d[from][to];
     pq.push(make_pair(to,dist[to]));
     p[to]=from;
    }
   }
  }

}
struct mycmp5{
 bool operator()(pair<pair<int,int>,int>a ,pair<pair<int,int>,int>b){
  return a.second<b.second;
 }
};
vector<pair<pair<int,int>,int>> kruskal(vector<vector<int>>&d){
 int n=d.size();
 vector<pair<pair<int,int>,int>> edges;
 vector<pair<pair<int,int>,int>> links;
 vector<int>p;
 vector<int>ranks(n,0);
 for(int i=0;i<n;i++){
  p.push_back(i);
  for(int j=i+1;j<n;j++){
   if(d[i][j]!=0){
    edges.push_back(make_pair(make_pair(i,j),d[i][j]));
   }
  }
 }
 sort(edges.begin(),edges.end(),mycmp5());
 int index =0;
 pair<pair<int,int>,int>cur;
 while(n>1 && index <edges.size()){
  cur =edges[index];
  //cout<<cur.first.first<<"--"<<cur.first.second<<endl;
  //cout<<p[cur.first.first]<<"--"<<p[cur.first.second]<<endl;
  int a =find_set(cur.first.first,p);
  int b =find_set(cur.first.second,p);

  if(a==b){
   index++;
   continue;
  }
  cout<<cur.first.first<<"--"<<cur.first.second<<" weight "<<d[cur.first.first][cur.first.second]<<endl;
  links.push_back(cur);
  n--;
  index++;
  union_set(a,b,ranks,p);

 }
 return links;
}

void single_sink_clustering(vector<vector<int>>& d,int k){
 int n=d.size();
 vector<pair<pair<int,int>,int>>links =kruskal(d);
 pair<pair<int,int>,int>cur;
 for(int i=0;i<n-k;i++){
  cur =links[i];
  cout<<cur.first.first<<"--"<<cur.first.second<<" weight "<<d[cur.first.first][cur.first.second]<<endl;
 }
}




struct Node{
 int freq;
 char ch;
 Node* left;
 Node* right;
 Node(int x,char c):freq(x),ch(c),left(NULL),right(NULL){}
};
struct mycmp6{
 bool operator()(Node* a,Node*b){
 return (a->freq)>(b->freq);
 }
};

void inorder_walk(Node* head){
 if(head==NULL) return;
 inorder_walk(head->left);
 cout<<"char:  "<<head->ch<<" freq: "<<head->freq<<endl;
 inorder_walk(head->right);
}
Node* huffman(vector<char>& ch, vector<int>& freqs){
 int  n=ch.size();
 priority_queue<Node*,vector<Node*>,mycmp6>pq;
 for(int i=0;i<n;i++){
  Node* temp =new Node(freqs[i],ch[i]);
  pq.push(temp);
 }
 while(pq.size()>1){
  Node* n1 =pq.top();
  pq.pop();
  Node* n2 =pq.top();
  pq.pop();
  Node* n3 =new Node(n1->freq+n2->freq,'0');
  n3->left =n1;
  n3->right =n2;
  pq.push(n3);
 }
 return pq.top();

 }

int main(){
 vector<int> s={1,3,0,5,3,5,6,8,8,2,12};
 vector<int> f={4,5,6,7,9,9,10,11,12,14,16};

 vector<int> t={3,2,1,4,3,2};
 vector<int> d={6,8,9,9,14,15};
 string str ="abcdadeadbc";

 vector<vector<int>> V1={{0,10,0,5,0},{0,0,1,2,0},{0,0,0,0,4},{0,3,9,0,2},{2,0,6,0,0}};
 vector<vector<int>> V2={{0,5,3,0,0,0},{0,0,2,6,0,0},{0,0,0,7,4,2},{0,0,0,0,-1,1},{0,0,0,0,0,-2},{0,0,0,0,0,0}};
 //bellman_ford(V1,0);
 vector<vector<int>>  V3(9,vector<int>(9,0));
 V3[0][1]=V3[1][0]=4;V3[0][2]=V3[2][0]=8;V3[1][3]=V3[3][1]=8;V3[3][8]=V3[8][3]=2;V3[8][2]=V3[2][8]=7;V3[8][5]=V3[5][8]=6;
 V3[3][6]=V3[6][3]=4;V3[5][6]=V3[6][5]=2;V3[3][4]=V3[4][3]=7;V3[4][6]=V3[6][4]=14;V3[4][7]=V3[7][4]=9;V3[6][7]=V3[7][6]=10;
 V3[2][5]=V3[5][2]=1;V3[1][2]=V3[2][1]=11;
 vector<char> ch={'f','e','c','b','d','a'};
 vector<int>  frqs={5,9,12,13,16,45};
 vector<pair<pair<int,int>,int>> edges={make_pair(make_pair(1,2),2),make_pair(make_pair(1,3),10),make_pair(make_pair(1,4),10),
 make_pair(make_pair(3,2),1),make_pair(make_pair(2,4),4),make_pair(make_pair(4,5),2),make_pair(make_pair(5,3),2),make_pair(make_pair(4,6),4),make_pair(make_pair(4,6),8)};

 //interval_schedule_dp(s,f);
 //interval_schedule_greedy(s,f);
 //interval_partition(s,f);
// interval_partition2(s,f);
 //schedule_minimize_lateness(t,d);
 // optimal_caching(str,3);
 //dag_shortest_path(V2,1);
  //dijkstra(V1,0);
 //prim(V3,0);
 //kruskal(V3);
 // single_sink_clustering(V3,5);
// Node* node =huffman(ch,frqs);
// inorder_walk(node);


 return 0;
}
