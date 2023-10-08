#include <vector>

class lazySegmentTree
{
private:
    std::vector<int> segTree, lazy;
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
        if (lazy[i])
        {
            segTree[i] += (end - start + 1) * lazy[i];
            if (start != end)
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }
        if (end < qs || qe < start)
            return 0;

        if (qs <= start && end <= qe)
            return segTree[i];

        int mid = start + (end - start) / 2;
        return query(2 * i + 1, start, mid, qs, qe) + query(2 * i + 2, mid + 1, end, qs, qe);
    }

    void update(int i, int start, int end, int qs, int qe, int inc)
    {
        if (lazy[i])
        {
            segTree[i] += (end - start + 1) * lazy[i];
            if (start != end)
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }
        if (end < qs || qe < start)
            return;

        if (qs <= start && end <= qe)
        {
            segTree[i] += (end - start + 1) * inc;
            if (start != end)
            {
                lazy[2 * i + 1] += inc;
                lazy[2 * i + 2] += inc;
            }
            return;
        }

        int mid = start + (end - start) / 2;

        update(2 * i + 1, start, mid, qs, qe, inc);
        update(2 * i + 2, mid + 1, end, qs, qe, inc);
        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
    }

public:
    lazySegmentTree(std::vector<int> &arr)
    {
        n = arr.size();
        segTree = std::vector<int>(4 * n);
        lazy = std::vector<int>(4 * n);
        build(0, 0, n - 1, arr);
    }
    ~lazySegmentTree()
    {
    }

    int query(int qs, int qe)
    {
        return query(0, 0, n - 1, qs, qe);
    }

    void update(int qs, int qe, int val)
    {
        update(0, 0, n - 1, qs, qe, val);
    }
};
