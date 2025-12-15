#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct edgenode{
    int u;
    int v;
    int w;
};

class disjointSet{
    vector<int> parent;
    vector<int> rank;
public:
    disjointSet(int n){
        parent.resize(n);
        rank.resize(n,0);
        for(int i=0;i<n;i++){
            parent[i] = i;
        }
    }
    int find(int u){
        if (u == parent[u])
            return u;
        return parent[u] = find(parent[u]);
    }
    void unionSets(int u, int v){
        int uRoot = find(u);
        int vRoot = find(v);
        if(uRoot == vRoot) return;
        if(rank[uRoot] < rank[vRoot]){
            parent[uRoot] = vRoot;
        }
        else if(rank[uRoot] > rank[vRoot]){
            parent[vRoot] = uRoot;
        }
        else{
            parent[vRoot] = uRoot;
            rank[uRoot]++;
        }
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
    pair<int,vector<edgenode>> MST(){
        vector<edgenode> edges;
        for(int u=0;u<V;u++){
            for(auto& p : adj[u]){
                int v = p.first;
                int w = p.second;
                if(u < v){ // to avoid duplicate edges
                    edges.push_back({u,v,w});
                }
            }
        }
        sortEdges(edges);
        disjointSet ds(V);
        vector<edgenode> mstEdges;
        int totalWeight = 0;
        for(auto& edge : edges){
            int u = edge.u;
            int v = edge.v;
            int w = edge.w;
            if(ds.find(u) != ds.find(v)){
                ds.unionSets(u,v);
                mstEdges.push_back(edge);
                totalWeight += w;
            }
        }
        return {totalWeight, mstEdges};
    }
    void sortEdges(vector<edgenode>& edges){
        sort(edges.begin(), edges.end(), [](edgenode& a, edgenode& b){
            return a.w < b.w;
        });
    }

    void displayMST(){
        auto result = MST();
        int totalWeight = result.first;
        vector<edgenode> edges = result.second;
        cout << "Total weight of MST: " << totalWeight << endl;
        cout << "Edges in the MST:" << endl;
        for(auto& edge : edges){
            cout << edge.u << " -- " << edge.v << " == " << edge.w << endl;
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
    g.addEdge(0,1,2);
    g.addEdge(0,3,6);
    g.addEdge(1,2,3);
    g.addEdge(1,3,8);
    g.addEdge(1,4,5);
    g.addEdge(2,4,7);
    g.addEdge(3,4,9);

    cout << "Graph representation:" << endl;
    g.displayGraph();

    cout << "\nMinimum Spanning Tree using Kruskal's Algorithm:" << endl;
    g.displayMST();

    return 0;
}