#include<iostream>
#include<vector>

using namespace std;


struct qnode{
    int w;
    int n;
    int p;
};
// priority queue
class queue{
    vector<qnode*> q;
public:
    void insert(int w,int n,int p){
        qnode* node = new qnode{w,n,p};
        q.push_back(node);
    }
    qnode* pop(){
        if(q.empty()) return nullptr;
        int minIndex = 0;
        for(int i=1;i<q.size();i++){
            if(q[i]->w < q[minIndex]->w){
                minIndex = i;
            }
        }
        qnode* temp = q[minIndex];
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
    pair<int,vector<pair<int,int>>> MST(){
        vector<pair<int,int>> mstEdges;
        queue q1;
        int wt = 0;
        vector<bool> visited(V,false);
        q1.insert(0,0,-1); // weight,node,parent
        while(q1.size() > 0){
            qnode* temp = q1.pop();
            int u = temp->n;
            if(visited[u]) continue;
            visited[u] = true;
            wt += temp->w;
            if(temp->p != -1){
                mstEdges.push_back({temp->p,u});
            }
            // get all adjcent nodes of u
            for(pair<int,int>& neighbor : adj[u]){
                int v = neighbor.first;
                int w = neighbor.second;
                if(!visited[v]){
                    q1.insert(w,v,u);
                }
            }
        }
        return {wt,mstEdges};
    }
    void displayMST(){
        auto result = MST();
        int totalWeight = result.first;
        vector<pair<int,int>> edges = result.second;
        cout << "Total weight of MST: " << totalWeight << endl;
        cout << "Edges in the MST:" << endl;
        for(auto& edge : edges){
            cout << edge.first << " - " << edge.second << endl;
        }
    }
    void displayGraph(){
        for(int i=0;i<V;i++){
            cout << "Node " << i << ": ";
            for(auto& neighbor : adj[i]){
                cout << "(" << neighbor.first << ", weight: " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};

int main(){
    Graph g(5);
    g.addEdge(0,1,2);
    g.addEdge(0,3,6);
    g.addEdge(1,2,3);
    g.addEdge(1,3,8);
    g.addEdge(1,4,5);
    g.addEdge(2,4,7);
    g.addEdge(3,4,9);

    cout << "Graph representation:" << endl;
    g.displayGraph();

    cout << "\nMinimum Spanning Tree using Prim's Algorithm:" << endl;
    g.displayMST();

    return 0;
}