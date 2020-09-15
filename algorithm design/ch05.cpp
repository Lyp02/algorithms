/*
Divide and Conquer
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<climits>

using namespace  std;
int  merge_and_count(vector<int>& nums,int l,int mid,int r){
  int n1 =mid-l+1;
  int n2 =r -mid;
  int i=l,j=mid+1;
  vector<int> vecs;
  int res =0;
  while(i<=(mid+1) || j<=(r+1)){
   if(i<=mid && j<=r){
    if(nums[i]<=nums[j]) {

    vecs.push_back(nums[i]);
    i++;}
    else {
     res =res +(mid-i+1);
     vecs.push_back(nums[j]);
     j++;
    }
   }else if(i>mid){
    for(int k=j;k<=r;k++) vecs.push_back(nums[k]);
    break;
   }else{
    for(int k=i;k<=mid;k++) vecs.push_back(nums[k]);
    break;
   }
  }
  for(int k=0;k<=r-l;k++) nums[l+k]=vecs[k];
  return res;
}

int sort_and_count(vector<int>& nums,int l,int r){
 if(r==l) return 0;
 if(r==l+1){
  if(nums[l]>nums[r]) {
   int temp =nums[l];
   nums[l]=nums[r];
   nums[r]=temp;
   return 1;
  }
  else return 0;
 }
 int mid =l+(r-l)/2;
 int left =sort_and_count(nums,l,mid);
 int right =sort_and_count(nums,mid+1,r);
 int mid_count =merge_and_count(nums,l,mid,r);
 cout<<"left "<<left<<" right "<<right<<" mid_count "<<mid_count<<endl;
 return (left +right +mid_count);
}


struct cmpx{
 bool operator()(pair<int,pair<float,float>> a,pair<int,pair<float,float>> b){
  return a.second.first < b.second.first;
 }
};

struct cmpy{
 bool operator()(pair<int,pair<float,float>> a,pair<int,pair<float,float>> b){
  return a.second.second < b.second.second;
 }
};

pair<int,int> closet_pair_rec(vector<vector<float>>&P,vector<int>&Px,vector<int>&Py){
  int n =Px.size();
  if(n<=3){
   int left =-1,right =-1;
   float d =99999.0;
   for(int i=0;i<n-1;i++){
    for(int j=i+1;j<n;j++){
     int w =Px[i];
     int m =Px[j];
     float temp =1.0*(P[w][0]-P[m][0])*(P[w][0]-P[m][0]) +1.0*(P[w][1]-P[m][1])*(P[w][1]-P[m][1]);
     if(temp<d){
      d =temp;
      left =w;
      right =m;
     }
    }
   }
   pair<int,int> temp =make_pair(left,right);
 //  cout<<"base case "<<temp.first<<" "<<temp.second<<endl;
   return temp;
  }
 // cout<<"@@@"<<endl;
  vector<vector<float>>L;
  vector<vector<float>>R;
  vector<int>Lx;
  vector<int>Ly;
  vector<int>Rx;
  vector<int>Ry;
  vector<int> mask(n,0);
  int xlimit =INT_MAX;
  vector<float> temp(2,0.0);
  for(int i=0;i<n;i++){
   int index =Px[i];
   if(i<=((n-1)/2)){
   mask[index]=1;
   xlimit =P[index][0];
 //  cout<<"$$$"<<endl;
   temp[0]=P[index][0];temp[1]=P[index][1];
   L.push_back(temp);
   Lx.push_back(index);
   }else{
   temp[0]=P[index][0];temp[1]=P[index][1];
   R.push_back(temp);
   Rx.push_back(index);
   }
  }
 // cout<<"###"<<endl;
  for(int i=0;i<n;i++){
  if(mask[Py[i]]==1){
   Ly.push_back(Py[i]);
  }else{
   Ry.push_back(Py[i]);
  }
  }
  //cout<<"***"<<endl;
  pair<int,int> left_pair =closet_pair_rec(P,Lx,Ly);
  pair<int,int> right_pair =closet_pair_rec(P,Rx,Ry);
 // cout<<"%%%"<<endl;
  int l1 =left_pair.first,r1=left_pair.second;
 // cout<<"&&&"<<endl;
  float d1 =1.0*((P[l1][0]-P[r1][0])*(P[l1][0]-P[r1][0])+(P[l1][1]-P[r1][1])*(P[l1][1]-P[r1][1]));
 // cout<<"~~~"<<endl;
  int l2 =right_pair.first;
  int r2 =right_pair.second;
  float d2 =1.0*((P[l2][0]-P[r2][0])*(P[l2][0]-P[r2][0])+(P[l2][1]-P[r2][1])*(P[l2][1]-P[r2][1]));
  float dist =min(d1,d2);
 // cout<<"^^^"<<endl;
  vector<int> Sy;
  for(int i=0;i<n;i++){
   int index =Py[i];
   if(P[index][0]>(xlimit-dist) && P[index][0]<(xlimit+dist)){
    Sy.push_back(index);
   }
  }
  int len_max =15;
  int len =15;
  float dist_cross =99999.0;
  int left_cross=-1,right_cross=-1;
  for(int i=0;i<Sy.size()-1;i++){
   int w =Sy[i];
   for(int j=i+1;j<(i+16);j++){
    if(j>=Sy.size()) break;
    int m =Sy[j];
    float temp =1.0*((P[w][0]-P[m][0])*(P[w][0]-P[m][0])+(P[w][1]-P[m][1])*(P[w][1]-P[m][1]));
    if(dist_cross > temp){
     dist_cross =temp;
     left_cross =w;
     right_cross =m;
    }
   }
  }
  if(dist_cross<dist){
   return make_pair(left_cross,right_cross);
  }else if(dist==d1){
   return make_pair(l1,r1);
  }else return make_pair(l2,r2);

}
void closet_pair(vector<vector<float>>& P){
 int n =P.size();
 vector<pair<int,pair<float,float>>> vecs;
 for(int i=0;i<n;i++) vecs.push_back(make_pair(i,make_pair(P[i][0],P[i][1])));
 vector<int> Px(n,-1);
 vector<int> Py(n,-1);
 sort(vecs.begin(),vecs.end(),cmpx());
 for(int i=0;i<n;i++) Px[i]=vecs[i].first;
 sort(vecs.begin(),vecs.end(),cmpy());
 for(int i=0;i<n;i++) Py[i]=vecs[i].first;

 pair<int,int> points =closet_pair_rec(P,Px,Py);
 cout<<"closet pair "<<"<"<<P[points.first][0]<<","<<P[points.first][1]<<">, "<<"<"<<P[points.second][0]<<","<<P[points.second][1]<<">"<<endl;

}
int main(){
 vector<int> nums={5,2,4,7,1,3,2,6};
 //cout<<"inversions "<<endl<<sort_and_count(nums,0,nums.size()-1)<<endl;

 vector<vector<float>> P={{-2,0},{-1,-1},{-4,-3},{2,4},{3,2},{4,7},{8,9},{1,2}};
 closet_pair(P);
 return 0;
}
