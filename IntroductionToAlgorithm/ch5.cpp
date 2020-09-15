#include<iostream>
#include<climits>
#include<vector>
#include<queue>
#include<time.h>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace  std;

struct Node{
    int from;
    int val;
    bool operator > (const Node &x) const{
      return val>x.val;
    }
};

void MAX_HEAPIFY(vector<int>& nums,int& len ,int i ){

  int l =2*i;
  int r =2*i+1;
  int largest =-1;

  if(l<=len && nums[l]>nums[i]) largest =l;
  else largest =i;
  if(r<=len && nums[r]>nums[largest]) largest =r;

  if(largest!=i){

   int temp =nums[i];
   nums[i] =nums[largest];
   nums[largest]=temp;
   MAX_HEAPIFY(nums,len,largest);
  }

}

void  MIN_HEAPIFY(vector<int>& nums,int& len,int i){
  int l =2*i;
  int r =2*i+1;
  int smallest = i;
  if(l<=len  && nums[l]<nums[i]) smallest =l;
  else smallest=i;
  if(r<=len && nums[r]<nums[smallest]) smallest=r;

  if(smallest!=i){
    int temp =nums[i];
    nums[i]=nums[smallest];
    nums[smallest]=temp;
    MIN_HEAPIFY(nums,len,smallest);
  }

}

void printArr(vector<int>& nums){
 int n =nums.size();
 cout<<endl;
 for(int i=0;i<n;i++){
  cout<<" "<<nums[i];
 }
 cout<<" "<<endl;
}

void MAX_HEAPIFY_LOOP(vector<int>& nums, int& len, int i){
   int l =2*i;
   int r =2*i +1;
   int largest =-1;

   while(largest!=i){
     l =2*i;
     r =2*i+1;
     if(l<=len && nums[l]>nums[i]) largest=l;
     else largest=i;
     if(r<=len && nums[r]>nums[largest]) largest=r;
     if(largest!=i){
       int temp =nums[i];
       nums[i] =nums[largest];
       nums[largest]=temp;
       i =largest;
     }

   }

}

void BUILD_MAX_HEAP(vector<int>& nums){
  int len =nums.size()-1;
  for(int i=(len/2);i>=1;i--){
   MAX_HEAPIFY(nums,len,i);
  }

}

void HEAPSORT(vector<int>& nums){
  int n =nums.size();
  int len =n-1;
  BUILD_MAX_HEAP(nums);
  printArr(nums);
  for(int i=len;i>=1;i--){
   int temp =nums[i];
   nums[i]=nums[1];
   nums[1]=temp;
   len--;
   MAX_HEAPIFY(nums,len,1);
  }
}

int HEAP_MAXIMUM(vector<int>& nums,int& len){
  return nums[1];
}

int HEAP_EXTRACT_MAX(vector<int>& nums,int& len){
  if(len<0) {
   cout<<"underflow "<<endl;
   return INT_MIN;
  }
  int val =nums[1];
  nums[1]=nums[len];
  len--;
  nums.pop_back();
  MAX_HEAPIFY(nums,len,1);
  return val;

}
void HEAP_INCREASE_KEY(vector<int>& nums,int i,int key,int& len){
  if(nums[i]>key){
    cout<<"new key is smaller than current key";
    return;
  }
  cout<<"nums[i] "<<nums[i]<<"key "<<key<<endl;
  nums[i]=key;
  while(i>1 && nums[i/2]<nums[i]){

     int temp =nums[i/2];
     nums[i/2]=nums[i];
     nums[i] =temp;


   i=i/2;
  }

}

void MAX_HEAP_INSERT(vector<int>& nums,int key,int& len){
  len++;
  nums.push_back(INT_MIN);
  cout<<" nums.size() "<<nums.size()<<" len "<<len<<endl;
  HEAP_INCREASE_KEY(nums,len,key,len);
  return;
}

void HEAP_DELETE(vector<int>& nums,int i,int& len){
  if(nums[i]>nums[len]){
    nums[i]=nums[len];
   len--;
   nums.pop_back();
   MAX_HEAPIFY(nums,len,i);
  }else {
    HEAP_INCREASE_KEY(nums,i,nums[len],len);
    len--;
    nums.pop_back();
  }

}

vector<int> MergeKLists(vector<vector<int>>& arrs,priority_queue<Node, vector<Node>, greater<Node>>& q,int k){
  vector<int> res;
  int counts[arrs.size()];
  cout<<"arrs below"<<endl;
  for(int i=0;i<arrs.size();i++) printArr(arrs[i]);
  memset(counts,0,sizeof(counts));
  for(int i=0;i<k;i++){
    Node temp;
    temp.from=i;
    temp.val =arrs[i][0];
    cout<<"arrs["<<i<<"]"<<"[0]"<<" "<<arrs[i][0]<<endl;
    q.push(temp);
    counts[i]=0;
    cout<<"temp val "<<temp.val<<" current top "<<q.top().val<<endl;
  }

  int stop =0;
  while(!q.empty()){
   Node temp =q.top();
   q.pop();
   res.push_back(temp.val);
   if(counts[temp.from]<arrs[temp.from].size()-1){
    Node temp2 ;
    temp2.from =temp.from;
    temp2.val =arrs[temp.from][counts[temp.from]++];
    q.push(temp2);
   }
  }
  return res;

}


void YOUNG_MAXIFY(vector<vector<int>>&matrix,int i,int j){
  int h =matrix.size();
  int w =matrix[0].size();
  int largest_x =i,largest_y=j;
  if(i>=1 && matrix[i][j]<matrix[i-1][j]){
    largest_x =i-1;
    largest_y =j;
  }
  if(j>=1 && matrix[largest_x][largest_y]<matrix[i][j-1]){
    largest_x =i;
    largest_y =j-1;
  }
  if(largest_x!=i || largest_y!=j){
    int temp =matrix[i][j];
    matrix[i][j]=matrix[largest_x][largest_y];
    matrix[largest_x][largest_y]=temp;
    YOUNG_MAXIFY(matrix,largest_x,largest_y);
  }
}

void YOUNG_MINIFY(vector<vector<int>>&matrix,int i,int j){
  int h =matrix.size();
  int w =matrix[0].size();
  int smallest_x =i,smallest_y=j;
  if(i<h-1 && matrix[i][j]>matrix[i+1][j]){
    smallest_x =i+1;
    smallest_y =j;
  }
  if(j<w-1 && matrix[smallest_x][smallest_y]>matrix[i][j+1]){
    smallest_x =i;
    smallest_y =j+1;
  }
  if(smallest_x!=i || smallest_y!=j){
    int temp =matrix[i][j];
    matrix[i][j]=matrix[smallest_x][smallest_y];
    matrix[smallest_x][smallest_y]=temp;
    YOUNG_MINIFY(matrix,smallest_x,smallest_y);
  }
}

int YOUNG_EXTRACT_MIN(vector<vector<int>>& matrix){
   int h =matrix.size();
   int w =matrix[0].size();
   if(matrix[0][0]==INT_MAX){
     cout<<"underflow "<<endl;
     return -1;
   }
   int val =matrix[0][0];
   matrix[0][0]=matrix[h-1][w-1];
   matrix[h-1][w-1]=INT_MAX;
   YOUNG_MINIFY(matrix,0,0);
   return val;
}

void YOUNG_INSERT(vector<vector<int>>& matrix,int val){
  int h =matrix.size();
  int w =matrix[0].size();
  if(matrix[h-1][w-1]!=INT_MAX){
    cout<<"overflow"<<endl;
    return;
  }

  matrix[h-1][w-1]=val;
  YOUNG_MAXIFY(matrix, h-1, w-1);

}

void printYOUNG(vector<vector<int>>& matrix){
 int h =matrix.size();
 int w =matrix[0].size();
 for(int i=0;i<h;i++){
  cout<<endl;
  for(int j=0;j<w;j++){
  if(matrix[i][j]!=INT_MAX)  cout<<"   "<<matrix[i][j];
  else cout<<"   "<<"INF";
  }
 }
 cout<<endl;
}

void YOUNGSORT(vector<vector<int>>& matrix){
 //insert the disordered array elements in YOUNG
 while(matrix[0][0]!=INT_MAX){
  cout<<" "<<YOUNG_EXTRACT_MIN(matrix);
 }
}

void YOUNGFINDVAL(vector<vector<int>>& matrix,int val){
  int h =matrix.size();
  int w =matrix[0].size();
  int i =h-1;
  int j=0;
  while(i>=0 && j<w){
    if(matrix[i][j]==val){
     cout<<"find "<<val<<"  at ["<<i<<","<<j<<"]"<<endl;
     return ;
    }
    else if(matrix[i][j]>val) i--;
    else j++;
  }
  cout<<"not find "<<val<<endl;
  return;
}

int main(){

 //vector<int> nums={-1,16,4,10,14,7,9,3,2,8,1};
 //int len =nums.size()-1;
 //MAX_HEAPIFY(nums,len,2);
 //MAX_HEAPIFY_LOOP(nums,len,2);
 //printArr(nums);
 //HEAPSORT(nums);
 /*
 cout<<" nums.size() "<<nums.size()<<" len "<<len<<endl;
 printArr(nums);
 BUILD_MAX_HEAP(nums);
 printArr(nums);
 cout<<" nums.size() "<<nums.size()<<" len "<<len<<endl;
 cout<<"max "<<HEAP_MAXIMUM(nums,len)<<endl;
 HEAP_EXTRACT_MAX(nums,len);
 cout<<"max "<<HEAP_MAXIMUM(nums,len)<<endl;
 cout<<" nums.size() "<<nums.size()<<" len "<<len<<endl;
 int t =len/2;
 HEAP_INCREASE_KEY(nums,t,9999,len);
 cout<<" nums.size() "<<nums.size()<<" len "<<len<<endl;
 printArr(nums);
 cout<<" nums.size() "<<nums.size()<<" len "<<len<<endl;
 MAX_HEAP_INSERT(nums,222,len);
 printArr(nums);
 HEAP_DELETE(nums,4,len);
 cout<<" nums.size() "<<nums.size()<<" len "<<len<<endl;
 printArr(nums);
 */

 /*
 priority_queue<Node, vector<Node>, greater<Node> >A;
 vector<vector<int>> arrs(4,vector<int>(10,0));
 srand((int)time(NULL));
 for(int i=0;i<arrs.size();i++){
  for(int j=0;j<arrs[0].size();j++){
    arrs[i][j]=rand()%120;
  }

  sort(arrs[i].begin(),arrs[i].end());
 // printArr(arrs[i]);
  cout<<" "<<endl;
 }
 for(int i=0;i<arrs.size();i++) printArr(arrs[i]);

 vector<int> output =MergeKLists(arrs,A,4);
 printArr(output);

 */
 vector<vector<int> >matrix ={{2,3,4,INT_MAX},{5,8,9,INT_MAX},{12,14,16,INT_MAX},{INT_MAX,INT_MAX,INT_MAX,INT_MAX}};
 printYOUNG(matrix);
 cout<<"minmal "<<YOUNG_EXTRACT_MIN(matrix)<<endl;
 printYOUNG(matrix);
 YOUNG_INSERT(matrix,7);
 printYOUNG(matrix);
 YOUNGFINDVAL(matrix,13);
 YOUNGFINDVAL(matrix,16);
 YOUNGSORT(matrix);
 return 0;
}
