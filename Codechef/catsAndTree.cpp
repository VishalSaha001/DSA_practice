#include <bits/stdc++.h>
using namespace std;
#define getT  \
    int t;    \
    cin >> t; \
    while (t--)
#define ll long long int
#define ipair pair<int, int>
#define pb push_back
#define getArr(arr, n)          \
    int n;                      \
    cin >> n;                   \
    int arr[n];                 \
    for (int i = 0; i < n; i++) \
    cin >> arr[i]
#define MAX_BITS 19

int table[MAX_BITS][300005];

void build(int parent[], int n)
{
    for (int j = 1; j <= n; j++)
        table[0][j] = parent[j];

    for (int i = 1; i < MAX_BITS; i++)
    {
        for (int j = 1; j <= n; j++)
            table[i][j] = table[i - 1][table[i - 1][j]];
    }
}

int query(int node, bool visited[])
{
    int res = 1;
    if (visited[node] == true)
        return 0;

    for (int i = MAX_BITS - 1; i >= 0; i--)
    {
        int p = table[i][node];
        if (visited[p] == false)
        {
            res += (1 << i);
            node = p;
        }
    }
    visited[node] = true;

    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int parent[n + 1];
    for (int i = 1; i <= n; i++)
        cin >> parent[i];

    build(parent, n);

    bool visited[n + 1];
    memset(visited, false, sizeof(visited));

    visited[0] = true;
    for (int i = 0; i < n; i++)
    {
        int node;
        cin >> node;

        cout << query(node, visited) << "\n";
    }
    return 0;
}