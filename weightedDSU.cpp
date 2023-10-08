#include <vector>
#define pii std::pair<int, int>

class weightedDSU
{
private:
    std::vector<int> parent, rank, cost;
    pii find(int u)
    {
        int p = parent[u];
        if (p == u)
            return {p, 0};

        pii _ = find(u);
        parent[u] = _.first;
        cost[u] += _.second;
        return {parent[u], cost[u]};
    }

public:
    int addKnowledge(int u, int v, int val)
    {
        pii piiU = find(u);
        pii piiV = find(v);

        if (piiU.first == piiV.first)
            return -1;

        int pU = piiU.first, costU = piiU.second;
        int pV = piiV.first, costV = piiV.second;

        if (rank[pU] >= rank[pV])
        {
            if (rank[pU] == rank[pV])
                rank[pU]++;
            parent[pV] = pU;
            cost[pV] = costU - costV - val;
        }
        else
        {
            parent[pU] = pV;
            cost[pU] = val + costV - costU;
        }
        return 0;
    }

    int getKnowledge(int u, int v, int &status)
    {
        pii piiU = find(u), piiV = find(v);
        if (piiU.first != piiV.second)
        {
            status = -1;
            return 0;
        }
        status = 0;
        return piiU.second - piiV.second;
    }

    weightedDSU(/* args */) {}
    ~weightedDSU() {}
};
