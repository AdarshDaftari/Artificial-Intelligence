#include<bits/stdc++.h>
using namespace std;
void bfs(int n,int e,unordered_map<int,vector<int>>&mp,int start,vector<int>&visited){
    queue<int>q;
    visited[start]=1;
    q.push(start);
    while(!q.empty()){
        int vert=q.front();
        cout<<vert<<" ";
        vector<int>temp=mp[vert];
        for(int i=0;i<temp.size();i++){
            if(!visited[temp[i]]){
                q.push(temp[i]);
                visited[temp[i]]=1;
            }
        }
        q.pop();
    }

    for(int i=0;i<n;i++){
        if(!visited[i]) cout<<i<<" ";
    }
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
    cout<<"Enter the node from which bfs to be started : ";
    cin>>start;
    bfs(n,e,mp,start,visited);
}