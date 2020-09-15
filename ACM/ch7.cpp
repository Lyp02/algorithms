/*
Permutation
*/

#include<iostream>
#include<algorithm>

using namespace std;


void print_permutation(int n,int *A,int* P,int cur){
  if(cur==n){
   cout<<endl;
   for(int i=0;i<n;i++) cout<<" "<<A[i];
   cout<<endl;
   return;
  }
  for(int i=0;i<n;i++){
   if(!i && P[i]==P[i-1]) continue;
   int c1=0,c2=0;
   for(int k=0;k<n;k++) if(P[k]==P[i]) c1++;
   for(int j=0;j<cur;j++){
    if(A[j]==P[i]) c2++;
   }
   if(c2<c1){
    A[cur]=P[i];
    print_permutation(n,A,P,cur+1);
   }

  }
  return;
}

void  print_permutation2(int n, int* P){
  cout<<endl;
  do{
    for(int i=0;i<n;i++) cout<<" "<<P[i];
    cout<<endl;
  }while(next_permutation(P,P+n));
  return ;

}

void print_subset(int n,int* A,int cur){
  //must be sorted first
  for(int i=0;i<cur;i++) cout<<" "<<A[i];
  cout<<endl;
  int s=(cur)?A[cur-1]+1:0;
  for(int i=s;i<n;i++){
   A[cur]=i;
   print_subset(n,A,cur+1);
  }
  return;

}

void print_subset2(int n,int*A,int*P,int cur){
 if(cur==n){
  for(int i=0;i<n;i++){
   if(A[i]==1) cout<<" "<<P[i];
  }
  cout<<endl;
  return;
 }
 A[cur]=1;
 print_subset2(n,A,P,cur+1);
 A[cur]=0;
 print_subset2(n,A,P,cur+1);
 return;
}
void print_subset3(int n){
 for(int i=0;i<(1<<n);i++){
  for(int j=0;j<n;j++){
   if(i&(1<<j))cout<<" "<<(j+1);
  }
  cout<<endl;
 }
}
int main(){
 int N =8;
 int A[N]={0,0,0,0,0,0,0,0};
 int P[N]={1,2,3,4,5,6,7,8};
 //print_permutation2(N,P);
 sort(P,P+N);
//print_subset(N,P,0);
// print_subset2(N,A,P,0);
print_subset3(8);
 return 0;
}




