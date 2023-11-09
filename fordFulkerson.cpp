#include <queue>
#include <cstring>
#include <iostream>
#define pii std::pair<int, int>
#define V 6
#define min(a, b) (a) < (b) ? (a) : (b)

int adj[V][V] = {{0, 16, 13, 0, 0, 0}, {0, 0, 10, 12, 0, 0}, {0, 4, 0, 0, 14, 0}, {0, 0, 9, 0, 0, 20}, {0, 0, 0, 7, 0, 4}, {0, 0, 0, 0, 0, 0}};

int parent[V];

bool bfs(int s, int t)
{
    bool visited[V];
    memset(visited, false, sizeof(visited));

    std::queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && adj[u][v] > 0)
            {
                parent[v] = u;
                if (v == t)
                    return true;
                visited[v] = true;
                q.push(v);
            }
        }
    }

    return false;
}

int fordFulkerson(int s, int t)
{
    int maxFlow = 0;

    while (bfs(s, t))
    {
        int pathFlow = __INT_MAX__;
        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            pathFlow = min(pathFlow, adj[u][v]);
        }

        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            adj[u][v] -= pathFlow;
            adj[v][u] += pathFlow;
        }
        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main()
{
    // Let us create a graph shown in the above example

    std::cout << "The maximum possible flow is "
              << fordFulkerson(0, 5);

    return 0;
}
