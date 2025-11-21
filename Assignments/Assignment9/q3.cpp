// Write a Program to implement Kruskal's algorithm to find the minimum spanning tree
// of a user defined graph. Use Adjacency List to represent a graph.

#include <iostream>
#include <climits>
using namespace std;

// Forward declarations
struct EdgeNode;
struct Edge;
class Graph;
class DisjointSet;

// Node in adjacency list
struct EdgeNode {
    int vertex;
    int weight;
    EdgeNode* next;
};

// Edge structure for Kruskal's algorithm
struct Edge {
    int src;
    int dest;
    int weight;
};

// Disjoint Set (Union-Find) for cycle detection
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
        
        // Initially, all vertices are in different sets
        for (int i = 0; i < size; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    
    // Find set of an element (with path compression)
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }
    
    // Union of two sets (by rank)
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            // Union by rank
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
    
    // Check if two elements are in same set
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
    EdgeNode** adjList;
    Edge* edges;
    int edgeCount;
    int edgeCapacity;
    
    // Sort edges by weight (Bubble Sort for simplicity)
    void sortEdges() {
        for (int i = 0; i < edgeCount - 1; i++) {
            for (int j = 0; j < edgeCount - i - 1; j++) {
                if (edges[j].weight > edges[j + 1].weight) {
                    // Swap edges
                    Edge temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }
    }
    
public:
    Graph(int vertices) {
        numVertices = vertices;
        adjList = new EdgeNode*[numVertices];
        edgeCount = 0;
        edgeCapacity = 100;  // Initial capacity
        edges = new Edge[edgeCapacity];
        
        // Initialize all adjacency lists as empty
        for (int i = 0; i < numVertices; i++) {
            adjList[i] = NULL;
        }
    }
    
    // Add edge to the graph (undirected)
    void addEdge(int src, int dest, int weight) {
        // Add to adjacency list (src to dest)
        EdgeNode* newNode = new EdgeNode;
        newNode->vertex = dest;
        newNode->weight = weight;
        newNode->next = adjList[src];
        adjList[src] = newNode;
        
        // Add to adjacency list (dest to src)
        newNode = new EdgeNode;
        newNode->vertex = src;
        newNode->weight = weight;
        newNode->next = adjList[dest];
        adjList[dest] = newNode;
        
        // Add to edges array (store only once for undirected graph)
        if (edgeCount >= edgeCapacity) {
            // Resize array if needed
            edgeCapacity *= 2;
            Edge* newEdges = new Edge[edgeCapacity];
            for (int i = 0; i < edgeCount; i++) {
                newEdges[i] = edges[i];
            }
            delete[] edges;
            edges = newEdges;
        }
        
        // Store edge with smaller vertex first
        if (src <= dest) {
            edges[edgeCount].src = src;
            edges[edgeCount].dest = dest;
        } else {
            edges[edgeCount].src = dest;
            edges[edgeCount].dest = src;
        }
        edges[edgeCount].weight = weight;
        edgeCount++;
    }
    
    // Display the adjacency list
    void displayGraph() {
        cout << "\n========== Graph (Adjacency List) ==========\n";
        for (int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << ": ";
            EdgeNode* temp = adjList[i];
            
            if (temp == NULL) {
                cout << "No edges";
            } else {
                while (temp != NULL) {
                    cout << "(" << temp->vertex << ", W:" << temp->weight << ")";
                    if (temp->next != NULL) {
                        cout << " -> ";
                    }
                    temp = temp->next;
                }
            }
            cout << endl;
        }
        cout << "Total edges: " << edgeCount << endl;
        cout << "============================================\n";
    }
    
    // Kruskal's algorithm to find MST
    void kruskalMST() {
        // Sort all edges by weight
        sortEdges();
        
        cout << "\n========== Kruskal's Algorithm Steps ==========\n";
        cout << "\nStep 1: Sorted edges by weight:\n";
        cout << "Edge\t\tWeight\n";
        cout << "----\t\t------\n";
        for (int i = 0; i < edgeCount; i++) {
            cout << edges[i].src << " - " << edges[i].dest 
                 << "\t\t" << edges[i].weight << endl;
        }
        
        // Create disjoint set
        DisjointSet ds(numVertices);
        
        // Array to store MST edges
        Edge* mstEdges = new Edge[numVertices - 1];
        int mstCount = 0;
        int totalWeight = 0;
        
        cout << "\n\nStep 2: Processing edges (cycle detection):\n";
        cout << "-----------------------------------------------\n";
        
        // Process all edges
        for (int i = 0; i < edgeCount && mstCount < numVertices - 1; i++) {
            int src = edges[i].src;
            int dest = edges[i].dest;
            int weight = edges[i].weight;
            
            cout << "\nConsidering edge: " << src << " - " << dest 
                 << " (Weight: " << weight << ")\n";
            
            // Check if adding this edge creates a cycle
            if (!ds.isSameSet(src, dest)) {
                // No cycle, add to MST
                mstEdges[mstCount] = edges[i];
                mstCount++;
                totalWeight += weight;
                
                ds.unionSets(src, dest);
                
                cout << "  -> ACCEPTED (No cycle formed)\n";
                cout << "  -> MST edges so far: " << mstCount << endl;
            } else {
                cout << "  -> REJECTED (Would create a cycle)\n";
            }
        }
        
        cout << "===============================================\n";
        
        // Check if MST is complete
        if (mstCount < numVertices - 1) {
            cout << "\nGraph is not connected! Cannot form complete MST.\n";
            cout << "MST edges found: " << mstCount << " (Need: " 
                 << (numVertices - 1) << ")\n";
        } else {
            displayMST(mstEdges, mstCount, totalWeight);
        }
        
        delete[] mstEdges;
    }
    
    // Display the Minimum Spanning Tree
    void displayMST(Edge* mstEdges, int count, int totalWeight) {
        cout << "\n========== Minimum Spanning Tree ==========\n";
        cout << "Edge\t\tWeight\n";
        cout << "----\t\t------\n";
        
        for (int i = 0; i < count; i++) {
            cout << mstEdges[i].src << " - " << mstEdges[i].dest 
                 << "\t\t" << mstEdges[i].weight << endl;
        }
        
        cout << "-------------------------------------------\n";
        cout << "Total number of edges in MST: " << count << endl;
        cout << "Total Weight of MST: " << totalWeight << endl;
        cout << "===========================================\n";
    }
    
    // Display all edges
    void displayAllEdges() {
        cout << "\n--- All Edges ---\n";
        cout << "Edge\t\tWeight\n";
        cout << "----\t\t------\n";
        for (int i = 0; i < edgeCount; i++) {
            cout << edges[i].src << " - " << edges[i].dest 
                 << "\t\t" << edges[i].weight << endl;
        }
        cout << "Total: " << edgeCount << " edges\n";
    }
    
    ~Graph() {
        // Free all edge nodes
        for (int i = 0; i < numVertices; i++) {
            EdgeNode* temp = adjList[i];
            while (temp != NULL) {
                EdgeNode* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
        delete[] adjList;
        delete[] edges;
    }
};

int main() {
    int vertices, numEdges;
    
    cout << "================================================\n";
    cout << " Kruskal's Algorithm - Minimum Spanning Tree\n";
    cout << "================================================\n";
    
    cout << "\nEnter number of vertices: ";
    cin >> vertices;
    
    if (vertices < 1) {
        cout << "Invalid number of vertices!\n";
        return 1;
    }
    
    Graph graph(vertices);
    
    cout << "Enter number of edges: ";
    cin >> numEdges;
    
    if (numEdges < 0) {
        cout << "Invalid number of edges!\n";
        return 1;
    }
    
    cout << "\nEnter edges (source destination weight):\n";
    cout << "(Vertices should be numbered from 0 to " << (vertices - 1) << ")\n";
    
    for (int i = 0; i < numEdges; i++) {
        int src, dest, weight;
        cout << "Edge " << (i + 1) << ": ";
        cin >> src >> dest >> weight;
        
        if (src < 0 || src >= vertices || dest < 0 || dest >= vertices) {
            cout << "Invalid vertex! Vertices must be between 0 and " 
                 << (vertices - 1) << endl;
            i--;
            continue;
        }
        
        if (src == dest) {
            cout << "Self-loops not allowed!\n";
            i--;
            continue;
        }
        
        if (weight < 0) {
            cout << "Invalid weight! Weight must be non-negative.\n";
            i--;
            continue;
        }
        
        graph.addEdge(src, dest, weight);
    }
    
    int choice;
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Display Graph (Adjacency List)\n";
        cout << "2. Display All Edges\n";
        cout << "3. Find MST using Kruskal's Algorithm\n";
        cout << "4. Add More Edges\n";
        cout << "5. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                graph.displayGraph();
                break;
            
            case 2:
                graph.displayAllEdges();
                break;
            
            case 3:
                graph.kruskalMST();
                break;
            
            case 4: {
                int numNewEdges;
                cout << "How many edges to add? ";
                cin >> numNewEdges;
                
                cout << "\nEnter edges (source destination weight):\n";
                for (int i = 0; i < numNewEdges; i++) {
                    int src, dest, weight;
                    cout << "Edge " << (i + 1) << ": ";
                    cin >> src >> dest >> weight;
                    
                    if (src < 0 || src >= vertices || dest < 0 || dest >= vertices) {
                        cout << "Invalid vertex!\n";
                        i--;
                        continue;
                    }
                    
                    if (src == dest) {
                        cout << "Self-loops not allowed!\n";
                        i--;
                        continue;
                    }
                    
                    if (weight < 0) {
                        cout << "Invalid weight!\n";
                        i--;
                        continue;
                    }
                    
                    graph.addEdge(src, dest, weight);
                    cout << "Edge added successfully!\n";
                }
                break;
            }
            
            case 5:
                cout << "\nExiting program...\n";
                cout << "Thank you!\n";
                break;
            
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);
    
    return 0;
}
