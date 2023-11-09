#include <queue>
#include <iostream>
#include <cstring>
#define pii std::pair<int, int>
std::vector<std::vector<pii>> adj;

int parent[10];

int prim(int src)
{
    int totalCost = 0;

    int n = adj.size();
    bool visited[n];
    memset(visited, false, sizeof(visited));

    std::vector<int> cost(n, __INT_MAX__);
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    cost[src] = 0;
    pq.push({cost[src], src});
    while (!pq.empty())
    {
        pii el = pq.top();
        pq.pop();

        int u = el.second;
        totalCost += el.first;
        visited[u] = true;

        for (auto &pItr : adj[u])
        {
            int v = pItr.first;
            int weight = pItr.second;

            if (!visited[v] && cost[v] > weight)
            {
                cost[v] = weight;
                parent[v] = u;
                pq.push({cost[v], v});
            }
        }
    }

    return totalCost;
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

    //  making above shown graph
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

    std::cout << prim(0) << "\n";

    for (int i = 1; i < V; ++i)
        printf("%d - %d\n", parent[i], i);
    return 0;
}