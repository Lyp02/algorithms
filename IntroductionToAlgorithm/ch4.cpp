#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

int randomNum(int a,int b){
  if(a==b) return a;
  float mid =0.5*(a+b);
  int mask =rand()%2;
  if(mask==0) return randomNum(a,floor(mid));
  else return randomNum(ceil(mid),b);
}

void permuteBySorting(vector<int>&A){
  if(n==1) return;
  int n =A.size();
  vector<int> B(n,0);
  for(int i=0;i<n;i++) B[i]=rand()%(n*n*n);

  for(int i=1;i<n;i++){
   int key =B[i];
   int val =A[i];
   int j=i-1;
   while(j>=0 && B[j]>key){
     B[j+1]=B[j];
     A[j+1]=A[j];
     j--;
   }
   B[j+1]=key;
   A[j+1]=val;
  }
  return;

}

void randomizeInPlace(vector<int>& A){
  int n =A.size();
  int temp =0;
  for(int i=0;i<n;i++){
    index =randomNum(i,n-1);
    temp =A[index];
    A[index]=A[i];
    A[i]=temp;
  }
  return;
}
set<int> randomSample(int m,int n){
  set<int> res;
  if(m==0) return res;
  else res =randomSample(m-1,n-1);
  int i =randomNum(1,n);
  if(res.count(i)>0) res.insert(n);
  else res.insert(i);
  return res;

}
int main(){
  srand((int)time(NULL));

  return 0;
}
