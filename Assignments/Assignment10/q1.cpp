// Write a Program to implement Kruskal's algorithm to find the minimum spanning tree
// of a user defined graph. Use Adjacency Matrix to represent a graph.

#include <iostream>
using namespace std;

struct Edge {
    int src;
    int dest;
    int weight;
};

class DisjointSet {
private:
    int* parent;
    int* rank;
    int size;
    
public:
    DisjointSet(int n) {
        size = n;
        parent = new int[size];
        rank = new int[size];
        
        for (int i = 0; i < size; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
    
    bool isSameSet(int x, int y) {
        return find(x) == find(y);
    }
    
    ~DisjointSet() {
        delete[] parent;
        delete[] rank;
    }
};

class Graph {
private:
    int numVertices;
    int** adjMatrix;
    Edge* edges;
    int edgeCount;
    
    void sortEdges() {
        for (int i = 0; i < edgeCount - 1; i++) {
            for (int j = 0; j < edgeCount - i - 1; j++) {
                if (edges[j].weight > edges[j + 1].weight) {
                    Edge temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }
    }
    
    void extractEdges() {
        edgeCount = 0;
        
        for (int i = 0; i < numVertices; i++) {
            for (int j = i + 1; j < numVertices; j++) {
                if (adjMatrix[i][j] != 0) {
                    edgeCount++;
                }
            }
        }
        
        edges = new Edge[edgeCount];
        
        int index = 0;
        for (int i = 0; i < numVertices; i++) {
            for (int j = i + 1; j < numVertices; j++) {
                if (adjMatrix[i][j] != 0) {
                    edges[index].src = i;
                    edges[index].dest = j;
                    edges[index].weight = adjMatrix[i][j];
                    index++;
                }
            }
        }
    }
    
public:
    Graph(int vertices) {
        numVertices = vertices;
        edgeCount = 0;
        edges = nullptr;
        
        adjMatrix = new int*[numVertices];
        for (int i = 0; i < numVertices; i++) {
            adjMatrix[i] = new int[numVertices];
            for (int j = 0; j < numVertices; j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }
    
    void addEdge(int src, int dest, int weight) {
        adjMatrix[src][dest] = weight;
        adjMatrix[dest][src] = weight;
    }
    
    void kruskalMST() {
        extractEdges();
        sortEdges();
        
        DisjointSet ds(numVertices);
        
        cout << "\nMinimum Spanning Tree:\n";
        cout << "Edge\t\tWeight\n";
        
        int totalWeight = 0;
        int mstCount = 0;
        
        for (int i = 0; i < edgeCount && mstCount < numVertices - 1; i++) {
            int src = edges[i].src;
            int dest = edges[i].dest;
            int weight = edges[i].weight;
            
            if (!ds.isSameSet(src, dest)) {
                cout << src << " - " << dest << "\t\t" << weight << endl;
                totalWeight += weight;
                mstCount++;
                ds.unionSets(src, dest);
            }
        }
        
        cout << "\nTotal Weight: " << totalWeight << endl;
    }
    
    ~Graph() {
        for (int i = 0; i < numVertices; i++) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
        
        if (edges != nullptr) {
            delete[] edges;
        }
    }
};

int main() {
    int vertices, numEdges;
    
    cout << "Enter number of vertices: ";
    cin >> vertices;
    
    Graph graph(vertices);
    
    cout << "Enter number of edges: ";
    cin >> numEdges;
    
    cout << "Enter edges (source destination weight):\n";
    
    for (int i = 0; i < numEdges; i++) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }
    
    graph.kruskalMST();
    
    return 0;
}