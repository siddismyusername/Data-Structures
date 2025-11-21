// Write a Program to implement Dijkstra's algorithm to find shortest distance
// between two nodes of a user defined graph. Use Adjacency List to represent a graph.

#include <iostream>
#include <climits>
using namespace std;

// Forward declarations
struct EdgeNode;
class Graph;

// Node in adjacency list representing an edge
struct EdgeNode {
    int vertex;      // Destination vertex
    int weight;      // Edge weight
    EdgeNode* next;  // Next edge in the list
};

class Graph {
private:
    int numVertices;
    EdgeNode** adjList;  // Array of adjacency lists
    
    // Helper function to find vertex with minimum distance
    int findMinDistance(int dist[], bool visited[]) {
        int min = INT_MAX;
        int minIndex = -1;
        
        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && dist[v] < min) {
                min = dist[v];
                minIndex = v;
            }
        }
        
        return minIndex;
    }
    
    // Print the shortest path from source to destination
    void printPath(int parent[], int dest) {
        if (parent[dest] == -1) {
            cout << dest;
            return;
        }
        
        printPath(parent, parent[dest]);
        cout << " -> " << dest;
    }
    
public:
    Graph(int vertices) {
        numVertices = vertices;
        adjList = new EdgeNode*[numVertices];
        
        // Initialize all adjacency lists as empty
        for (int i = 0; i < numVertices; i++) {
            adjList[i] = NULL;
        }
    }
    
    // Add edge to the graph (directed graph)
    void addEdge(int src, int dest, int weight, bool bidirectional = false) {
        // Add edge from src to dest
        EdgeNode* newNode = new EdgeNode;
        newNode->vertex = dest;
        newNode->weight = weight;
        newNode->next = adjList[src];
        adjList[src] = newNode;
        
        // If bidirectional, add edge from dest to src
        if (bidirectional) {
            newNode = new EdgeNode;
            newNode->vertex = src;
            newNode->weight = weight;
            newNode->next = adjList[dest];
            adjList[dest] = newNode;
        }
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
        cout << "============================================\n";
    }
    
    // Dijkstra's algorithm to find shortest path
    void dijkstra(int source, int destination) {
        if (source < 0 || source >= numVertices || 
            destination < 0 || destination >= numVertices) {
            cout << "Invalid source or destination vertex!\n";
            return;
        }
        
        // Arrays for Dijkstra's algorithm
        int* dist = new int[numVertices];      // Shortest distance from source
        bool* visited = new bool[numVertices]; // Visited vertices
        int* parent = new int[numVertices];    // To store shortest path
        
        // Initialize all distances as infinite and visited as false
        for (int i = 0; i < numVertices; i++) {
            dist[i] = INT_MAX;
            visited[i] = false;
            parent[i] = -1;
        }
        
        // Distance from source to itself is 0
        dist[source] = 0;
        
        cout << "\n========== Dijkstra's Algorithm Steps ==========\n";
        cout << "Source: " << source << ", Destination: " << destination << endl;
        cout << "================================================\n";
        
        // Find shortest path for all vertices
        for (int count = 0; count < numVertices; count++) {
            // Pick minimum distance vertex not yet processed
            int u = findMinDistance(dist, visited);
            
            if (u == -1) {
                // No more reachable vertices
                break;
            }
            
            // Mark the picked vertex as visited
            visited[u] = true;
            
            cout << "\nStep " << (count + 1) << ": Selected vertex " << u 
                 << " (Distance: ";
            if (dist[u] == INT_MAX) {
                cout << "INF";
            } else {
                cout << dist[u];
            }
            cout << ")" << endl;
            
            // Update distances of adjacent vertices
            EdgeNode* temp = adjList[u];
            bool hasUpdates = false;
            
            while (temp != NULL) {
                int v = temp->vertex;
                int weight = temp->weight;
                
                // Update distance if not visited and shorter path found
                if (!visited[v] && dist[u] != INT_MAX && 
                    dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    
                    cout << "  Updated dist[" << v << "] = " << dist[v] 
                         << " (via vertex " << u << ")" << endl;
                    hasUpdates = true;
                }
                
                temp = temp->next;
            }
            
            if (!hasUpdates) {
                cout << "  No updates to distances" << endl;
            }
            
            // Early termination if destination is processed
            if (u == destination) {
                cout << "\nDestination vertex reached! Early termination.\n";
                break;
            }
        }
        
        cout << "================================================\n";
        
        // Display result
        displayShortestPath(source, destination, dist, parent);
        
        // Cleanup
        delete[] dist;
        delete[] visited;
        delete[] parent;
    }
    
    // Display shortest path and distance
    void displayShortestPath(int source, int destination, int dist[], int parent[]) {
        cout << "\n========== Shortest Path Result ==========\n";
        
        if (dist[destination] == INT_MAX) {
            cout << "No path exists from vertex " << source 
                 << " to vertex " << destination << endl;
        } else {
            cout << "Shortest distance from " << source << " to " 
                 << destination << ": " << dist[destination] << endl;
            
            cout << "\nPath: ";
            printPath(parent, destination);
            cout << endl;
        }
        
        cout << "==========================================\n";
    }
    
    // Display shortest paths from source to all vertices
    void dijkstraAll(int source) {
        if (source < 0 || source >= numVertices) {
            cout << "Invalid source vertex!\n";
            return;
        }
        
        int* dist = new int[numVertices];
        bool* visited = new bool[numVertices];
        int* parent = new int[numVertices];
        
        // Initialize
        for (int i = 0; i < numVertices; i++) {
            dist[i] = INT_MAX;
            visited[i] = false;
            parent[i] = -1;
        }
        
        dist[source] = 0;
        
        cout << "\n========== Dijkstra's Algorithm (All Paths) ==========\n";
        cout << "Source: " << source << endl;
        
        // Process all vertices
        for (int count = 0; count < numVertices; count++) {
            int u = findMinDistance(dist, visited);
            
            if (u == -1) break;
            
            visited[u] = true;
            
            // Update distances
            EdgeNode* temp = adjList[u];
            while (temp != NULL) {
                int v = temp->vertex;
                int weight = temp->weight;
                
                if (!visited[v] && dist[u] != INT_MAX && 
                    dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
                
                temp = temp->next;
            }
        }
        
        // Display all shortest paths
        cout << "\n--- Shortest Paths from vertex " << source << " ---\n";
        cout << "Destination\tDistance\tPath\n";
        cout << "-----------\t--------\t----\n";
        
        for (int i = 0; i < numVertices; i++) {
            cout << i << "\t\t";
            
            if (dist[i] == INT_MAX) {
                cout << "INF\t\tNo path";
            } else {
                cout << dist[i] << "\t\t";
                printPath(parent, i);
            }
            cout << endl;
        }
        
        cout << "======================================================\n";
        
        delete[] dist;
        delete[] visited;
        delete[] parent;
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
    }
};

int main() {
    int vertices, edges;
    char graphType;
    
    cout << "================================================\n";
    cout << "  Dijkstra's Algorithm - Shortest Path\n";
    cout << "================================================\n";
    
    cout << "\nEnter number of vertices: ";
    cin >> vertices;
    
    if (vertices < 1) {
        cout << "Invalid number of vertices!\n";
        return 1;
    }
    
    Graph graph(vertices);
    
    cout << "Is the graph directed or undirected? (D/U): ";
    cin >> graphType;
    
    bool bidirectional = (graphType == 'U' || graphType == 'u');
    
    cout << "Enter number of edges: ";
    cin >> edges;
    
    if (edges < 0) {
        cout << "Invalid number of edges!\n";
        return 1;
    }
    
    cout << "\nEnter edges (source destination weight):\n";
    cout << "(Vertices should be numbered from 0 to " << (vertices - 1) << ")\n";
    
    for (int i = 0; i < edges; i++) {
        int src, dest, weight;
        cout << "Edge " << (i + 1) << ": ";
        cin >> src >> dest >> weight;
        
        if (src < 0 || src >= vertices || dest < 0 || dest >= vertices) {
            cout << "Invalid vertex! Vertices must be between 0 and " 
                 << (vertices - 1) << endl;
            i--;
            continue;
        }
        
        if (weight < 0) {
            cout << "Invalid weight! Dijkstra's algorithm requires non-negative weights.\n";
            i--;
            continue;
        }
        
        graph.addEdge(src, dest, weight, bidirectional);
    }
    
    int choice;
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Display Graph (Adjacency List)\n";
        cout << "2. Find Shortest Path (Source to Destination)\n";
        cout << "3. Find Shortest Paths (Source to All)\n";
        cout << "4. Add More Edges\n";
        cout << "5. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                graph.displayGraph();
                break;
            
            case 2: {
                int source, destination;
                cout << "Enter source vertex: ";
                cin >> source;
                cout << "Enter destination vertex: ";
                cin >> destination;
                
                graph.dijkstra(source, destination);
                break;
            }
            
            case 3: {
                int source;
                cout << "Enter source vertex: ";
                cin >> source;
                
                graph.dijkstraAll(source);
                break;
            }
            
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
                    
                    if (weight < 0) {
                        cout << "Invalid weight! Must be non-negative.\n";
                        i--;
                        continue;
                    }
                    
                    graph.addEdge(src, dest, weight, bidirectional);
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
