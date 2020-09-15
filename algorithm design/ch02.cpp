/*
PriorityQueue

*/

#include<iostream>
#include<vector>
#include<climits>
#include<map>

using namespace std;
template<class T>
class PriorityQueue{
/*from smaller->bigger*/
 public:
    vector<T> key;
    vector<int> Position;
    map<T,int> dict;
    int heapsize;
    PriorityQueue():heapsize(0){ T temp;key.push_back(temp);Position.push_back(INT_MAX);}
    int Parent(int i){
     return i/2;
    }
    int Left(int i){
     return 2*i;
    }
    int Right(int i){
     return 2*i+1;
    }

    void Heapify_up(int i){
     if(i<=1) return;
     int p =Parent(i);
     if(key[i]<key[p]){
      dict[key[i]]=p;
      dict[key[p]]=i;

      T temp =key[i];
      key[i]=key[p];
      key[p]=temp;


      Heapify_up(p);
     }
     return;
    }

   void Heapify_down(int i){
     int left =Left(i);
     int right =Right(i);
     int min_index=i;
     if(left<=heapsize && key[min_index]>key[left]){
       min_index =left;
     }
     if(right<=heapsize && key[min_index]>key[right]){
       min_index =right;
     }
     if(min_index!=i){
      dict[key[i]]=min_index;
      dict[key[min_index]]=i;
      T temp =key[i];
      key[i]=key[min_index];
      key[min_index]=temp;


      Heapify_down(min_index);
     }
    }

    void StartHeap(vector<T>& a){
      int n =a.size();
      heapsize =n;
      for(int i=0;i<n;i++){
       key.push_back(a[i]);
       Position.push_back(i+1);
       dict[a[i]]=i+1;
      }
      for(int i=(n/2);i>=1;i--){
       Heapify_down(i);
      }
    }

    void Insert(T t){
      heapsize =heapsize+1;
      key.push_back(t);
      Position.push_back(Position.size());
      dict[t]=Position.size();
      Heapify_up(heapsize);
    }

    T FindMin(){
      if(heapsize<1){
       cout<<"under flow "<<endl;
       return NULL;
      }
      return key[1];
    }
    void Delete(int i){
     if(i>heapsize || heapsize<1) {
       cout<<"under flow"<<endl;
     }
     else{
       Position[i]=INT_MAX;
       dict.erase(key[i]);
       key[i]=key[heapsize];
       heapsize--;
       Heapify_down(i);

     }
    }
    void ExtractMin(){
     Delete(1);
    }
    void Delete_Position(T t){
     int i=dict[t];
     Delete(i);
    }

    void ChangeKey(T t,T val){
     int i =dict[t];

     if(key[i]>val){

      dict[val]=dict[key[i]];
      dict.erase(key[i]);
      key[i]=val;


      Heapify_up(i);
     }
    else if(key[i]<val){

     dict[val]=dict[key[i]];
     dict.erase(key[i]);
     key[i]=val;


     Heapify_down(i);
    }
  }

};

int main(){
 vector<int> num ={4,1,3,2,16,9,10,14,8,7};
 PriorityQueue<int> q;
 q.StartHeap(num);
 cout<<endl;
 for(int i=1;i<q.key.size();i++) cout<<" "<<q.key[i];
 cout<<endl;
 for(int i=1;i<q.Position.size();i++) cout<<" "<<q.dict[q.key[i]];
 cout<<endl;
 q.ChangeKey(14,-3);
 for(int i=1;i<q.key.size();i++) cout<<" "<<q.key[i];
 cout<<endl;
 cout<<endl;
 for(int i=1;i<q.Position.size();i++) cout<<" "<<q.dict[q.key[i]];
 cout<<endl;
 return 0;
}
