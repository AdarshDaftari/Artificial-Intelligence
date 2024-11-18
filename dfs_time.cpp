#include<bits/stdc++.h>
using namespace std;

// Depth-First Search function
void dfs(unordered_map<int, vector<int>>& mp, int start, vector<int>& visited) {
    if (!visited[start]) {
        cout << start << " ";
        visited[start] = 1;
    }
    for (auto x : mp[start]) {
        if (!visited[x]) dfs(mp, x, visited);
    }
    return;
}

int main() {
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;
    vector<int> visited(n, 0); // Visited array to track visited nodes

    int e;
    cout << "Enter the number of edges: ";
    cin >> e;

    unordered_map<int, vector<int>> mp; // Adjacency list representation of the graph

    int v1, v2;
    for (int i = 1; i <= e; i++) {
        cout << "Enter the vertices between which edge is there: ";
        cin >> v1 >> v2;
        mp[v1].push_back(v2);
        mp[v2].push_back(v1); // For undirected graph, add both directions
    }

    // Sorting adjacency list for each node
    for (auto &x : mp) {
        sort((x.second).begin(), (x.second).end());
    }

    int start;
    cout << "Enter the node from which DFS to be started: ";
    cin >> start;

    // Perform DFS starting from the given node
    dfs(mp, start, visited);

    // Output time complexity
    cout << "\nTime Complexity: O(e log e + n + e) ≈ O(e log e)" << endl;
    cout << "Space Complexity: O(n + e)" << endl;

    return 0;
}
