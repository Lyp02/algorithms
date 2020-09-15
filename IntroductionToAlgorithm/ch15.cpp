/*
 Dynamic Programming
*/
#include<iostream>
#include<vector>
#include<climits>
#include<cstring>
#include<cmath>


using namespace  std;

typedef struct Node{
	int data;
	struct Node *next;
	Node(int x):data(x),next(NULL){
	}
}Node;

Node* copyNode(Node* head){
 Node* newhead =new Node(head->data);
 Node* cur =head->next;
 Node* item =newhead;

 while(cur!=NULL){

  Node* temp =new Node(cur->data);
  item->next =temp;
  item=item->next;
  cur =cur->next;
 }
 return newhead;

}

Node*  insertNode(Node* head,int val){
 Node* item =new Node(val);
 if(head==NULL) {
  head =item;
  return head;
 }
 item->next =head;
 head =item;
 return head;
}


int MEMORIZED_CUT_ROD_AUX(vector<int>&p,int n,vector<int>&r){
 if(n==0) return 0;
 if(r[n]!=INT_MIN) return r[n];
 r[n]=p[n];
 for(int i=1;i<n;i++){
  r[n] =max(r[n],p[i]+MEMORIZED_CUT_ROD_AUX(p,n-i,r));
 }
 return r[n];
}

int BOTTOM_UP_CUT_ROD(vector<int>& p,int n){
 vector<int> r(p.size(),INT_MIN);
 vector<int> s(p.size(),-1);
 r[0]=0;r[1]=p[1];
 for(int i=2;i<=n;i++){
  for(int j=1;j<=i;j++){
   if((p[j]+r[i-j])>r[i]){
    r[i] =p[j]+r[i-j];
    s[i]=j;
   }
  }

 }
 cout<<endl;
 int len =n;
 while(len>=0 && s[len]!=-1){
  cout<<" cut "<<s[len];
  len=len -s[len];
 }
 cout<<endl;
 return r[n];
}

void PRINT_OPTIMAL_PARENTS(vector<vector<int>>& s,int i,int j){
 if(i==j){
  cout<<" A"<<i<<" ";
 }else{
  cout<<"(";
  PRINT_OPTIMAL_PARENTS(s,i,s[i][j]);
  PRINT_OPTIMAL_PARENTS(s,s[i][j]+1,j);
  cout<<")";
 }
}

int MATRIX_CHAIN_ORDER(vector<int>& p){
 int n =p.size() -1;
 vector<vector<int>>s(n+1,vector<int>(n+1,0));
 vector<vector<int>>m(n+1,vector<int>(n+1,0));
 for(int l=2;l<=n;l++){
  for(int i=1;i<=n-l+1;i++){
   int j =i+l-1;
   int q =INT_MAX;
   for(int k=i;k<j;k++){
    if(q>(m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j])){
      q =m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
      s[i][j] =k;
    }
   }
   m[i][j] =q;
  }
 }
 PRINT_OPTIMAL_PARENTS(s,1,n);
 cout<<endl;
 return m[1][n];
}

void PRINT_LCS(vector<vector<int>>& b,string X,int i,int j){
  if(i==0 || j==0) return;
  else if(b[i][j]==1){
   PRINT_LCS(b,X,i-1,j-1);
   cout<<X[i];
  }else if(b[i][j]==2){
   PRINT_LCS(b,X,i,j-1);
  }else PRINT_LCS(b,X,i-1,j);
  return ;
}

int LCS_LENGTH(string X,string Y){
  int m =X.length();
  int n =Y.length();
  vector<vector<int>> b(m+1,vector<int>(n+1,-1));
  vector<vector<int>> c(m+1,vector<int>(n+1,0));
  for(int i=1;i<=m;i++){
   for(int j=1;j<=n;j++){
    if(X[i-1]==Y[j-1]){
      c[i][j]=1+c[i-1][j-1];
      b[i][j]=1;
    }else if(c[i-1][j]>=c[i][j-1]){
      c[i][j] =c[i-1][j];
      b[i][j] =3;
    }else{
      c[i][j]=c[i][j-1];
      b[i][j]=2;
    }
   }
  }
  cout<<endl;
  PRINT_LCS(b,X,m,n);
  cout<<endl;
  return c[m][n];
}

void LONG_MONOTONIC(vector<int>& A){
 int L =1;
 int n =A.size();
 Node* C[n+1];
 for(int i=0;i<=n;i++){
  C[i]=NULL;
 }
 vector<int> B;
 B.push_back(INT_MAX);
 for(int i=0;i<n;i++){
   if(A[i]<B[0]){
    B[0] =A[i];
    Node* temp = new Node(B[0]);
    C[1]=temp;
   }else{
    int low =0;
    int high = B.size()-1;
    int mid =low;
    while(low<=high){
     mid =low +(high-low)/2;
     if(low==high && B[mid]<A[i]){
      break;
     }else if(low==high){
      mid =low-1;
      break;
     }
     if(B[mid]>=A[i]) high =mid-1;
     else low=mid+1;
    }
    cout<<"B[mid] "<<B[mid]<<endl;
    cout<<"A[i] "<<A[i]<<endl;
    if(B[mid]>=A[i]) continue;

    C[mid+2] =copyNode(C[mid+1]);
    C[mid+2]=insertNode(C[mid+2],A[i]);
    if((mid+2)>L){
     L++;
     B.push_back(A[i]);
     }else {
     B[mid+1]=A[i];
     }
   }
 }
 cout<<"LCS size : "<<L<<endl;
 Node* cur =C[L];

 while(cur!=NULL){
  cout<<" "<<cur->data;
  cur =cur->next;
 }
 cout<<endl;

}
void CONSTRUCT_OPTIMAL_BST(vector<vector<int>>& root,int i,int j){
    int n=root.size()-1;
    if(i<1 || j>n || i>j) return;
    CONSTRUCT_OPTIMAL_BST(root,i,root[i][j]-1);
    cout<<root[i][j];
    CONSTRUCT_OPTIMAL_BST(root,root[i][j]+1,j);
}

void OPTIMAL_BST(vector<float>& p,vector<float>&q,int n){
 vector<vector<float>> e(n+2,vector<float>(n+2,0));
 vector<vector<float>> w(n+2,vector<float>(n+2,0));
 vector<vector<int>> root(n+1,vector<int>(n+1,0));

 for(int i=1;i<=n+1;i++){
  e[i][i-1] =q[i-1];
  w[i][i-1] =q[i-1];
 }
 for(int l=1;l<=n;l++){
  for(int i =1;i<=n+1-l;i++){
   int j=i+l-1;
   w[i][j]=w[i][j-1]+p[j]+q[j];
   e[i][j]=INT_MAX;
   for(int r=i;r<=j;r++){
    float t =e[i][r-1]+w[i][j]+e[r+1][j];
    if(t<e[i][j]){
     e[i][j]=t;
     root[i][j]=r;
    }

   }
  }
 }
 cout<<"cost "<<e[1][n]<<endl;
 cout<<"inorder walk "<<endl;
 CONSTRUCT_OPTIMAL_BST(root,1,n);

}

string PALINDROME(string s){
  int n =s.length();
  int left =0;
  int right =0;
  int c[n][n];
  int L=1;
  memset(c,0,sizeof(c));
  for(int i=0;i<n-1;i++){
   c[i][i]=1;
   if(s[i]==s[i+1]){
   if(L==1) {
     L=2;
     left =i;right=i+1;
   }
   c[i][i+1]=2;
   }
  }
  c[n-1][n-1]=1;

  for(int l=3;l<=n;l++){
   for(int i=0;i<=n-l;i++){
    int j =i+l-1;
    if(c[i+1][j-1]>0 && s[i]==s[j]){
     c[i][j] =2+c[i+1][j-1];
     if(c[i][j]>L){
      L =c[i][j];
      left =i;
      right =j;
     }
    }
   }
  }
  cout<<"max size "<<L<<endl;
  cout<<s.substr(left,L)<<endl;
}
float dist(int x1,int y1,int x2,int y2){
  return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void BITONIC_TOURS(vector<vector<int>>& points){
 int n =points.size();
 vector<vector<float>> d(n,vector<float>(n,999.0));
 vector<vector<int>> s(n,vector<int>(n,-1));
 d[0][0]=0.0;
 d[1][0]=d[0][1]=dist(points[0][0],points[0][1],points[1][0],points[1][1]);
 for(int i=2;i<n;i++) {
  d[0][i]=d[0][i-1]+dist(points[i-1][0],points[i-1][1],points[i][0],points[i][1]);
  d[i][0]=d[0][i];
 }
 for(int i=1;i<n;i++){
  for(int j=0;j<=n;j++){
   if((i-1)>=j){
    d[i][j]=d[i-1][j]+dist(points[i-1][0],points[i-1][1],points[i][0],points[i][1]);
    d[j][i]=d[i][j];
    s[i][j]=i-1;
   }else if(j==i ){
    d[i][j]=999.0;

    float temp =0.0;
    for(int k=0;k<i;k++){
     temp =d[k][j]+dist(points[k][0],points[k][1],points[i][0],points[i][1]);
     if(temp<d[i][j]){
      d[i][j]=temp;
      s[i][j]=k;
     }
    }
    d[j][i]=temp;
   }
  }
 }

 cout<<"dist "<<d[n-1][n-1]<<endl;


}
int main(){
 //vector<int> p={0,1,5,8,9,10,17,17,20,24,30};
 //vector<int> r(p.size(),INT_MIN);
 //cout<<"max profit "<<BOTTOM_UP_CUT_ROD(p,p.size()-1)<<endl;

 //vector<int> p={30,35,15,5,10,20,25};
 //cout<<"min multiply times "<<MATRIX_CHAIN_ORDER(p)<<endl;
  /*
  string strA ="ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
  string strB ="GTCGTTCGGAATGCCGTTGCTCTGTAAA";
  cout<<"LCS : "<<LCS_LENGTH(strA,strB)<<endl;
  vector<int> arr={1,2,3,7,4,5};
  LONG_MONOTONIC(arr);
  */
  /*
  vector<float> p ={0,0.15,0.10,0.05,0.10,0.20};
  vector<float> q ={0.05,0.10,0.05,0.05,0.05,0.10};
  OPTIMAL_BST(p,q,p.size()-1);
  */
  /*string str ="whopaibohphobialka";
  PALINDROME(str);
  */
  vector<vector<int>> points ={{0,6},{1,0},{2,3},{5,4},{6,1},{7,5},{8,2}};
  BITONIC_TOURS(points);
 return 0;
}
