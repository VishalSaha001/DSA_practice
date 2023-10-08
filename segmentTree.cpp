#include <vector>

class segmentTree
{
private:
    std::vector<int> segTree;
    int n;
    void build(int i, int start, int end, std::vector<int> &arr)
    {
        if (start == end)
        {
            segTree[i] = arr[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * i + 1, start, mid, arr);
        build(2 * i + 2, mid + 1, end, arr);
        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
    }

    int query(int i, int start, int end, int qs, int qe)
    {
        if (end < qs || qe < start)
            return 0;

        if (qs <= start && end <= qe)
            return segTree[i];

        int mid = start + (end - start) / 2;
        return query(2 * i + 1, start, mid, qs, qe) + query(2 * i + 2, mid + 1, end, qs, qe);
    }

    void update(int i, int start, int end, int index, int val)
    {
        if (start == end)
        {
            segTree[i] = val;
            return;
        }

        int mid = start + (end - start) / 2;
        if (index <= mid)
            update(2 * i + 1, start, mid, index, val);
        else
            update(2 * i + 2, mid + 1, end, index, val);

        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
    }

public:
    segmentTree(std::vector<int> &arr)
    {
        n = arr.size();
        segTree = std::vector<int>(4 * n);
        build(0, 0, n - 1, arr);
    }
    ~segmentTree()
    {
    }

    int query(int qs, int qe)
    {
        return query(0, 0, n - 1, qs, qe);
    }

    void update(int index, int val)
    {
        update(0, 0, n - 1, index, val);
    }
};
