/*
Dynamic Programming

*/
#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>
#include<cstring>
#include<map>
#include<cstdlib>
#include<queue>
using namespace std;

struct cmp1{
 bool operator()(pair<pair<float,float>,float> a,pair<pair<float,float>,float> b){
  return a.first.second<b.first.second;
 }
};

void WeightedIntervalScheduling(){
 vector<pair<pair<float,float>,float>> nums={{{0,0},0},{{1,2.5},2},{{2,4.5},4},{{4,7},4},{{2.2,10},7},{{8,11},2},{{9,12},1}};
 sort(nums.begin(),nums.end(),cmp1());
 vector<int>p(nums.size(),0);
 vector<float>d(nums.size(),0);
 vector<int>r(nums.size(),0);
 for(int i=1;i<nums.size();i++){
  int j=i-1;
  while(j>=0 && nums[i].first.first<nums[j].first.second) j--;
  p[i]=j;
 }
 for(int i=1;i<nums.size();i++){
  if((d[p[i]]+nums[i].second)>=(d[i-1])){
   d[i]=d[p[i]]+nums[i].second;
   r[i]=p[i];
  }else{
   d[i]=d[i-1];
   r[i]=i-1;
  }
  cout<<"d["<<i<<"]"<<" "<<d[i]<<endl;
 }

 int i =nums.size()-1;
 while(i>0){
  if(d[i]==d[i-1]){
   i =i-1;
  }else{
   cout<<i<<" : "<<p[i]<<endl;
   i =r[i];
  }
 }
 }

 void SegmentedLeastSquares(){
  vector<pair<float,float>>nums={{0.0,0.0},{1,1.3},{2,2.2},{3,2.8},{4,3.9},{5,4.5},{6,5.4},{7,6.7},{8,15.4},{9,17.4},{10,20.5},
  {11,23},{12,23.1},{13,26.3},{14,14.1},{15,15.9},{16,16.4},{17,16.8},{18,17.9}};
  vector<float> x(nums.size(),0);
  vector<float> y(nums.size(),0);
  vector<float> xx(nums.size(),0);
  vector<float> xy(nums.size(),0);
  int C=4;
  for(int i=1;i<nums.size();i++){
   x[i]=nums[i].first+x[i-1];
   y[i]=nums[i].second+y[i-1];
   xx[i]=nums[i].first*nums[i].first+xx[i-1];
   xy[i]=nums[i].first*nums[i].second+xy[i-1];
  }
  vector<vector<int>> e(nums.size(),vector<int>(nums.size(),0));
  for(int i=1;i<nums.size();i++){
   for(int j=i-1;j>0;j--){
   //cout<<"e["<<j<<"]["<<i<<"]"<<" "<<e[j][i]<<endl;
    float a =((i-j+1)*(xy[i]-xy[j-1])-(x[i]-x[j-1])*(y[i]-y[j-1]))/((i-j+1)*(xx[i]-xx[j-1])-(x[i]-x[j-1])*(x[i]-x[j-1]));
    float b =((y[i]-y[j-1])-a*(x[i]-x[j-1]))/(i-j+1);
    for(int k=j;k<=i;k++){
     cout<<"k "<<k<<" "<<(nums[k].second-a*nums[k].first-b)*(nums[k].second-a*nums[k].first-b)<<endl;
     e[j][i]=e[j][i]+(nums[k].second-a*nums[k].first-b)*(nums[k].second-a*nums[k].first-b);
    }
    cout<<"e["<<j<<"]["<<i<<"]"<<" "<<e[j][i]<<endl;
   }
  }
  vector<int> d(nums.size(),0);
  vector<int> r(nums.size(),0);
  for(int i=1;i<nums.size();i++){
   float val =9999.0;
   for(int j=i;j>0;j--){
    if(val>(e[j][i]+C+d[j-1])){
     val =e[j][i]+C+d[j-1];
     r[i]=j;

    }
   }
   d[i]=val;
  }
  cout<<"error "<<d[nums.size()-1]<<endl;
  int i =nums.size()-1;
  while(i>0){
   cout<<i<<" : "<<r[i]<<endl;
   i =r[i]-1;
  }
 }
 void SubsetSum(){
  int W=6;
  vector<int>w={0,2,2,3};
  vector<vector<int>>d(w.size()+1,vector<int>(W+1,0));
  vector<vector<int>>r(w.size()+1,vector<int>(W+1,0));
  for(int i=1;i<w.size();i++){
   for(int k=0;k<=W;k++){
    if(k<w[i]){
     d[i][k]=d[i-1][k];
     r[i][k]=r[i-1][k];
    }else{
     if((d[i-1][k])>(d[i-1][k-w[i]]+w[i])){
      d[i][k]=d[i-1][k];
      r[i][k]=r[i-1][k];
     }else{
      d[i][k]=d[i-1][k-w[i]]+w[i];
      r[i][k]=i;
     }
    }
   }
  }
  cout<<"max "<<d[3][W]<<endl;
  int k=3,V=W;
  while(r[k][V]>0){
   cout<<r[k][V]<<endl;
   int x =r[k][V]-1;
   V =V-w[r[k][V]];
   k =x;
  }
 }

 void RNASecondaryStructure(){
  string str="ACCGGUAGU";
  map<char,char>dict;
  dict['A']='U';dict['U']='A';dict['C']='G';dict['G']='C';
  int n =str.length();
  int d[n+1][n+1];
  int r[n+1][n+1];
  memset(d,0,sizeof(d));
  memset(r,0,sizeof(r));

  for(int l=5;l<=n;l++){
   for(int i=0;i<=(n-l);i++){
    int j=i+l-1;
    d[i][j]=d[i][j-1];
    r[i][j]=r[i][j-1];
    for(int k=i;k<j-4;k++){
     if(str[k]==dict[str[j]]){
      int temp =1+d[i][k-1]+d[k+1][j-1];
      if(temp>d[i][j]){
       d[i][j]=temp;
       r[i][j]=k;
      }
     }
    }
   }
  }
  for(int i=0;i<=3;i++){
   cout<<endl;
   for(int j=5;j<9;j++){
    cout<<d[i][j];
   }
  }
  }

void SequenceAlignment(){
 string s1 ="mean";
 string s2 ="name";
 int cost[4]={0,2,1,3};
 int m =s1.length();
 int n =s2.length();
 int d[m+1][n+1];
 int r[m+1][n+1];//0 表示对角， 1 表示左移 ,2 表示右移动
 memset(d,0,sizeof(d));
 memset(r,0,sizeof(r));
 for(int i=0;i<=m;i++) d[i][0]=cost[1]*i;
 for(int i=0;i<=n;i++) d[0][i]=cost[1]*i;
 int judge[26];
 memset(judge,0,sizeof(judge));
 judge['a'-'a']=1;judge['e'-'a']=1;judge['i'-'a']=1;judge['o'-'a']=1;judge['u'-'a']=1; //元音字母

 for(int i=1;i<=m;i++){
  for(int j=1;j<=n;j++){
   int a=0,b=0,c=0;
   if(s1[i-1]==s2[j-1]) a=cost[0];
   else if(judge[s1[i-1]-'a']==judge[s2[j-1]-'a']) a=cost[2];
   else a=cost[3];
   if((a+d[i-1][j-1])<=(cost[1]+d[i-1][j]) && (a+d[i-1][j-1])<=(cost[1]+d[i][j-1])){
    d[i][j]=a+d[i-1][j-1];
    r[i][j]=1;
   }else if((a+d[i-1][j-1])>(cost[1]+d[i-1][j]) && (cost[1]+d[i][j-1])>(cost[1]+d[i-1][j])){
    d[i][j]=cost[1]+d[i-1][j];
    r[i][j]=2;
   }else{
    d[i][j]=cost[1]+d[i][j-1];
    r[i][j]=3;
   }
  }
 }


 cout<<" "<<d[m][n]<<endl;
 int x=m,y=n;
 string s3="";
 string s4="";
 while(r[x][y]!=0){
  if(r[x][y]==1){
   s3.append(1,s1[x-1]);
   s4.append(1,s2[y-1]);
   x=x-1;
   y=y-1;
  }else if(r[x][y]==2){
   s3.append(1,s1[x-1]);
   s4.append(1,'_');
   x=x-1;
  }else{
   s3.append(1,'_');
   s4.append(1,s2[y-1]);
   y=y-1;
  }
 }
 reverse(s3.begin(),s3.end());
 reverse(s4.begin(),s4.end());
 cout<<" "<<s3<<endl;
 cout<<" "<<s4<<endl;
}

void BellmanFord(){
 int n=5;
 int d[n][n];
 int m[n+1][n+1];
 memset(m,0,sizeof(m));
 memset(d,0,sizeof(d));
 for(int i=1;i<n;i++) m[0][i]=INT_MAX;
 d[0][1]=6;d[0][4]=7;d[3][0]=2;d[1][2]=5;d[2][1]=-2;d[1][4]=8;d[1][3]=-4;
 d[4][2]=-3;d[3][2]=7;d[4][3]=9;
 int changed =1;
 for(int i=1;i<=n;i++){
  //if(changed==0) break;
  changed =0;
  for(int k=1;k<n;k++){
   m[i][k]=m[i-1][k];
   for(int w=0;w<n;w++){
    if(d[w][k]!=0 && m[i-1][w]!=INT_MAX){
     if(m[i][k]>(d[w][k]+m[i-1][w])){
      changed =1;
      m[i][k]=d[w][k]+m[i-1][w];
     }
    }
   }
  }
 }

 for(int i=0;i<n;i++){
  if(m[n][i]!=m[n-1][i]){
   cout<<"negative circle "<<endl;
   break;
  }
 }


 for(int i=0;i<n;i++){
  cout<<endl;
  for(int j=0;j<n;j++)cout<<" "<<m[i][j];
 }


}

void PushBasedShortestPath(){
 int n=5;
 int d[n][n];
 int m[n];
 int first[n];
 int last[n];
 memset(first,0,sizeof(first));
 memset(m,0,sizeof(m));
 memset(d,0,sizeof(d));
 memset(last,0,sizeof(last));
 for(int i=0;i<n;i++) {last[i]=m[i]=INT_MAX;}
 m[0]=0;
 d[0][1]=6;d[0][4]=7;d[3][0]=2;d[1][2]=5;d[2][1]=-2;d[1][4]=8;d[1][3]=-4;
 d[4][2]=-3;d[3][2]=7;d[4][3]=9;



 for(int i=1;i<n;i++){
  for(int k=0;k<n;k++){
   if(m[k]!=last[k]){
    for(int w=0;w<n;w++){
     if(d[k][w]!=0 && m[k]!=INT_MAX && (d[k][w]+m[k])<m[w]){
      last[w]=m[w];
      m[w]=d[k][w]+m[k];
      first[w]=k;
     }
    }
    last[k]=m[k];
   }
  }
 }

 for(int i=0;i<n;i++){
  cout<<" "<<m[i]<<endl;
 }

}

void AsychronousShortestPath(){
  int n=5;
 int d[n][n];
 int m[n];
 int first[n];
 memset(first,0,sizeof(first));
 memset(m,0,sizeof(m));
 memset(d,0,sizeof(d));
 for(int i=0;i<n;i++) {m[i]=INT_MAX;}
 m[0]=0;
 d[0][1]=6;d[0][4]=7;d[3][0]=2;d[1][2]=5;d[2][1]=-2;d[1][4]=8;d[1][3]=-4;
 d[4][2]=-3;d[3][2]=7;d[4][3]=9;
 vector<int> active;
 active.push_back(0);
 while(active.size()>0){
  int k =active.back();
  active.pop_back();
  for(int w=0;w<n;w++){
   if(d[k][w]!=0 && m[k]!=INT_MAX && (m[k]+d[k][w])<(m[w])){
     m[w]=m[k]+d[k][w];
     first[w]=k;
     active.push_back(w);
   }
  }
 }
 for(int i=0;i<n;i++){
  cout<<" "<<m[i]<<endl;
 }

}
void PrintAllPairsShortestPath(vector<vector<int>>&pi,int i,int j){
 if(i==j){
  cout<<i;
  return;
 }
 if(pi[i][j]==-1){
  cout<<"no path from i to j"<<endl;
  return;
 }else{
  PrintAllPairsShortestPath(pi,i,pi[i][j]);
  cout<<"->"<<j;
  return;
 }
}
void ExtendShortestPaths(vector<vector<int>>&L,vector<vector<int>>&W,vector<vector<int>>&pi){
 int n =L.size();
 for(int i=0;i<n;i++){
  for(int j=0;j<n;j++){
   int val =0;
   for(int k=0;k<n;k++){
    if(L[i][k]!=INT_MAX && W[k][j]!=INT_MAX) val =L[i][k]+W[k][j];
    else continue;
    if(L[i][j]>val){
     L[i][j]=val;
     pi[i][j]=k;
    }
   }
  }
 }
}
void FasterAllPairsShortestPath(){
 int n=5;
 vector<vector<int>>W(n,vector<int>(n,INT_MAX));
 W[0][1]=3;W[0][0]=0;W[0][2]=8;W[0][4]=-4;W[1][4]=7;W[1][3]=1;W[1][1]=0;
 W[2][1]=4;W[2][2]=0;W[3][0]=2;W[3][2]=-5;W[3][3]=0;W[4][3]=6;W[4][4]=0;
 vector<vector<int>>L;
 L.assign(W.begin(),W.end());
 vector<vector<int>>pi(n,vector<int>(n,-1));
 pi[0][1]=0;pi[0][2]=0;pi[0][4]=0;pi[1][4]=1;pi[1][3]=1;
 pi[2][1]=2;pi[3][0]=3;pi[3][2]=3;pi[4][3]=4;
 int m=1;
 while(m<(n-1)){
  ExtendShortestPaths(L,L,pi);
  m =2*m;
 }

 for(int i=0;i<n;i++){
  cout<<endl;
  for(int j=0;j<n;j++){
   cout<<" <"<<i<<","<<j<<">";
   cout<<":  "<<L[i][j];
   //PrintAllPairsShortestPath(pi,i,j);
   //cout<<endl;
  }
 }
 return;

}
void FloydWarshall(){
 int n=5;
 vector<vector<int>>W(n,vector<int>(n,INT_MAX));
 W[0][1]=3;W[0][0]=0;W[0][2]=8;W[0][4]=-4;W[1][4]=7;W[1][3]=1;W[1][1]=0;
 W[2][1]=4;W[2][2]=0;W[3][0]=2;W[3][2]=-5;W[3][3]=0;W[4][3]=6;W[4][4]=0;
 vector<vector<int>>L;
 L.assign(W.begin(),W.end());
 vector<vector<int>>pi(n,vector<int>(n,-1));
 pi[0][1]=0;pi[0][2]=0;pi[0][4]=0;pi[1][4]=1;pi[1][3]=1;
 pi[2][1]=2;pi[3][0]=3;pi[3][2]=3;pi[4][3]=4;
 for(int k=0;k<n;k++){
  for(int i=0;i<n;i++){
   int val =0;
   for(int j=0;j<n;j++){
    if(L[i][k]!=INT_MAX && L[k][j]!=INT_MAX) val=L[i][k]+L[k][j];
    else continue;
    if(L[i][j]>val){
     L[i][j]=val;
     pi[i][j]=pi[k][j];
    }
   }
  }
 }

 for(int i=0;i<n;i++){
  cout<<endl;
  for(int j=0;j<n;j++){
   cout<<" <"<<i<<","<<j<<">";
   cout<<":  "<<L[i][j];
   //PrintAllPairsShortestPath(pi,i,j);
   //cout<<endl;
  }
 }

}

struct mycmp3{
 bool  operator()(pair<int,int>a,pair<int,int>b){
   return a.second>b.second;
 }
};
void dijkstra(vector<vector<int>>& d,vector<int>& dist,int v){
 int n =d.size();
 vector<vector<int>> outputs(n,vector<int>());
 //vector<int> dist(n,INT_MAX-1000);
 priority_queue< pair<int,int>,vector<pair<int,int> >,mycmp3>pq;
 vector<int> done(n,0);

 for(int i=0;i<n;i++){
  for(int j=0;j<n;j++){
   if(d[i][j]!=INT_MAX){
    outputs[i].push_back(j);
   }
  }
 }
 dist[v]=0;
 for(int i=0;i<n;i++){
  if(i==v){
   pq.push(make_pair(i,0));
  }else pq.push(make_pair(i,INT_MAX));
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
  //cout<<v<<"-->"<<cur.first<<" : "<<dist[cur.first]<<endl;
  for(int j=0;j<outputs[cur.first].size();j++){
    int from =cur.first;
    int to =outputs[cur.first][j];
    if(d[from][to]!=INT_MAX && dist[from]!=INT_MAX &&dist[to]>(dist[from]+d[from][to])){
     dist[to]=dist[from]+d[from][to];
     pq.push(make_pair(to,dist[to]));
    }
  }
 }

}


void TransitiveClosure(){
  int n=5;
 vector<vector<int>>W(n,vector<int>(n,INT_MAX));
 W[0][1]=3;W[0][0]=0;W[0][2]=8;W[0][4]=-4;W[1][4]=7;W[1][3]=1;W[1][1]=0;
 W[2][1]=4;W[2][2]=0;W[3][0]=2;W[3][2]=-5;W[3][3]=0;W[4][3]=6;W[4][4]=0;

 vector<vector<int>>T(n,vector<int>(n,0));
 T[0][1]=1;T[0][0]=1;T[0][2]=1;T[0][4]=1;T[1][4]=1;T[1][3]=1;T[1][1]=1;
 T[2][1]=1;T[2][2]=1;T[3][0]=1;T[3][2]=1;T[3][3]=1;T[4][3]=1;T[4][4]=1;

 for(int k=0;k<n;k++){
  for(int i=0;i<n;i++){
   for(int j=0;j<n;j++){
    T[i][j]=(T[i][j] | (T[i][k] & T[k][j]));
   }
  }
 }
}

void Johnson(){
   int n=5;
 vector<vector<int>>W(n,vector<int>(n,INT_MAX));
 W[0][1]=3;W[0][0]=0;W[0][2]=8;W[0][4]=-4;W[1][4]=7;W[1][3]=1;W[1][1]=0;
 W[2][1]=4;W[2][2]=0;W[3][0]=2;W[3][2]=-5;W[3][3]=0;W[4][3]=6;W[4][4]=0;
 for(int i=0;i<n;i++){
  W[i].insert(W[i].begin(),INT_MAX);
 }
 W.insert(W.begin(),vector<int>(n+1,0));
  n++;
 vector<vector<int>>L(n,vector<int>(n,INT_MAX));

 vector<int>d(n,INT_MAX);
 d[0]=0;
 bool negcircle =false;
 int changed =0;
 for(int k=1;k<(n+1);k++){
  for(int i=0;i<n;i++){
   int val=0;
   for(int j=0;j<n;j++){
    if(d[j]!=INT_MAX && W[j][i]!=INT_MAX){
     val =d[j]+W[j][i];
    }else continue;
    if(val<d[i]){
     changed =k;
     d[i]=val;
    }
   }
  }
 }
 //for(int i=0;i<n;i++)cout<<"d["<<i<<"]"<<" "<<d[i]<<endl;
 if(changed==n){
  cout<<"has negative circle "<<endl;
  return;
 }

 else{
  for(int i=0;i<n;i++){
   //cout<<endl;
   for(int j=0;j<n;j++){

    if(W[i][j]!=INT_MAX){
     W[i][j]=W[i][j]+d[i]-d[j];
    }
   // cout<<" "<<W[i][j];
   }

  }
  //cout<<endl;
  //cout<<"dist "<<endl;
  for(int i=1;i<n;i++){
   dijkstra(W,L[i],i);
   for(int j=1;j<n;j++){
    L[i][j]=L[i][j]-d[i]+d[j];
   }
   //cout<<endl;
  }


 }


}
int main(){
 //WeightedIntervalScheduling();
// SegmentedLeastSquares();
// SubsetSum();
// RNASecondaryStructure();
// SequenceAlignment();
// BellmanFord();
 //PushBasedShortestPath();
 // AsychronousShortestPath();
 //FasterAllPairsShortestPath();
 //FloydWarshall();
// Johnson();
 return 0;
}
