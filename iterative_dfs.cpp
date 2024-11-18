#include <iostream>
#include <vector>
using namespace std;

// DFS function with depth limitation
void depthLimitedDFS(const vector<vector<int>>& graph, int node, int depth, vector<bool>& visited) {
    // If depth is 0, stop the recursion
    if (depth == 0) return;

    // Mark the current node as visited
    visited[node] = true;
    cout << node << " ";

    // Recursively visit all adjacent nodes
    for (int i = 0; i < graph[node].size(); i++) {
        if (graph[node][i] && !visited[i]) {
            depthLimitedDFS(graph, i, depth - 1, visited);
        }
    }
}

// Function to perform DFS for depth levels from 1 to 3
void iterativeDFS(const vector<vector<int>>& graph, int startNode) {
    int n = graph.size();

    for (int depth = 1; depth <= 3; depth++) {
        vector<bool> visited(n, false);
        cout << "DFS with depth = " << depth << ": ";
        depthLimitedDFS(graph, startNode, depth, visited);
        cout << endl;
    }
}

int main() {
    int n = 21; // Number of nodes
    vector<vector<int>> graph(n, vector<int>(n, 0));

    int edges;
    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter the edges (node1 node2) as pairs:" << endl;
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1; // Assuming an undirected graph
    }

    int startNode;
    cout << "Enter the starting node: ";
    cin >> startNode;

    iterativeDFS(graph, startNode);

    return 0;
}
