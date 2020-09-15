/*
Stable Matching
*/
#include<iostream>
#include<vector>

using namespace std;

struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};

void ListNode_insert(ListNode* head,int val){
 ListNode* node = new ListNode(val);
 node->next =head->next;
 head->next =node;
 return;
}
void ListNode_delete(ListNode* head){
 if(head->next==NULL) return;
 int val =head->next->val;
 head->next =head->next->next;
 return ;
}
void stableMatching(vector<vector<int>>& ManPref,vector<vector<int>>& WomanPref){
  ListNode* man_free =new ListNode(-1);
  ListNode* cur =man_free;
  int n =ManPref.size();
  for(int i=0;i<n;i++){
   ListNode* temp =new ListNode(i);
   cur->next =temp;
   cur=temp;
  }
  vector<int>Next(n,0);//man prefer order
  vector<vector<int>>Ranking(n,vector<int>(n,0));
  for(int i=0;i<WomanPref.size();i++){
   for(int j=0;j<WomanPref[0].size();j++){
    Ranking[i][WomanPref[i][j]]=j;
   }
  }

  vector<int> Current(n,-1);//woman free
  while(man_free!=NULL &&man_free->next!=NULL){
   cout<<"i"<<endl;
   int m =man_free->next->val;
   if(Next[m]==Next.size()){
    ListNode_delete(man_free);
    continue;
   }
   int w =ManPref[m][Next[m]];
   cout<<"m "<<m<<" w "<<w<<endl;
   Next[m]++;
   cout<<"Next[m] "<<Next[m]<<endl;
   if(Current[w]==-1){
    Current[w]=m;
    ListNode_delete(man_free);
   }else {
    int m2 =Current[w];
    if(Ranking[w][m]<Ranking[w][m2]){
     Current[w]=m;
     ListNode_delete(man_free);
     ListNode_insert(man_free,m2);
    }
   }
  }

  for(int i=0;i<Current.size();i++){
   cout<<"Man "<<Current[i]<<" Woman "<<i<<endl;
  }
  return;

}
int main(){
 vector<vector<int>>ManPref={{1,0,3,4,2},{3,1,0,2,4},{1,4,2,3,0},{0,3,2,1,4},{1,3,0,4,2}};
 vector<vector<int>>WomanPref={{4,0,1,3,2},{2,1,3,0,4},{1,2,3,4,0},{0,4,3,2,1},{3,1,4,2,0}};
 vector<vector<int>>Forbid={{0,0,1,0,0},{0,0,0,1,0},{0,1,0,0,0},{0,0,0,1,0},{0,0,1,0,0}};
 stableMatching(ManPref,WomanPref);
 return 0;
}
