#include<iostream>
#include<vector>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<cstring>
using namespace std;
void printArr(vector<int>& nums){
 int n =nums.size();
 cout<<endl;
 for(int i=0;i<n;i++){
   cout<<" "<<nums[i];
 }
 cout<<endl;
}

void COUNTINGSORT(vector<int>& nums,int k){
 vector<int> counts(k+1,0);

 int n =nums.size();

 vector<int> arr(n,0);
 for(int i=0;i<n;i++){
  counts[nums[i]]=counts[nums[i]]+1;
 }
 //cout<<"counts"<<endl;
 //printArr(counts);
 for(int i=1;i<=k;i++){
  counts[i]=counts[i-1]+counts[i];
 }
 //cout<<"counts "<<endl;
 //printArr(counts);
 for(int i=n-1;i>=0;i--){ //for stability

  arr[counts[nums[i]]-1]=nums[i]; // from index 0
  counts[nums[i]]=counts[nums[i]]-1;
 }
 nums.assign(arr.begin(),arr.end());
 return;
}

void printArrs(vector<vector<int>>&nums){
 int m =nums.size();
 int n =nums[0].size();
 cout<<endl;
 for(int i =0;i<n;i++){
  for(int j=0;j<m;j++){
   cout<<(char)(nums[j][i]+'0');
  }
  cout<<endl;
 }
}
void printStrings(vector<string>& nums){
 int n =nums.size();
 cout<<"String "<<endl;
 for(int i=0;i<n;i++){
  cout<<" "<<nums[i];
 }
 cout<<endl;
}
void RADIXSORT_STRING(vector<string>& nums,int k){
  int n =nums.size();
  int m=nums[0].size();
  int len =10;

  //cout<<" k "<<k<<endl;
  for(int i=k-1;i>=0;i--){
   vector<int> counts(len,0);
   vector<string> res(n,"");
   for(int j=0;j<n;j++){
    counts[nums[j][i]-'0'] =counts[nums[j][i]-'0']+1;
   }
   for(int j=1;j<len;j++){
    counts[j]=counts[j]+counts[j-1];
   }
   for(int j=n-1;j>=0;j--){
    res[counts[nums[j][i]-'0']-1]=nums[j];
    counts[nums[j][i]-'0']--;
   }
   nums.clear();
   nums.assign(res.begin(),res.end());
   //printStrings(nums);
  }

}
void BUCKETSORT(vector<float>& nums){
 int n=nums.size();
 //cout<<" n "<<n<<endl;
 vector<vector<float>> dict(n,vector<float>());
 for(int i=0;i<n;i++){
  int temp =floor(nums[i]*n);
  //cout<<" "<<temp<<endl;
  dict[temp].push_back(nums[i]);
 }
 //cout<<"00"<<endl;
 vector<float> res;
 for(int i=0;i<n;i++){
  for(int j=1;j<dict[i].size();j++){
    float key =dict[i][j];
    int k=j-1;
    while(k>=0 && dict[i][k]>key) {
      dict[i][k+1]=dict[i][k];
      k--;
    }
    dict[i][k+1]=key;
  }
 }
 //cout<<"01"<<endl;
 for(int i=n-1;i>=0;i--){
   res.insert(res.begin(),dict[i].begin(),dict[i].end());
 }
 //cout<<"02"<<endl;
 nums.assign(res.begin(),res.end());
}
void printArrfloat(vector<float>& nums){
 int n=nums.size();
 //cout<<endl;
 for(int i=0;i<n;i++){
  //cout<<" "<<nums[i];
 }
 //cout<<endl;
}

void Problem8_1(vector<int>& nums,int k){

  int n =nums.size();
  vector<int> A(k+1,0);
  vector<int> B(k+1,0);
  for(int i=0;i<n;i++){
   A[nums[i]] =A[nums[i]]+1;
   B[nums[i]] =B[nums[i]]+1;
  }
  for(int i=1;i<=k;i++){
   B[i]=B[i-1]+B[i];
  }
  //printArr(A);
  //printArr(B);
  int  i=0;
  vector<int> low(k+1,0);
  vector<int> high(k+1,0);
  for(int i=0;i<=k;i++){
   low[i]=B[i]-A[i];
   high[i]=B[i]-1;
  }
  for(i=0;i<n;){
  // cout<<" nums[i] "<<nums[i]<<" i "<<i<<endl;
  // cout<<" B[nums[i] "<<B[nums[i]]<<endl;

  // cout<<i<<" range ["<<low[nums[i]]<<" "<<high[nums[i]]<<"]"<<endl;
   if(!(i>=low[nums[i]] && i<=high[nums[i]])){

     int temp =nums[B[nums[i]]-1];
  //   cout<<" temp "<<temp<<endl;
     nums[B[nums[i]]-1]=nums[i];
     B[nums[i]]--;
     A[nums[i]]--;
     nums[i]=temp;
   }else i++;
  }
}

void Problem8_3a(vector<string>& nums){
 int len =0;
 int n=nums.size();


 for(int i=0;i<n;i++){
   len =max(len,(int)nums[i].length());
 }
 //cout<<" len "<<len<<endl;
 vector<vector<string>> buckets(len+1,vector<string>());
 for(int i=0;i<n;i++){
 //cout<<"nums[i] "<<nums[i]<<" length "<<nums[i].length()<<endl;
  buckets[nums[i].length()].push_back(nums[i]);
 }
 for(int i=0;i<=len;i++){
  //cout<<"bucket:  "<<i<<endl;
  for(int j=0;j<buckets[i].size();j++){
   //cout<<" "<<buckets[i][j];
  }
  //cout<<endl;
 }
 //cout<<"after buckets"<<endl;
 vector<string> res;
 for(int i=len;i>=1;i--){
   RADIXSORT_STRING(buckets[i],i);
   //cout<<"return "<<endl;
   for(int j=0;j<buckets[i].size();j++){
  //  cout<<" "<<buckets[i][j];
   }
  // cout<<endl;
   res.insert(res.begin(),buckets[i].begin(),buckets[i].end());
 }
// cout<<"99"<<endl;
 nums.assign(res.begin(),res.end());
}

void Problem8_3b(vector<string>& nums){
 if(nums.size()==0) return ;
 vector<vector<string>> buckets(26,vector<string>());
 int n =nums.size();
 for(int i=0;i<n;i++){
   buckets[nums[i][0]-'a'].push_back(nums[i]);
 }
 int counts =0;
 int last_size =0;
 vector<string> res;
 for(int i=0;i<buckets.size();i++){
  counts =0;
  last_size =buckets[i].size();
  if(last_size!=0){
   //cout<<"before "<<endl;
  // printStrings(buckets[i]);
  }
  vector<string>::iterator it =buckets[i].begin();
  for(it=buckets[i].begin();it!=buckets[i].end();){
    if((*it).length()==1){
     counts++;
     buckets[i].erase(it);
    }else{
     (*it) =(*it).substr(1);
     it++;
    }
  }
  if(last_size!=0){
    Problem8_3b(buckets[i]);

    for(int k=0;k<buckets[i].size();k++){
     buckets[i][k] =buckets[i][k].insert(0,1,('a'+i));
    }
    string temp ="";
    temp.insert(0,1,('a'+i));
    buckets[i].insert(buckets[i].begin(),counts,temp);
    //cout<<"after "<<endl;
    //printStrings(buckets[i]);
  }

  res.insert(res.end(),buckets[i].begin(),buckets[i].end());
 }
 nums.clear();
 nums.assign(res.begin(),res.end());

}
void Problem8_4(vector<int>&reds,int rl,int rr,vector<int>&blues ,int bl,int br){
  if(rl==rr || bl==br){
    cout<<"find val paired "<<reds[rl]<<endl;
    return;
  }
  if(rl>rr || bl>br ) return;
  int index = rl +rand()%(rr-rl+1);
  int x =blues[index];
  //partition reds;
  int q =rl,t=rl;
  reds.insert(reds.begin()+rl,1,x);
  for(int j =rl+1;j<=rr+1;j++){
    if(reds[j]<x){
      int temp =reds[j];
      reds[j]=reds[t+1];
      reds[t+1]=reds[q];
      reds[q]=temp;
      q++;t++;
    }else if(reds[j]==x){
     cout<<"find val paired "<<x<<endl;
     int temp =reds[j];
     reds[j]=reds[t+1];
     reds[t+1]=temp;
     t++;
    }
  }
  reds.erase(reds.begin()+q);
  int red_loc =q;
  //partition blues
  q=bl,t=bl;
  blues.insert(blues.begin()+bl,1,x);
  for(int j =bl+1;j<=br+1;j++){
    if(blues[j]<x){
      int temp =blues[j];
      blues[j]=blues[t+1];
      blues[t+1]=blues[q];
      blues[q]=temp;
      q++;t++;
    }else if(blues[j]==x){
     cout<<"find val paired "<<x<<endl;
     int temp =blues[j];
     blues[j]=blues[t+1];
     blues[t+1]=temp;
     t++;
    }
  }
  blues.erase(blues.begin()+q);
  int blue_loc =q;
  Problem8_4(reds,rl,red_loc-1,blues,bl,blue_loc-1);
  Problem8_4(reds,red_loc+1,rr,blues,blue_loc+1,br);

}
int main(){

 vector<int> nums ={9,4,6,0,3,2,6,1,4,2,6,4,8,1,7,0,9};
 vector<string> str2nums ={"12","0","234","17","222","78","9","456","333","1234","4562","4210"};
 vector<string> strs ={"aacc","avx","a","vvs","bb","ab","b","rwa","opsa","abac","abaa"};
 vector<int> reds ={1,3,7,9,0,5,6,2,8,4};
 vector<int> blues={8,4,5,3,1,2,9,0,6,7};
 /*
 vector<string> strs ={"COW","DOG","SEA","RUG","ROW","MOB","BOX","TAB","BAR","EAR","TAR","DIG","BIG","TEA","NOW","FOX"};
 vector<vector<int>> strnums(3,vector<int>(strs.size(),0));
 for(int i=0;i<=2;i++){
   for(int j=0;j<strs.size();j++){
     strnums[i][j]=strs[j][i]-'A';
   }
 }
 */
 //printArr(nums);
 //COUNTINGSORT(nums,9);
 //printArr(nums);
 //printArrs(strnums);
 //RADIXSORT(strnums);
 //printArrs(strnums);


 //vector<float> nums ={0.78,0.17,0.39,0.26,0.72,0.94,0.21,0.12,0.23,0.68};
 //printArrfloat(nums);
 //BUCKETSORT(nums);
 //printArrfloat(nums);
 //printArr(nums);
 //Problem8_1(nums,9);
 //printArr(nums);
// COUNTINGSORT(nums,9);
 //printArr(nums);
 //Problem8_3a(str2nums);
 //cout<<"Numbers "<<endl;
 /*
 for(int i=0;i<str2nums.size();i++){
  cout<<" "<<str2nums[i]<<endl;
 }
 */

 //printStrings(strs);
 //Problem8_3b(strs);
 //printStrings(strs);

 srand((int)(time(NULL)));
 Problem8_4(reds,0,reds.size()-1,blues,0,blues.size()-1);


 return 0;
}
