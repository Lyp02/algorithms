#include<iostream>
#include<vector>
#include<climits>
#include<set>
#include<ctime>
#include<cstdlib>
#include<algorithm>
using namespace std;
vector<int> Problem9_1_1(vector<int>& nums ,int p,int r){
  if(p==r){
    vector<int> res={nums[p],nums[p]};
    return res;
  }
  if((p+1)==r){
    int a =max(nums[p],nums[r]);
    int b =min(nums[p],nums[r]);
    vector<int> res={b,a};
    return res;
  }
  int q =p+(r-p)/2;
  int index1 =-1;
  int val1 =INT_MAX;
  int index2 =-1;
  int val2 =INT_MAX;
  for(int i=p;i<=r;i++){
    if(i<=q && nums[i]<val1){
      val1 =nums[i];
      index1 =i;
    }
    if(i>q && nums[i]<val2){
     val2 =nums[i];
     index2 =i;
    }
  }
vector<int> res;

if(val1<val2){
  res =Problem9_1_1(nums,p,q);
  if(res[1]>val2){
    res[1]=val2;
    return res;
  }
}else{
   res =Problem9_1_1(nums,q+1,r);
   if(res[1]>val1){
     res[1]=val1;
     return res;
   }
}
return res;
}
void printArrs(vector<int>& nums){
  cout<<endl;
  for(int i=0;i<nums.size();i++){
   cout<<" "<<nums[i];
  }
  cout<<endl;
}


void printArrs(vector<int>& nums,int p,int r){
  cout<<endl;
  for(int i=p;i<=r;i++){
   cout<<" "<<nums[i];
  }
  cout<<endl;
}

vector<int> Problem9_1_2(vector<int>& nums){
  set<int> max_cnd;
  set<int> min_cnd;
  vector<int> res;
  if(nums.size()==1){
   res.push_back(nums[0]);
   res.push_back(nums[0]);
   return res;
  }
  if(nums.size()==2){
   res.push_back(max(nums[0],nums[1]));
   res.push_back(min(nums[0],nums[1]));
   return res;
  }
  for(int i=0;i<nums.size()-1;i=i+2){
    max_cnd.insert(max(nums[i],nums[i+1]));
    min_cnd.insert(min(nums[i],nums[i+1]));
  }
  if(nums.size()%2==1) max_cnd.insert(nums[nums.size()-1]);
  set<int>::iterator it;
  int max_val =INT_MIN;
  int min_val =INT_MAX;
  for(it=max_cnd.begin();it!=max_cnd.end();it++){
    if(max_val<(*it)) max_val=*it;
  }
  for(it=min_cnd.begin();it!=min_cnd.end();it++){
    if(min_val>(*it)) min_val=*it;
  }
  res.push_back(max_val);
  res.push_back(min_val);
  return res;
}

int RANDOMIZED_PARTITION(vector<int>& nums,int p,int r){
  int index = p + rand()%(r-p+1);
  int temp =nums[r];
  nums[r] =nums[index];
  nums[index] =temp;
  int x =nums[r];
  int i =p-1;
  for(int j=p;j<=r-1;j++){
    if(nums[j]<=x){
      int temp =nums[j];
      nums[j]=nums[i+1];
      nums[i+1]=temp;
      i++;
    }
  }
  temp =nums[r];
  nums[r]=nums[i+1];
  nums[i+1]=temp;
  return (i+1);
}

int RANDOMIZED_SELECT(vector<int>& nums,int p,int r,int k){
  if(p==r) return nums[p];
  int q =RANDOMIZED_PARTITION(nums,p,r);
  int counts =q-p+1;
  if(counts==k) return nums[q];
  else if(counts>k) return RANDOMIZED_SELECT(nums,p,q-1,k);
  else return RANDOMIZED_SELECT(nums,q+1,r,k-counts);
}

int RANDOMIZED_SELECT_LOOP(vector<int>& nums, int p, int r, int k){
  while(p!=r){
   int q =RANDOMIZED_PARTITION(nums,p,r);
   int counts =q-p+1;
   if(counts==k) return nums[q];
   if(counts>k){
     r =q-1;
   }else{
    p=q+1;
    k=k-counts;
   }
  }
  return nums[p];
}

int PARTITION_BY_VAL(vector<int>& nums,int p,int r,int x){


  int i =p-1;
  int once =0;
  int temp =0;
  for(int j=p;j<=r-1;j++){
    if(nums[j]<=x){
      if(nums[j]==x && once==0){
        temp =nums[r];
        nums[r]=nums[j];
        nums[j]=temp;
        once =1;
        j =j-1;
        continue;
      }
      temp =nums[j];
      nums[j]=nums[i+1];
      nums[i+1]=temp;
      i++;
    }
  }
  //printArrs(nums);
  temp =nums[r];
  nums[r]=nums[i+1];
  nums[i+1]=temp;
  //cout<<"index: "<<(i+1)<<" val: "<<x<<endl;
  //printArrs(nums);
  return (i+1);
}

int WORSE_CASE_SELECT_LINEAR(vector<int>& nums,int p,int r,int k){
  if((r-p)<5){
   sort(nums.begin()+p,nums.begin()+r+1);
   return nums[p+k-1];
  }
  int N =(r-p+1)/5;
  int len =N;
  if((r-p+1)%5!=0) len=N+1;
  vector<int> medians;
  vector<vector<int>> groups(len,vector<int>());
  for(int i=0;i<N;i++){
   groups[i].assign(nums.begin()+p+i*5,nums.begin()+p+i*5+5);
   sort(groups[i].begin(),groups[i].end());
   //cout<<"size "<<groups[i].size()<<endl;
   medians.push_back(groups[i][2]);
  }
  if(len!=N){
   groups[N].assign(nums.begin()+p+5*N,nums.begin()+p+r+1);
   sort(groups[N].begin(),groups[N].end());
   medians.push_back(groups[N][(0+groups[N].size()-1)/2]);
  }
  int median =WORSE_CASE_SELECT_LINEAR(medians,0,medians.size()-1,(medians.size()+1)/2);
  //cout<<"before "<<median<<endl;
  int q =PARTITION_BY_VAL(nums,p,r,median);
  //cout<<"after"<<nums[q]<<endl;
  int  counts= q-p+1;
  if(k==counts) return nums[q];
  else if(k<counts) return WORSE_CASE_SELECT_LINEAR(nums,p,q-1,k);
  else return WORSE_CASE_SELECT_LINEAR(nums,q+1,r,k-counts);


}

void KTH_QUANTILES(vector<int>& nums,int p,int r,int k,int m ,vector<int>& res){
  if(r==p) return;
  if((r-p+1)<=m) return;
  int  n =r-p+1;

  //cout<<endl;
  if(k%2==0){
      //cout<<"p "<<p<<" r "<<r<<" k "<<k<<" m "<<m<<endl;
      int median =WORSE_CASE_SELECT_LINEAR(nums,p,r,(1+n)/2);
       printArrs(nums,p,r);
      int q =PARTITION_BY_VAL(nums,p,r,median);
      cout<<" index "<<(1+n)/2<<endl;
      printArrs(nums,p,r);
      cout<<"nums "<<nums[q]<<" "<<median<<" q "<<q<<endl;
      res.push_back(median);
      KTH_QUANTILES(nums,p,q,k/2,m,res);
      KTH_QUANTILES(nums,q+1,r,k/2,m,res);
  }else{
       int key=0,q=0;
      if(m%2==0){

        key =WORSE_CASE_SELECT_LINEAR(nums,p,r,(1+n)/2+(m/2));
        q =PARTITION_BY_VAL(nums,p,r,key);
        res.push_back(key);
        KTH_QUANTILES(nums,p,q,(k/2)+1,m,res);
        KTH_QUANTILES(nums,q+1,r,(k/2),m,res);
      }else{
        //cout<<"p "<<p<<" r "<<r<<" k "<<k<<" m "<<m<<endl;
        key =WORSE_CASE_SELECT_LINEAR(nums,p,r,(1+n)/2+((m-1)/2));
        q =PARTITION_BY_VAL(nums,p,r,key);
        res.push_back(key);
        KTH_QUANTILES(nums,p,q,(k/2)+1,m,res);
        KTH_QUANTILES(nums,q+1,r,(k/2),m,res);
      }
  }

}

int Problem9_3_8(vector<int>& A, int p1,int r1,vector<int>&B,int p2,int r2,int n){
  if(p1==r1) return A[p1];
  if(p2==r2) return B[p2];
  int midA =WORSE_CASE_SELECT_LINEAR(A,p1,r1,(1+n)/2);
  int midB =WORSE_CASE_SELECT_LINEAR(B,p2,r2,(1+n)/2);
  int q1 =PARTITION_BY_VAL(A,p1,r1,midA);
  int q2 =PARTITION_BY_VAL(B,p2,r2,midB);
  if(midA==midB) return midA;
  else if(midA<midB) return Problem9_3_8(A,q1+1,r1,B,p2,q2,n/2);
  else return Problem9_3_8(A,p1,q1,B,q2+1,r2,n/2);
}
void Problem9_3_7(vector<int>&nums,int k,vector<int>& res){
  int n =nums.size();
  int p=0,r=n-1;
  int key =WORSE_CASE_SELECT_LINEAR(nums,p,r,(n-k)/2);
  int q =PARTITION_BY_VAL(nums,p,r,key);
  int key2 =WORSE_CASE_SELECT_LINEAR(nums,q+1,r,k);
  int q2 =PARTITION_BY_VAL(nums,q+1,r,key2);
  res.assign(nums.begin()+p+q+1,nums.begin()+p+q2+1);
}

int main(){
 srand((int)time(NULL));
 vector<int> nums={11,2,-1,4,-2,7,9,-3,0,6,-7,8};
 vector<int>nums2={-9,0,3,2,4,-5,1,9,32,22,13,7};
 vector<int> res;
 //printArrs(nums);
 //vector<int> temp=Problem9_1_1(nums,0,nums.size()-1);
 //vector<int> temp =Problem9_1_2(nums);

 //printArrs(nums2);
 //cout<<WORSE_CASE_SELECT_LINEAR(nums2,0,nums2.size()-1,(1+6)/2)<<endl;
 //sort(nums2.begin(),nums2.end());
 //printArrs(nums2);

 /*
 vector<int> res;
 int p =0,r =nums.size()-1,k=2,m=nums.size()/2;
 KTH_QUANTILES(nums,p,r,k,m,res);
 sort(nums.begin(),nums.end());
 printArrs(nums);
 cout<<endl;
 printArrs(res);
 sort(res.begin(),res.end());
 printArrs(res);
 */
 /*
 int p1=0,p2=0,r1=nums.size()-1,r2=nums2.size()-1,n=nums.size();
 cout<<"mid "<<Problem9_3_8(nums,p1,r1,nums2,p2,r2,n)<<endl;
 nums.insert(nums.end(),nums2.begin(),nums2.end());
 sort(nums.begin(),nums.end());
 printArrs(nums);
 */

 return 0;
}
