#include <vector>

class fenwickTree
{
private:
    std::vector<int> fTree;
    int n;

public:
    void update(int index, int val)
    {
        index++;
        while (index <= n)
        {
            fTree[index] += val;
            index += index & (-index);
        }
    }

    int query(int index)
    {
        index++;
        int sum = 0;
        while (index)
        {
            sum += fTree[index];
            index -= index & (-index);
        }
        return sum;
    }
    int query(int start, int end)
    {
        return query(end) - query(start - 1);
    }

    fenwickTree(std::vector<int> &arr)
    {
        n = arr.size();
        fTree = std::vector<int>(n + 1);
        for (int i = 0; i < n; i++)
            update(i, arr[i]);
    }
    ~fenwickTree()
    {
    }
};
