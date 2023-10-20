#include <vector>
#include <cassert>

#define MAX_BITS 20
#define N 100005

int table[MAX_BITS][N];
int arr[N];

void build(int n)
{
    for (int i = 0; i < n; i++)
        table[0][i] = arr[i];

    for (int i = 1; i < MAX_BITS; i++)
        for (int j = 0; j < n; j++)
            table[i][j] = table[i - 1][table[i - 1][j]];
}

int lca(int u, int v)
{
    assert(u != v);

    for (int i = MAX_BITS - 1; i >= 0; i--)
    {
        int up = table[i][u], vp = table[i][v];
        if (up != vp)
        {
            u = up;
            v = vp;
        }
    }

    return table[0][u];
}