#include<iostream>
#include<list>
#include<queue>
#include<stack>
using namespace std;

class Graph{
int V;
list<int> *adj;

public:

Graph(int V);
void addEdge(int v, int w);
void BFS(int s);
void DFS(int s);
};

Graph::Graph(int V){
this -> V = V;
adj = new list<int>[V];
}
void Graph::addEdge(int v, int w){
adj[v].push_back(w);}

void Graph::BFS(int s){

bool* visited = new bool[V];
for(int i=0;i<V;i++){
visited[i] = false;
}

queue<int>queue;

visited[s]=true;

queue.push(s);

while(!queue.empty()){

s=queue.front();

cout<<s<<" ";

queue.pop();

for(auto adjVtx : adj[s]){

if(!visited[adjVtx]){

visited[adjVtx]=true;

queue.push(adjVtx);

}

}

}

 
delete [] visited;

}

void Graph::DFS(int s) {

bool* visited = new bool[V];

for (int i = 0; i < V; i++) {

visited[i] = false;

}

stack<int> stack;

visited[s] = true;

stack.push(s);

while (!stack.empty()) {

s = stack.top();

cout << s << " ";

stack.pop();

for (auto adjVtx : adj[s]) {

if (!visited[adjVtx]) {

visited[adjVtx] = true;

stack.push(adjVtx);

}

}

}

delete[] visited;

}

 
int main(){

int n, a, b, k, vertex;

cout << "Enter number of edges: ";

cin >> n;

Graph g(n+2);

cout << "Enter the edges :\n";

for (int i = 0; i < n; i++) {

cin >> a >> b;

g.addEdge(a, b);

}

cout<<"Through which way you want to search the path?\n (1) BFS \n (2) DFS"<<endl;

cin>>k;

switch(k){

case 1:{

cout<<"Enter starting vertex for BFS: ";

cin>>vertex;

g.BFS(vertex);

cout << endl;

break;

}

case 2:{

cout<<"Enter starting vertex for DFS: ";


 
cin>>vertex;

g.DFS(vertex);

cout << endl;

break;

}

default:{

cout<<"Wrong case";

}

}

return 0;

}


