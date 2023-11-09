#include <queue>
#include <iostream>
#define pii std::pair<int, int>
std::vector<std::vector<pii>> adj;

std::vector<int> dijkstra(int src)
{
    int n = adj.size();
    std::vector<int> dist(n, __INT_MAX__);
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    dist[src] = 0;
    pq.push({dist[src], src});

    while (!pq.empty())
    {
        pii el = pq.top();
        pq.pop();

        int u = el.second;

        for (auto &pItr : adj[u])
        {
            int v = pItr.first;
            int weight = pItr.second;

            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

class Graph
{
public:
    Graph(int V); // Constructor

    // function to add an edge to graph
    void addEdge(int u, int v, int w);
};

// Allocates memory for adjacency list
Graph::Graph(int V)
{
    adj.resize(V);
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(std::make_pair(v, w));
    adj[v].push_back(std::make_pair(u, w));
}

int main()
{
    // create the graph given in above figure
    int V = 9;
    Graph g(V);

    // making above shown graph
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    // Function call
    auto res = dijkstra(0);

    for (int i = 0; i < res.size(); i++)
    {
        std::cout << i << " " << res[i] << "\n";
    }

    return 0;
}