#include <vector>
#include <math.h>
#define max(a, b) (a) > (b) ? (a) : (b)
class sparseTable
{
private:
    std::vector<std::vector<int>> table;
    int m, n;

    void build(std::vector<int> &arr)
    {
        for (int i = 0; i < n; i++)
            table[0][i] = arr[i];

        for (int i = 1; (1 << i) <= n; i++)
        {
            int size = 1 << i;
            for (int j = 0; j + size <= n; j++)
                table[i][j] = max(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
        }
    }

public:
    sparseTable(std::vector<int> &arr)
    {
        n = arr.size();
        build(arr);
    }
    ~sparseTable() {}

    int query(int start, int end)
    {
        int l = end - start + 1;
        l = log2(l);

        return max(table[l][start], table[l][end - (1 << l) + 1]);
    }
};
