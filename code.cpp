#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Node{
    private:
        T val;
    public:
        Node(){
            //do nothing
        }
        Node(T t){
            val=t;
        }
        T getval(){
            return val;
        }
        bool operator==(const Node & n)const{
            return n.val==val;
        }
        bool operator<(const Node & n)const{
            return val>n.val;
        }
};

template <typename T>
class Edge{
    private:
        T val;
        long long weight;
    public:
        Edge(){}
        Edge(T n,long long w){
            weight=w;val=n;
        }
        long long getweight()const{
            return weight;
        }
        void setweight(long long w){
            weight=w;
        }
        T getval()const{
            return val;
        }
        bool operator<(const Edge& other)const {
            return weight>other.weight; // Compare based on weight
        }
};

template <typename T>
bool compare(const pair<Edge<T>,long long> &a,const pair<Edge<T>,long long>& b){
    if(a.first.getweight()==b.first.getweight()){return a.first.getval()<b.first.getval();}
    return a.first.getweight()<b.first.getweight();
}

// T will be pair of Edge and long long
template <typename T>
class minpq{
    private:
        vector<T> arr;
        long long cursize;
    public:
        minpq(){
            cursize=0;
            arr.push_back(T());
        }
        minpq(long long n){arr.resize(n+1);cursize=0;}
        //TOP OF AN ELEMENT
        T top(){
            if(cursize==0){cout<<"error"<<endl;exit(0);}
            return arr[1];
        }
        //PUSHING AN 
        void push(T t){
            if(arr.size()==cursize+1){
                arr.resize(2*cursize+1);
            }
            //now we have sufficient size
            cursize++;
            //we need to percolate up
            long long hole=cursize;
            while(hole>1 && compare(t,arr[hole/2])){
                arr[hole]=arr[hole/2];
                hole=hole/2;
            }
            arr[hole]=t;
            return;
        }
        void pop(){
            if(cursize==0){return;}
            arr[1]=arr[cursize];
            cursize--;
            long long hole=1;
            T val=arr[hole];
            while(2*hole<=cursize) {
                long long child=2*hole;
                if(child+1<=cursize && compare(arr[child+1],arr[child])) {
                    child++;
                }
                if(compare(val,arr[child])) break;
                arr[hole]=arr[child];
                hole=child;
            }
            arr[hole]=val;
            return;
        }
        void print(){
            for(int i=1;i<=cursize;i++){
                cout<<arr[i].first.getval()<<" "<<arr[i].first.getweight()<<" "<<arr[i].second<<endl;
            }
        }
        bool empty(){
            return cursize==0;
        }
};


template <typename T>
class Graph{
    private:
        map<T,Node<T>> strp;
        map<T,long long> pairing;
        map<long long,vector<Edge<long long>>> mp;
        long long vertices;
        long long edges;
    public:
        Graph(){
            //do nothing
            vertices=0;edges=0;
        }
        Graph(long long n,long long m){
            vertices=n;edges=m;
        }
        void printNodes(){
            for(auto x:strp){
                cout<<x.first<<" "<<pairing[x.second]<<endl;
            }
        }
        void takeinput(){
            for(long long i=0;i<vertices;i++){
                T t;cin>>t;
                Node<T> n(t);
                strp[t]=n;
                pairing[t]=i;
            }
            //setting edges
            for(long long i=0;i<edges;i++){
                T t1;cin>>t1;
                T t2;cin>>t2;long long x;cin>>x;
                Edge<long long> e1(pairing[t1],x);
                Edge<long long> e2(pairing[t2],x);           //2 edges 
                mp[pairing[t1]].push_back(e2);       //find the node ans associated long long add edge to it
                mp[pairing[t2]].push_back(e1);
            }
            return;
        }
        void Dijkstra(T t1,T t2){
            long long u=pairing[t1];
            long long v=pairing[t2];
            if(u==v){cout<<0<<endl;return;}
            //find path from u to v even no.of wdges
            //we will malong longain a priority queue
            minpq<pair<Edge<long long>,long long>> pq(mp.size());
            vector<long long> evendistances(vertices,LLONG_MAX);
            vector<long long> odddistances(vertices,LLONG_MAX);
            // 0 for even 1 for odd
            //we will push the edge with even parity
            Edge<long long> e(u,0);    //dist is 0
            evendistances[u]=0;
            pq.push({e,0});
            while(!pq.empty()){
                pair<Edge<long long>,long long> cur=pq.top();pq.pop();
                //cur.first.val is the vertex num
                //cur.first.weight is the weight
                //cur.second is the parity
                //we will update the dist of cur
                if(cur.second==1 && odddistances[cur.first.getval()]<cur.first.getweight()){continue;}  
                if(cur.second==0 && evendistances[cur.first.getval()]<cur.first.getweight()){continue;}  
                
                if(cur.second==1){
                    //odd parity
                    //update dist if it is less         
                    //now push things in pq by keeping parity as 0
                    for(auto ele: mp[cur.first.getval()]){
                        long long num=ele.getweight()+odddistances[cur.first.getval()];
                        if(num<=evendistances[ele.getval()]){
                            evendistances[ele.getval()]=num;
                            pq.push({Edge<long long>(ele.getval(),num),0});
                        }
                    }         
                }
                else{
                    //evem parity
                    //update dist if it is less         
                    //now push things in pq by keeping parity as 0
                    for(auto ele: mp[cur.first.getval()]){
                        long long num=ele.getweight()+evendistances[cur.first.getval()];
                        if(num<=odddistances[ele.getval()]){
                            odddistances[ele.getval()]=num;
                            pq.push({Edge<long long>(ele.getval(),num),1});
                        }
                    }
                }     
            }
            if(evendistances[v]==LLONG_MAX){cout<<-1<<endl;return;}
            cout<<evendistances[v]<<endl;return;
        }
};

int main()
{
    long long int n, m;
    cin >> n >> m;
    Graph<string> g(n, m);
    g.takeinput();
    string a, b;
    cin>>a>>b;
    //g.printNodes();
    g.Dijkstra(a,b);
}
