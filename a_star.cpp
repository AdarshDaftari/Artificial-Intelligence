#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits> 
#include <algorithm> 
using namespace std;

const int NODES = 10; 
vector<vector<int>> graph = {
    {0, 6, 3, 1, 0, 0, 0, 0, 0, 0},
    {6, 0, 2, 6, 3, 4, 0, 0, 0, 0},
    {3, 2, 0, 0, 0, 5, 0, 9, 0, 0},
    {1, 6, 0, 0, 7, 8, 9, 0, 0, 0},
    {0, 3, 0, 7, 0, 0, 9, 0, 0, 0},
    {0, 4, 5, 8, 0, 0, 0, 9, 0, 0},
    {0, 0, 0, 9, 9, 0, 0, 8, 12, 0},
    {0, 0, 9, 0, 0, 9, 8, 0, 14, 15},
    {0, 0, 0, 0, 0, 0, 12, 14, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 15, 0, 0}
};


vector<int> heuristic = {15, 13, 13, 12, 10, 9, 7, 6, 5, 0};


void printPath(vector<int> &parent, int j) {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    cout << " -> " << char(j + 'A');
}


void DFS(int start) {
    vector<bool> visited(NODES, false);
    stack<int> s;
    s.push(start);
    visited[start] = true;

    cout << "DFS Traversal: ";
    while (!s.empty()) {
        int node = s.top();
        s.pop();
        cout << char(node + 'A') << " ";

        for (int i = 0; i < NODES; ++i) {
            if (graph[node][i] && !visited[i]) {
                s.push(i);
                visited[i] = true;
            }
        }
    }
    cout << endl;
}


void BestFirstSearch(int start) {
    vector<bool> visited(NODES, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    cout << "Best-First Search Traversal: ";
    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();

        if (!visited[node]) {
            cout << char(node + 'A') << " ";
            visited[node] = true;
        }

        for (int i = 0; i < NODES; ++i) {
            if (graph[node][i] && !visited[i]) {
                pq.push({graph[node][i], i});
            }
        }
    }
    cout << endl;
}


bool DLS(int node, int target, int limit, vector<bool> &visited) {
    visited[node] = true;
    if (node == target)
        return true;

    if (limit <= 0)
        return false;

    for (int i = 0; i < NODES; ++i) {
        if (graph[node][i] && !visited[i]) {
            if (DLS(i, target, limit - 1, visited)) {
                return true;
            }
        }
    }
    return false;
}

void IterativeDeepeningDFS(int start, int target, int maxDepth) {
    cout << "Iterative Deepening Search: ";
    for (int limit = 0; limit <= maxDepth; ++limit) {
        vector<bool> visited(NODES, false);
        if (DLS(start, target, limit, visited)) {
            cout << endl << "Reached Target at Depth: " << limit << endl;
            return;
        }
    }
    cout << "Target Not Found" << endl;
}


void BFS(int start) {
    vector<bool> visited(NODES, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    cout << "BFS Traversal: ";
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << char(node + 'A') << " ";

        for (int i = 0; i < NODES; ++i) {
            if (graph[node][i] && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
    cout << endl;
}


void BeamSearch(int start) {
    vector<bool> visited(NODES, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    cout << "Beam Search Traversal: ";
    int beamWidth = 2;
    while (!pq.empty()) {
        vector<pair<int, int>> levelNodes;

        for (int i = 0; i < beamWidth && !pq.empty(); ++i) {
            levelNodes.push_back(pq.top());
            pq.pop();
        }

        sort(levelNodes.begin(), levelNodes.end());

        for (auto &node : levelNodes) {
            int currentNode = node.second;
            if (!visited[currentNode]) {
                cout << char(currentNode + 'A') << " ";
                visited[currentNode] = true;
            }

            for (int i = 0; i < NODES; ++i) {
                if (graph[currentNode][i] && !visited[i]) {
                    pq.push({graph[currentNode][i], i});
                }
            }
        }
    }
    cout << endl;
}


void AStar(int start, int goal) {
    vector<int> g(NODES, INT_MAX);
    vector<int> f(NODES, INT_MAX);
    vector<int> parent(NODES, -1);
    vector<bool> closedSet(NODES, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> openSet;

    g[start] = 0;
    f[start] = heuristic[start];
    openSet.push({f[start], start});

    cout << "A* Traversal: ";
    while (!openSet.empty()) {
        int node = openSet.top().second;
        openSet.pop();

        if (node == goal) {
            cout << "Goal Reached!" << endl;
            cout << "Path: A";
            printPath(parent, goal);
            cout << endl;
            return;
        }

        closedSet[node] = true;

        for (int i = 0; i < NODES; ++i) {
            if (graph[node][i] && !closedSet[i]) {
                int tentative_g = g[node] + graph[node][i];

                if (tentative_g < g[i]) {
                    parent[i] = node;
                    g[i] = tentative_g;
                    f[i] = g[i] + heuristic[i];
                    openSet.push({f[i], i});
                }
            }
        }
    }
    cout << "No Path Found" << endl;
}

int main() {
    int start = 0; 
    int goal = 9;  

    DFS(start);
    BestFirstSearch(start);
    IterativeDeepeningDFS(start, goal, 4);
    BFS(start);
    BeamSearch(start);
    AStar(start, goal);

    return 0;
}
