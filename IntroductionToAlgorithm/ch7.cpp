#include<iostream>
#include<vector>

using namespace std;

void printArr(vector<int>& nums){
 int  n =nums.size();
 cout<<endl;
 for(int i=0;i<n;i++){
  cout<<" "<<nums[i];
 }
 cout<<endl;
}

int Partition(vector<int>& nums,int p,int r){
 int x =nums[r];
 int i =p-1;
 for(int j=p;j<r;j++){
  if(nums[j]<=x){
    i =i+1;
    int temp =nums[i];
    nums[i]=nums[j];
    nums[j]=temp;
  }
 }
 int temp =nums[i+1];
 nums[i+1]=nums[r];
 nums[r] =temp;
 return (i+1);
}

void QUICKSORT(vector<int>& nums,int p,int r){
  if(p>r) return;
  int q = Partition(nums,p,r);
  QUICKSORT(nums,p,q-1);
  QUICKSORT(nums,q+1,r);
}
int RANDOMIZED_PARTITION(vector<int>&nums,int p,int r){
  int q =p+rand()%(r-p+1);
  int temp =nums[r];
  nums[r] =nums[q];
  nums[q]=temp;
  return Partition(nums,p,r);
}
void RANDOMIZED_QUICKSORT(vector<int>&nums,int p,int r){
 if(p>r) return;
 int q =RANDOMIZED_PARTITION(nums,p,r);
 RANDOMIZED_QUICKSORT(nums,p,q-1);
 RANDOMIZED_QUICKSORT(nums,q+1,r);
}

void QUICKSORT_INSERTIONSORT(vector<int>&nums,int p,int r,int k){
  if((p+k)<=r){
    for(int i=p+1;i<=r;i++){
     int j=i-1;
     int key =nums[i];
     while(j>=p && nums[j]>key) {nums[j+1]=nums[j];j--;}
     nums[j+1]=key;
    }
    return;

  }
  else{
    int q =RANDOMIZED_PARTITION(nums,p,r);
    QUICKSORT_INSERTIONSORT(nums,p,q-1,k);
    QUICKSORT_INSERTIONSORT(nums,q+1,r,k);
    return;
  }

}

void QUICKSORT_MEDIAN(vector<int>& nums, int p, int r){
  if((p+2)<=r){
     for(int i=p+1;i<=r;i++){
     int j=i-1;
     int key =nums[i];
     while(j>=p && nums[j]>key) {nums[j+1]=nums[j];j--;}
     nums[j+1]=key;
    }
    return;
  }
  //in pratical need to ensure both unequal
  int a =p+rand()%(r-p+1);
  int b =p+rand()%(r-p+1);
  int c =p+rand()%(r-p+1);
  int median =a;
  if(nums[b]<=nums[c] && nums[c]<=nums[a]) median= c;
  if(nums[c]<=nums[b] && nums[b]<=nums[a]) median= b;
  int temp =nums[r];
  nums[r] =nums[median];
  nums[median]=temp;
  QUICKSORT_MEDIAN(nums,p,median-1);
  QUICKSORT_MEDIAN(nums,median+1,r);

}

int HOARE_PARTITION(vector<int>&nums,int p,int r){
 int i =p;
 int j =r+1;
 int x =nums[p];
 while(1){
  do{
    j--;
  }while(nums[j]>x);
  do{
   i++;
  }while(nums[i]<x);
  if(i<j){
   int temp =nums[i];
   nums[i]=nums[j];
   nums[j]=temp;
  }else break;;
 }
 int temp =nums[j];
 nums[j]=nums[p];
 nums[p]=temp;
 return j;
}

void QUICKSORT_HOARE(vector<int>& nums, int p, int r){
  if(p>r) return;
  int q =HOARE_PARTITION(nums,p,r);
  QUICKSORT_HOARE(nums,p,q-1);
  QUICKSORT_HOARE(nums,q+1,r);
  return;

}

vector<int> PARTITION3DIV(vector<int>&nums,int p,int r){
  int q=p;
  int t=p;
  int j =p;
  int x =nums[p];
  for(int i=p+1;i<=r;i++){
   if(nums[i]<x){
    int temp =nums[i];
    nums[i]=nums[t+1];
    nums[t+1]=nums[q];
    nums[q]=temp;
    t++;
    q++;
   }else if(nums[i]==x){
    int temp =nums[i];
    nums[i]=nums[t+1];
    nums[t+1]=temp;
    t++;
   }
  }
  vector<int> res={q,t};
  return res;
}

void QUICKSORT3DIV(vector<int>& nums, int p, int r){
  if(p>r) return;
  vector<int> res =PARTITION3DIV(nums,p,r);
  int q =res[0];
  int t =res[1];
  QUICKSORT3DIV(nums,p,q-1);
  QUICKSORT3DIV(nums,t+1,r);
}

void TAIL_RECURSIVE_QUICKSORT(vector<int>& nums,int p,int r){
  while(p<=r){
    int q =Partition(nums,p,r);
    TAIL_RECURSIVE_QUICKSORT(nums,p,q-1);
    p=q+1;
  }
}

void TAIL_RECURSIVE_QUICKSORT2(vector<int>& nums, int p, int r){
  while(p<=r){
    int q =Partition(nums,p,r);
    if((q-p)<(r-q)){
      TAIL_RECURSIVE_QUICKSORT2(nums,p,q-1);
      p=q+1;
    }else{
      TAIL_RECURSIVE_QUICKSORT2(nums,q+1,r);
      r=q-1;
    }

  }
}
void printIntervals(vector<vector<int>>&nums,int p,int r){
 cout<<endl;
 for(int i=p;i<=r;i++){
   cout<<"   ["<<nums[i][0]<<" , "<<nums[i][1]<<"]";
 }
 cout<<endl;
}
vector<int> FUZZY_PARTITION(vector<vector<int>>&nums,int p,int r){
 int low =nums[p][0];
 int high =nums[p][1];
 int q=p,t=p;
 for(int i=p+1;i<=r;i++){
  if(nums[i][1]<low){
    int temp_low =nums[q][0];
    int temp_high =nums[q][1];
    nums[q][0]=nums[i][0];
    nums[q][1]=nums[i][1];
    nums[i][0]=temp_low;
    nums[i][1]=temp_high;
    q++;
    t++;
  }//else if((nums[i][0]<=high &&nums[i][1]>=high) || (nums[i][1]>=low && nums[i][0]<=low) || (nums[i][0]<=low && nums[i][1]>=high)){
    else if(nums[i][1]>=low || nums[i][0]<=high){
    low =max(low,nums[i][0]);
    high =min(nums[i][1],high);
    int temp_low =nums[t+1][0];
    int temp_high =nums[t+1][1];
    nums[t+1][0]=nums[i][0];
    nums[t+1][1]=nums[i][1];
    nums[i][0]=temp_low;
    nums[i][1]=temp_high;
    t++;
  }
 }
 vector<int> res ={q,t};
 return res;
}
void FUZZYSORT(vector<vector<int>>&nums,int p,int r){
 if(p>r) return;
 vector<int> res =FUZZY_PARTITION(nums,p,r);

 int q =res[0];
 int t =res[1];
 //printIntervals(nums,p,q-1);
 cout<<"overlapping: "<<endl;
 printIntervals(nums,q,t);

 //printIntervals(nums,t+1,r);
 FUZZYSORT(nums,p,q-1);
 FUZZYSORT(nums,t+1,r);
}

int main(){
 //vector<int>nums ={-1,3,2,4,2,4,1,8,2,-2,4,6};
 //printArr(nums);
 //RANDOMIZED_QUICKSORT(nums,0,nums.size()-1);
 //int k=3;
 //QUICKSORT_INSERTIONSORT(nums,0,nums.size()-1,k);
 //QUICKSORT_MEDIAN(nums,0,nums.size()-1);
 //HOARE_PARTITION(nums,0,nums.size()-1);
 //TAIL_RECURSIVE_QUICKSORT2(nums,0,nums.size()-1);
 //printArr(nums);
 vector<vector<int>> nums ={{-1,2},{0,1},{-4,-2},{3,5},{6,7},{8,11},{13,14},{15,17},{16,17}};
 printIntervals(nums,0,nums.size()-1);
 FUZZYSORT(nums,0,nums.size()-1);
 printIntervals(nums,0,nums.size()-1);

 return 0;
}
