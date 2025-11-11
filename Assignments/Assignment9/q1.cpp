// Write a Program to accept a graph from a user and represent it
// with Adjacency Matrix and perform BFS and DFS traversals on it.

#include <iostream>
#include <queue>

using namespace std;
#define MAX 10
class Graph {
private:
    int adjMatrix[MAX][MAX];
    int numVertices;
public:
    Graph(int vertices) {
        numVertices = vertices;
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }
    void addEdge(int src, int dest) {
        adjMatrix[src][dest] = 1;
        adjMatrix[dest][src] = 1; // For undirected graph
    }
    void BFS(int startVertex) {
        bool visited[MAX] = {false};
        queue<int> q;
        visited[startVertex] = true;
        q.push(startVertex);
        cout << "BFS Traversal starting from vertex " << startVertex << ": ";
        while (!q.empty()) {
            int vertex = q.front();
            cout << vertex << " ";
            q.pop();
            for (int i = 0; i < numVertices; i++) {
                if (adjMatrix[vertex][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }
    void DFSUtil(int vertex, bool visited[]) {
        visited[vertex] = true;
        cout << vertex << " ";
        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[vertex][i] == 1 && !visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }
    void DFS(int startVertex) {
        bool visited[MAX] = {false};
        cout << "DFS Traversal starting from vertex " << startVertex << ": ";
        DFSUtil(startVertex, visited);
        cout << endl;
    }

};

int main() {
    int vertices, edges, src, dest, startVertex;
    cout << "Enter number of vertices (max " << MAX << "): ";
    cin >> vertices;
    Graph g(vertices);
    cout << "Enter number of edges: ";
    cin >> edges;
    cout << "Enter edges (source destination) as pairs of vertex indices (0 to " << vertices - 1 << "):\n";
    for (int i = 0; i < edges; i++) {
        cin >> src >> dest;
        g.addEdge(src, dest);
    }
    cout << "Enter starting vertex for BFS and DFS: ";
    cin >> startVertex;
    g.BFS(startVertex);
    g.DFS(startVertex);
    return 0;
}