#include<iostream>
#include<vector>
#include<climits>

using namespace std;

void print(vector<int> & nums){
  int n =nums.size();
  cout<<endl;
  for(int i=0;i<n;i++){
    cout<<" "<<nums[i];
  }
  cout<<endl;
}

void insertSort(vector<int> & nums){
 int n=nums.size();
 if(n==0 || n==1) return;
 for(int i=1;i<n;i++){
   int j =i-1;
   int key =nums[i];
   for(j=i-1;j>=0 && nums[j]>key;j--){
     nums[j+1]=nums[j];
   }
   nums[j+1]=key;
  }
  return;
}

void selectSort(vector<int> & nums){
 int n =nums.size();
 if(n==0 || n==1) return;
 int val =0;
 int index =0;
 for(int i=0;i<n-2;i++){
    val =nums[i];
    index =i;
   for(int j=i;j<n;j++){
     if(val>nums[j]){
       index =j;
       val =nums[j];
     }
   }
   int temp =nums[i];
   nums[i] =nums[index];
   nums[index] =temp;
 }
 return;
}
int Merge(vector<int>& nums,int p,int q,int r){
  vector<int> left;
  vector<int> right;
  left.assign(nums.begin()+p,nums.begin()+q+1);
  right.assign(nums.begin()+q+1,nums.begin()+r+1);
  int i=0,j=0;
  left.push_back(INT_MAX);
  right.push_back(INT_MAX);
  int k=p;
  int counts =0;
  while(k<=r){
    if(left[i]<right[j]){
     nums[k++]=left[i++];
    }
    else {
      counts++;
      nums[k++]=right[j++];
    }
  }
  return counts;
}

void mergeSort(vector<int>& nums,int p,int r){
  if(p>=r) return;
  int q =p+(r-p)/2;
  mergeSort(nums,p,q);
  mergeSort(nums,q+1,r);
  Merge(nums,p,q,r);
}

int  binarySearch(vector<int>& nums,int p,int r,int key){
  if(p>=r) return r;
  int q =p +(r-p)/2;
  if(nums[q]>=key) return binarySearch(nums,p,q,key);
  else return binarySearch(nums,q+1,r,key);
}

bool findTwoSumInSet(vector<int> & nums,int sum){
  vector<int> nums2;
  int n =nums.size();
  if(n==0 || n==1) return false;
  for(int i=0;i<n;i++){
    nums2.push_back(sum-nums[i]);
  }
  mergeSort(nums,0,n-1);
  mergeSort(nums2,0,n-1);
  int  k=0;
  nums.push_back(INT_MAX);
  nums2.push_back(INT_MAX);
  vector<int> res(2*n,0);
  int i=0,j=0;
  while(k<(2*n)){
    if(nums[i]<nums2[j]) res[k++]=nums[i++];
    else res[k++]=nums2[j++];
  }
  for(int i=1;i<(2*n);i++){
   if(res[i]==res[i-1]) return true;
  }
  return false;
}

void bubbleSort(vector<int>& nums){
  int n =nums.size();
  int temp =0;
  for(int i=0;i<n-1;i++){
   for(int j=n-1;j>=i+1;j--){
     if(nums[j]<nums[j-1]){
       temp =nums[j];
       nums[j] =nums[j-1];
       nums[j-1]=temp;
     }
   }
  }
  return;
 }

 int inversCounts(vector<int>& nums,int p,int r){
   if(p>=r) return 0;
   int q =p +(r-p)/2;
   int res =0;
   res =inversCounts(nums,p,q);
   res =res + inversCounts(nums,q+1,r);
   res =res +Merge(nums,p,q,r);
   return res;


 }

 void shellSort(vector<int>& nums){
  int h=1;
  int n=nums.size();
  while(h<(n/3)){
    h =3*h+1;
  }
  while(h>=1){
    for(int i=h;i<n;i++){
     int j=i-h;
     int key =nums[i];
     while(j>=0 && nums[j]>key){
       nums[j+h]=nums[j];
       j =j-h;
     }
     nums[j+h]=key;
    }
    h =h/3;
  }
return;
 }

int main(){
 vector<int> nums ={2,3,8,6,1,5,0,-7,2,5,1,4,2,3,-9};
 //insertSort(nums);
 //selectSort(nums);
 //mergeSort(nums,0,nums.size()-1);
 //bubbleSort(nums);
 //int index =binarySearch(nums,0,nums.size(),2);
 //cout<<" index "<<index<<endl;
 //cout<<" "<<findTwoSumInSet(nums,13);
 shellSort(nums);
 print(nums);
 //cout<<" "<<inversCounts(nums,0,nums.size()-1);
 return 0;
}
