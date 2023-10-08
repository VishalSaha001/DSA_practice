#include <vector>

class twoDsegmentTree
{
private:
    std::vector<std::vector<int>> segTree;
    int m, n;
    void buildy(int ix, int startx, int endx, int iy, int starty, int endy, std::vector<std::vector<int>> &mat)
    {
        if (starty == endy)
        {
            if (startx == endx)
                segTree[ix][iy] = mat[startx][starty];
            else
                segTree[ix][iy] = segTree[2 * ix + 1][starty] + segTree[2 * ix + 2][iy];
            return;
        }
        int midy = starty + (endy - starty) / 2;
        buildy(ix, startx, endx, 2 * iy + 1, starty, midy, mat);
        buildy(ix, startx, endx, 2 * iy + 2, midy + 1, endy, mat);
        segTree[ix][iy] = segTree[ix][2 * iy + 1] + segTree[ix][2 * iy + 2];
    }

    void buildx(int ix, int startx, int endx, std::vector<std::vector<int>> &mat)
    {
        if (startx == endx)
        {
            buildy(ix, startx, endx, 0, 0, n - 1, mat);
            return;
        }

        int midx = startx + (endx - startx) / 2;
        buildx(2 * ix + 1, startx, midx, mat);
        buildx(2 * ix + 2, midx + 1, endx, mat);
        buildy(ix, startx, endx, 0, 0, n - 1, mat);
    }

    int queryy(int ix, int iy, int starty, int endy, int qsy, int qey)
    {
        if (endy < qsy || qey < starty)
            return 0;

        if (qsy <= starty && endy <= qey)
            return segTree[ix][iy];

        int midy = starty + (endy - starty) / 2;
        return queryy(ix, 2 * iy + 1, starty, midy, qsy, qey) + queryy(ix, 2 * iy + 2, midy + 1, endy, qsy, qey);
    }

    int queryx(int ix, int startx, int endx, int qsx, int qex, int qsy, int qey)
    {
        if (endx < qsx || qex < startx)
            return 0;
        if (qsx <= startx && endx <= qex)
            return queryy(ix, 0, 0, n - 1, qsy, qey);

        int midx = startx + (endx - startx) / 2;
        return queryx(2 * ix + 1, startx, midx, qsx, qex, qsy, qey) + queryx(2 * ix + 2, midx + 1, endx, qsx, qex, qsy, qey);
    }

    void updatey(int ix, int iy, int starty, int endy, int indexy, int val)
    {
        if (starty == endy)
        {
            segTree[ix][iy] = val;
            return;
        }

        int midy = starty + (endy - starty) / 2;
        if (indexy <= midy)
            updatey(ix, 2 * iy + 1, starty, midy, indexy, val);
        else
            updatey(ix, 2 * iy + 2, midy + 1, endy, indexy, val);

        segTree[ix][iy] = segTree[ix][2 * iy + 1] + segTree[ix][2 * iy + 2];
    }

    void updatex(int ix, int startx, int endx, int indexx, int indexy, int val)
    {
        if (startx == endx)
        {
            updatey(ix, 0, 0, n - 1, indexx, val);
            return;
        }

        int midx = startx + (endx - startx) / 2;
        if (indexx <= midx)
            updatex(2 * ix + 1, startx, midx, indexx, indexy, val);
        else
            updatex(2 * ix + 2, midx + 1, endx, indexx, indexy, val);

        updatey(ix, 0, 0, n - 1, indexy, val);
    }

public:
    twoDsegmentTree(std::vector<std::vector<int>> &mat)
    {
        m = mat.size();
        n = mat[0].size();
        segTree = std::vector<std::vector<int>>(4 * m, std::vector<int>(4 * n));
        buildx(0, 0, n - 1, mat);
    }
    ~twoDsegmentTree()
    {
    }

    int query(int qsx, int qsy, int qex, int qey)
    {
        return queryx(0, 0, m - 1, qsx, qex, qsy, qey);
    }

    void update(int indexx, int indexy, int val)
    {
        updatex(0, 0, m - 1, indexx, indexy, val);
    }
};
