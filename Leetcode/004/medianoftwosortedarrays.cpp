
#include <vector>
#include <climits>

inline int max(int a, int b)
{
    return a > b ? a : b;
}

inline int min(int a, int b)
{
    return a < b ? a : b;
}

double findMedian(std::vector<int> &arr1, std::vector<int> &arr2)
{
    if (arr1.size() > arr2.size())
        return findMedian(arr2, arr1);

    int m = arr1.size(), n = arr2.size();

    int low = 0, high = m;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        int index1 = mid;
        int index2 = (m + n + 1) / 2 - index1;

        int leftMax1 = index1 == 0 ? INT_MIN : arr1[index1 - 1];
        int leftMax2 = index2 == 0 ? INT_MIN : arr2[index2 - 1];

        int rightMin1 = index1 == m ? INT_MAX : arr1[index1];
        int rightMin2 = index2 == n ? INT_MAX : arr2[index2];

        if (leftMax1 <= rightMin2 && leftMax2 <= rightMin1)
        {
            if ((m + n) % 2)
                return max(leftMax1, leftMax2);
            else
            {
                double sum = max(leftMax1, leftMax2) + min(rightMin1, rightMin2);
                return sum / 2;
            }
        }
        if (leftMax1 > rightMin2)
            high = mid - 1;
        else
            low = mid + 1;
    }

    return -1;
}
