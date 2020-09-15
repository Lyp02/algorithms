#include<iostream>
#include<vector>
#include<climits>

using namespace  std;

void findMaxCrossingSubarray(vector<int>& nums,int low,int mid,int high,int& max_left,int& max_right,int& max_sum){
  int sum =0;
  int left_sum =INT_MIN;
  int right_sum =INT_MIN;
  for(int i=mid;i>=low;i--){
    sum =sum +nums[i];
    if(left_sum<sum){
     left_sum =sum;
     max_left =i;
    }
  }
  sum =0;
  for(int j=mid+1;j<=high;j++){
    sum =sum +nums[j];
    if(right_sum<sum){
      right_sum =sum;
      max_right =j;
    }
  }

  max_sum =left_sum+right_sum;
}

void findMaxmumSubarray(vector<int>& nums,int low,int high,int& max_left,int& max_right,int& max_sum){
  if(low==high) {
    max_left =low;max_right=high;max_sum=nums[max_left];
    return;
  }
  int left_low =0,left_high=0,left_max=0,right_low=0,right_high=0,right_max=0,cross_left=0,cross_right=0,cross_sum=0;
  int mid =low +(high-low)/2;
  findMaxmumSubarray(nums,low,mid,left_low,left_high,left_max);
  findMaxmumSubarray(nums,mid+1,high,right_low,right_high,right_max);
  findMaxCrossingSubarray(nums,low,mid,high,cross_left,cross_right,cross_sum);
  if(left_max>=right_max && left_max>=cross_sum){
    max_left =left_low;max_right=left_high;max_sum=left_max;
    return;
  }else if(right_max>=left_max && right_max>=cross_sum){
    max_left=right_low;max_right=right_high;max_sum=right_max;
    return;
  }else{
    max_left=cross_left;max_right=cross_right;max_sum=cross_sum;
    return;
  }
  return;

}

void maxmumSubarrayLinear(vector<int>& nums,int& max_left,int& max_right,int& max_sum){
 int ending_here_sum =0;
 int ending_here_low =0;
 int ending_here_high =0;
 if(nums.size()==1){
   max_left =0;max_right=0;max_sum=nums[0];
   return;
 }else{
  max_left =0;
  max_right =0;
  max_sum =0;
  ending_here_sum =nums[0];

 }
 for(int i=1;i<nums.size();i++){
   ending_here_high =i;
   if(ending_here_sum>=0){
    ending_here_sum =ending_here_sum +nums[i];
   }else {
     ending_here_low =i;
     ending_here_sum =nums[i];
   }
   if(max_sum<ending_here_sum){
    max_sum =ending_here_sum;
    max_left =ending_here_low;
    max_right =ending_here_high;
   }

 }
 return;

}

void matrixAdd(vector<vector<int>>& A,int x0,int y0,vector<vector<int>>& B,int x1,int y1,int l,vector<vector<int>>& C,int x2,int y2){

  for(int i=0;i<l;i++){
   for(int j=0;j<l;j++){
     C[x2+i][y2+j] =A[x0+i][y0+j]+B[x1+i][y1+j];
   }
  }
}

void matrixMinus(vector<vector<int>>& A,int x0,int y0,vector<vector<int>>& B,int x1,int y1,int l,vector<vector<int>>& C,int x2,int y2){

  for(int i=0;i<l;i++){
   for(int j=0;j<l;j++){
     C[x2+i][y2+j] =A[x0+i][y0+j]-B[x1+i][y1+j];
   }
  }
}
vector<vector<int>> strassen(vector<vector<int>>& A,int x0,int y0,vector<vector<int>>& B,int x1,int y1){
  int n =A.size();
  vector<vector<int>> C(n,vector<int>(n,0));
  int l =n/2;
  if(n==1) {
   C[0][0] =A[x0][y0]*B[x1][y1];
   return C;
  }
  vector<vector<int>>S1(l,vector<int>(l,0));
  vector<vector<int>>S2(l,vector<int>(l,0));
  vector<vector<int>>S3(l,vector<int>(l,0));
  vector<vector<int>>S4(l,vector<int>(l,0));
  vector<vector<int>>S5(l,vector<int>(l,0));
  vector<vector<int>>S6(l,vector<int>(l,0));
  vector<vector<int>>S7(l,vector<int>(l,0));
  vector<vector<int>>S8(l,vector<int>(l,0));
  vector<vector<int>>S9(l,vector<int>(l,0));
  vector<vector<int>>S10(l,vector<int>(l,0));


  vector<vector<int>>A11(l,vector<int>(l,0));
  vector<vector<int>>A12(l,vector<int>(l,0));
  vector<vector<int>>A21(l,vector<int>(l,0));
  vector<vector<int>>A22(l,vector<int>(l,0));
  vector<vector<int>>B11(l,vector<int>(l,0));
  vector<vector<int>>B12(l,vector<int>(l,0));
  vector<vector<int>>B21(l,vector<int>(l,0));
  vector<vector<int>>B22(l,vector<int>(l,0));

  for(int i=0;i<l;i++){
    for(int j=0;j<l;j++){
      A11[i][j]=A[i][j];A12[i][j]=A[i][l+j];A21[i][j]=A[i+l][j];A22[i][j]=A[i+l][j+l];

      B11[i][j]=B[i][j];B12[i][j]=B[i][l+j];B21[i][j]=B[i+l][j];B22[i][j]=B[i+l][j+l];
    }
  }




  matrixMinus(B12,0,0,B22,0,0,l,S1,0,0);
  matrixAdd(A11,0,0,A12,0,0,l,S2,0,0);
  matrixAdd(A21,0,0,A22,0,0,l,S3,0,0);
  matrixMinus(B21,0,0,B11,0,0,l,S4,0,0);
  matrixAdd(A11,0,0,A22,0,0,l,S5,0,0);
  matrixAdd(B11,0,0,B22,0,0,l,S6,0,0);
  matrixMinus(A12,0,0,A22,0,0,l,S7,0,0);
  matrixAdd(B21,0,0,B22,0,0,l,S8,0,0);
  matrixMinus(A11,0,0,A21,0,0,l,S9,0,0);
  matrixAdd(B11,0,0,B12,0,0,l,S10,0,0);

  vector<vector<int>>P1(l,vector<int>(l,0));
  vector<vector<int>>P2(l,vector<int>(l,0));
  vector<vector<int>>P3(l,vector<int>(l,0));
  vector<vector<int>>P4(l,vector<int>(l,0));
  vector<vector<int>>P5(l,vector<int>(l,0));
  vector<vector<int>>P6(l,vector<int>(l,0));
  vector<vector<int>>P7(l,vector<int>(l,0));

  P1 =strassen(A11,0,0,S1,0,0);
  P2 =strassen(S2,0,0,B22,0,0);
  P3 =strassen(S3,0,0,B11,0,0);
  P4 =strassen(A22,0,0,S4,0,0);
  P5 =strassen(S5,0,0,S6,0,0);
  P6 =strassen(S7,0,0,S8,0,0);
  P7 =strassen(S9,0,0,S10,0,0);

  matrixAdd(P5,0,0,P4,0,0,l,C,0*l,0*l);
  matrixMinus(C,0*l,0*l,P2,0,0,l,C,0*l,0*l);
  matrixAdd(C,0*l,0*l,P6,0,0,l,C,0*l,0*l);

  matrixAdd(P1,0,0,P2,0,0,l,C,0*l,1*l);

  matrixAdd(P3,0,0,P4,0,0,l,C,1*l,0*l);

  matrixAdd(P5,0,0,P1,0,0,l,C,1*l,1*l);
  matrixMinus(C,1*l,1*l,P3,0,0,l,C,1*l,1*l);
  matrixMinus(C,1*l,1*l,P7,0,0,l,C,1*l,1*l);
  return C;
}

void printMatrix(vector<vector<int>> A){
  int n =A.size();
  cout<<" "<<endl;
  cout<<"["<<endl;
  for(int i=0;i<n;i++){
    cout<<"[";
    for(int j=0;j<n;j++){
      cout<<" "<<A[i][j];
    }
    cout<<"]"<<endl;
  }
  cout<<"]"<<endl;
  return;
}
int main(){

 vector<int> prices={100,113,110,85,105,102,86,63,81,101,94,106,101,79,94,90,97};
 vector<int> profits;
 vector<vector<int>> A={{1,3},{7,5}};
 vector<vector<int>> B={{6,8},{4,2}};
 vector<vector<int>> C={{0,0},{0,0}};
 for(int i=1;i<prices.size();i++){
   profits.push_back(prices[i]-prices[i-1]);
 }
 int max_left=0,max_right=0,max_sum=0;
 //findMaxmumSubarray(profits,0,profits.size()-1,max_left,max_right,max_sum);
 //maxmumSubarrayLinear(profits,max_left,max_right,max_sum);
 //cout<<"buy at "<<(max_left-1)<<" "<<"sell at "<<max_right<<" profits "<<max_sum<<endl;
 cout<<" A"<<endl;
 printMatrix(A);
 cout<<" B"<<endl;
 printMatrix(B);
 C =strassen(A,0,0,B,0,0);
 cout<<" C"<<endl;
 printMatrix(C);
 return 0;
}
