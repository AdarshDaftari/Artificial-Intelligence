#include<bits/stdc++.h>
using namespace std;
void dfs(unordered_map<int,vector<int>>&mp,int start,vector<int>&visited){
    if(!visited[start]){
        cout<<start<<" ";
        visited[start]=1;
    }
   for(auto x:mp[start]){
    if(!visited[x]) dfs(mp,x,visited);
   }
   return;
}
int main(){
    int n;
    cout<<"Enter the number of nodes : ";
    cin>>n;
    vector<int>visited(n,0);
    int e;
    cout<<"Enter the number of edges : ";
    cin>>e;
    unordered_map<int,vector<int>>mp;
    int v1,v2;
    for(int i=1;i<=e;i++){
        cout<<"Enter the vertices btw which edge is there : ";
        cin>>v1>>v2;
        mp[v1].push_back(v2);
        mp[v2].push_back(v1);
    }
    for(auto &x:mp){
        sort((x.second).begin(),(x.second).end());
    }
    int start;
    cout<<"Enter the node from which dfs to be started : ";
    cin>>start;
    dfs(mp,start,visited);
    return 0;
}