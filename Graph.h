#include<iostream>
#include <list>
#include <set>
#include <string>
using namespace std;
# define INF 0x3f3f3f3f

// ============================================================================
// Graph class.
// ============================================================================
class Graph {
    int V;
    list< pair<int, int> > *adj;
 
public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void shortestPath(int s);
};

// ============================================================================
// Constructor.
// ============================================================================
Graph::Graph(int V) {
    this->V = V;
    adj = new list< pair<int, int> >[V];
}

// ============================================================================
// Adds a new edge.
// ============================================================================ 
void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

// ============================================================================
// Prints shortest paths from src to all other vertices
// ============================================================================
void Graph::shortestPath(int src) {
    set< pair<int, int> > setds;
    vector<int> dist(V, INF);
    setds.insert(make_pair(0, src));
    dist[src] = 0;
 
    while (!setds.empty())
    {
        pair<int, int> tmp = *(setds.begin());
        setds.erase(setds.begin());
 
        int u = tmp.second;
 
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;
 
            if (dist[v] > dist[u] + weight)
            {
                if (dist[v] != INF)
                    setds.erase(setds.find(make_pair(dist[v], v)));
 
                dist[v] = dist[u] + weight;
                setds.insert(make_pair(dist[v], v));
            }
        }
    }
 
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; ++i) {
        string city = "";
        switch (i) {
            case 0:
                city = "SFO";
                break;
            case 1:
                city = "DFW";
                break;
            case 2:
                city = "LAX";
                break;
            case 3:
                city = "ORD";
                break;
            case 4:
                city = "JFK";
                break;
            case 5:
                city = "MIA";
                break;
            case 6:
                city = "BOS";
                break;
        }
        cout << city << "\t\t" << dist[i] << endl;
    }
}