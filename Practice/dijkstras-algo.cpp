#include<iostream>
#include<vector>
#include<climits>

using namespace std;

struct edgenode{
    int u;
    int v;
    int w;
};

// priority queue
class queue{
    vector<edgenode*> q;
public:
    void insert(int u,int v,int w){
        edgenode* node = new edgenode{u,v,w};
        q.push_back(node);
    }
    edgenode* pop(){
        if(q.empty()) return nullptr;
        int minIndex = 0;
        for(int i=1;i<q.size();i++){
            if(q[i]->w < q[minIndex]->w){
                minIndex = i;
            }
        }
        edgenode* temp = q[minIndex];
        q.erase(q.begin() + minIndex);
        return temp;
    }
    int size(){
        return q.size();
    }
};

class Graph{
    int V;
    vector<vector<pair<int,int>>> adj; // pair<node,weight>
public:
    Graph(int v){
        V = v;
        adj.resize(V);
    }
    void addEdge(int u,int v,int w){
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    vector<pair<int,int>> dijkstra(int src){
        queue q1;
        vector<int> dist(V,INT_MAX);
        dist[src] = 0;
        q1.insert(src,-1,0); // u,v,w
        while(q1.size() > 0){
            edgenode* temp = q1.pop();
            int u = temp->u;
            for(auto& p : adj[u]){
                int v = p.first;
                int w = p.second;
                if(dist[u] + w < dist[v]){
                    dist[v] = dist[u] + w;
                    q1.insert(v,u,dist[v]);
                }
            }
        }
        vector<pair<int,int>> result; // pair<node,distance>
        for(int i=0;i<V;i++){
            result.push_back({i,dist[i]});
        }
        return result;
    }

    void displayDijkstra(int src){
        auto result = dijkstra(src);
        cout << "Shortest distances from source node " << src << ":\n";
        for(auto& p : result){
            cout << "Node " << p.first << " : Distance = " << p.second << endl;
        }
    }
    void displayGraph(){
        for(int u=0;u<V;u++){
            cout << u << ": ";
            for(auto& p : adj[u]){
                cout << "(" << p.first << ", " << p.second << ") ";
            }
            cout << endl;
        }
    }
};

int main(){
    Graph g(5);
    g.addEdge(0,1,10);
    g.addEdge(0,2,3);
    g.addEdge(1,2,1);
    g.addEdge(1,3,2);
    g.addEdge(2,1,4);
    g.addEdge(2,3,8);
    g.addEdge(2,4,2);
    g.addEdge(3,4,7);
    g.addEdge(4,3,9);

    cout << "Graph representation:" << endl;
    g.displayGraph();

    cout << "\nDijkstra's Shortest Path from source node 0:" << endl;
    g.displayDijkstra(0);

    return 0;
}