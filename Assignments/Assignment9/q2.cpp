// Write a Program to implement Prim's algorithm to find minimum spanning tree
// of a user defined graph. Use Adjacency List to represent a graph.

#include <iostream>
#include <climits>
using namespace std;

// Forward declarations
struct EdgeNode;
class Graph;

// Node in adjacency list representing an edge
struct EdgeNode
{
    int vertex;     // Destination vertex
    int weight;     // Edge weight
    EdgeNode *next; // Next edge in the list
};

class Graph
{
private:
    int numVertices;
    EdgeNode **adjList; // Array of adjacency lists

    // Helper function to find vertex with minimum key value
    int findMinKey(int key[], bool inMST[])
    {
        int min = INT_MAX;
        int minIndex = -1;

        for (int v = 0; v < numVertices; v++)
        {
            if (!inMST[v] && key[v] < min)
            {
                min = key[v];
                minIndex = v;
            }
        }

        return minIndex;
    }

public:
    Graph(int vertices)
    {
        numVertices = vertices;
        adjList = new EdgeNode *[numVertices];

        // Initialize all adjacency lists as empty
        for (int i = 0; i < numVertices; i++)
        {
            adjList[i] = NULL;
        }
    }

    // Add edge to the graph (undirected graph)
    void addEdge(int src, int dest, int weight)
    {
        // Add edge from src to dest
        EdgeNode *newNode = new EdgeNode;
        newNode->vertex = dest;
        newNode->weight = weight;
        newNode->next = adjList[src];
        adjList[src] = newNode;

        // Add edge from dest to src (undirected graph)
        newNode = new EdgeNode;
        newNode->vertex = src;
        newNode->weight = weight;
        newNode->next = adjList[dest];
        adjList[dest] = newNode;
    }

    // Display the adjacency list
    void displayGraph()
    {
        cout << "\n========== Graph (Adjacency List) ==========\n";
        for (int i = 0; i < numVertices; i++)
        {
            cout << "Vertex " << i << ": ";
            EdgeNode *temp = adjList[i];

            if (temp == NULL)
            {
                cout << "No edges";
            }
            else
            {
                while (temp != NULL)
                {
                    cout << "(" << temp->vertex << ", W:" << temp->weight << ")";
                    if (temp->next != NULL)
                    {
                        cout << " -> ";
                    }
                    temp = temp->next;
                }
            }
            cout << endl;
        }
        cout << "============================================\n";
    }

    // Prim's algorithm to find MST
    void primMST()
    {
        // Arrays to store MST
        int parent[numVertices]; // Stores MST
        int key[numVertices];    // Key values to pick minimum weight edge
        bool inMST[numVertices]; // To track vertices included in MST

        // Initialize all keys as infinite and inMST as false
        for (int i = 0; i < numVertices; i++)
        {
            key[i] = INT_MAX;
            inMST[i] = false;
            parent[i] = -1;
        }

        // Start with vertex 0
        key[0] = 0;
        parent[0] = -1; // First node is root of MST

        cout << "\n========== Prim's Algorithm Steps ==========\n";

        // MST will have numVertices vertices
        for (int count = 0; count < numVertices; count++)
        {
            // Pick the minimum key vertex not yet in MST
            int u = findMinKey(key, inMST);

            if (u == -1)
            {
                cout << "\nGraph is not connected! Cannot form complete MST.\n";
                return;
            }

            // Add picked vertex to MST
            inMST[u] = true;

            cout << "\nStep " << (count + 1) << ": Selected vertex " << u;
            if (parent[u] != -1)
            {
                cout << " (Edge: " << parent[u] << " - " << u
                     << ", Weight: " << key[u] << ")";
            }
            else
            {
                cout << " (Starting vertex)";
            }
            cout << endl;

            // Update key values of adjacent vertices
            EdgeNode *temp = adjList[u];
            while (temp != NULL)
            {
                int v = temp->vertex;
                int weight = temp->weight;

                // Update key if weight is smaller and vertex is not in MST
                if (!inMST[v] && weight < key[v])
                {
                    parent[v] = u;
                    key[v] = weight;
                    cout << "  Updated key[" << v << "] = " << weight
                         << " (via vertex " << u << ")" << endl;
                }

                temp = temp->next;
            }
        }

        cout << "============================================\n";

        // Display the MST
        displayMST(parent, key);
    }

    // Display the Minimum Spanning Tree
    void displayMST(int parent[], int key[])
    {
        cout << "\n========== Minimum Spanning Tree ==========\n";
        cout << "Edge\t\tWeight\n";
        cout << "----\t\t------\n";

        int totalWeight = 0;

        for (int i = 1; i < numVertices; i++)
        {
            if (parent[i] != -1)
            {
                cout << parent[i] << " - " << i << "\t\t" << key[i] << endl;
                totalWeight += key[i];
            }
        }

        cout << "-------------------------------------------\n";
        cout << "Total Weight of MST: " << totalWeight << endl;
        cout << "===========================================\n";
    }

    // Visualize MST structure
    void visualizeMSTStructure(int parent[])
    {
        cout << "\n--- MST Structure ---\n";
        cout << "Vertex\t\tParent\n";
        cout << "------\t\t------\n";
        for (int i = 0; i < numVertices; i++)
        {
            cout << i << "\t\t";
            if (parent[i] == -1)
            {
                cout << "ROOT\n";
            }
            else
            {
                cout << parent[i] << endl;
            }
        }
        cout << "--------------------\n";
    }

    ~Graph()
    {
        // Free all edge nodes
        for (int i = 0; i < numVertices; i++)
        {
            EdgeNode *temp = adjList[i];
            while (temp != NULL)
            {
                EdgeNode *toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
        delete[] adjList;
    }
};

int main()
{
    int vertices, edges;

    cout << "================================================\n";
    cout << "  Prim's Algorithm - Minimum Spanning Tree\n";
    cout << "================================================\n";

    cout << "\nEnter number of vertices: ";
    cin >> vertices;

    if (vertices < 1)
    {
        cout << "Invalid number of vertices!\n";
        return 1;
    }

    Graph graph(vertices);

    cout << "Enter number of edges: ";
    cin >> edges;

    if (edges < 0)
    {
        cout << "Invalid number of edges!\n";
        return 1;
    }

    cout << "\nEnter edges (source destination weight):\n";
    cout << "(Vertices should be numbered from 0 to " << (vertices - 1) << ")\n";

    for (int i = 0; i < edges; i++)
    {
        int src, dest, weight;
        cout << "Edge " << (i + 1) << ": ";
        cin >> src >> dest >> weight;

        if (src < 0 || src >= vertices || dest < 0 || dest >= vertices)
        {
            cout << "Invalid vertex! Vertices must be between 0 and "
                 << (vertices - 1) << endl;
            i--;
            continue;
        }

        if (weight < 0)
        {
            cout << "Invalid weight! Weight must be non-negative.\n";
            i--;
            continue;
        }

        graph.addEdge(src, dest, weight);
    }

    int choice;

    do
    {
        cout << "\n========== Menu ==========\n";
        cout << "1. Display Graph (Adjacency List)\n";
        cout << "2. Find MST using Prim's Algorithm\n";
        cout << "3. Add More Edges\n";
        cout << "4. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            graph.displayGraph();
            break;

        case 2:
            graph.primMST();
            break;

        case 3:
        {
            int numNewEdges;
            cout << "How many edges to add? ";
            cin >> numNewEdges;

            cout << "\nEnter edges (source destination weight):\n";
            for (int i = 0; i < numNewEdges; i++)
            {
                int src, dest, weight;
                cout << "Edge " << (i + 1) << ": ";
                cin >> src >> dest >> weight;

                if (src < 0 || src >= vertices || dest < 0 || dest >= vertices)
                {
                    cout << "Invalid vertex!\n";
                    i--;
                    continue;
                }

                if (weight < 0)
                {
                    cout << "Invalid weight!\n";
                    i--;
                    continue;
                }

                graph.addEdge(src, dest, weight);
                cout << "Edge added successfully!\n";
            }
            break;
        }

        case 4:
            cout << "\nExiting program...\n";
            cout << "Thank you!\n";
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
