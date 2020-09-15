#include<iostream>
#include<stack>
#include<vector>
using namespace std;
bool check_is_valid_order(vector<int>& order){
 //http://poj.org/problem?id=1363
  n =order.size();
  int k=0;
  stack<int>st;
  for(int i=1;i<=n;i++){
    st.push(i);
    while(!st.empty() && st.top()==order[k]){
      st.pop();
      k++;
    }
  }
  if(st.empty()) return true;
  else return false;
}
int main(){
 cout<<"Hello"<<endl;
 vector<vector<int>> test(2,vector<int>(5,0));
 test[0]={3,2,5,4,1};
 test[1]={3,1,2,4,5};
 for(int i=0;i<2;i++){
  bool ans =check_is_valid_order(test[i]);
  cout<<"test "<<i;
  if(ans) cout<<" "<<"yes"<<endl;
  else cout<<" "<<"no"<<endl;
 }
 return 0;
}
