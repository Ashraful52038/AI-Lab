#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// BFS from given source s
void bfs(vector<vector<int>>& adj, int s, 
                      vector<bool>& visited);

// Perform BFS for the entire graph which maybe
// disconnected
void bfsDisconnected(vector<vector<int>>& adj) {
    vector<bool> visited(adj.size(), false); 

    for (int i = 0; i < adj.size(); ++i) {
        if (!visited[i]) {
            bfs(adj, i, visited);
        }
    }
}


// BFS from given source s
void bfs(vector<vector<int>>& adj, int s, 
                      vector<bool>& visited) 
{
    queue<int> q; // Create a queue for BFS

    // Mark the source node as visited and enqueue it
    visited[s] = true;
    q.push(s);

    // Iterate over the queue
    while (!q.empty()) {
        int curr = q.front(); // Dequeue a vertex
        q.pop();
        cout << curr << " ";

        // Get all adjacent vertices of curr
        for (int x : adj[curr]) {
            if (!visited[x]) {
                visited[x] = true; // Mark as visited
                q.push(x); // Enqueue it
            }
        }
    }
}

// Function to add an edge to the graph
void addEdge(vector<vector<int>>& adj, int u, int v) 
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int main() 
{
    int V = 6;

    vector<vector<int>> adj(V); 
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 3, 4);
    addEdge(adj, 4, 5);  
    bfsDisconnected(adj);

    return 0;
}
