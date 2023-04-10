#include <iostream>

using namespace std;
int n, a[500001], b[500001], b_idx[1000001], seg[1048576], p=1;
long long sum;

int find_sum(int root, int left, int right, int key)
{
    if (left > key) // [left, right] in (key, n]
        return seg[root];
    else if (right <= key)
        return 0;
    else
        return find_sum(root * 2, left, (left + right) / 2, key) + find_sum(root * 2 + 1, (left + right) / 2 + 1, right, key);
}

int main()
{
    int i, idx;
    cin >> n;
    for (i = 1; i <= n; i++)
        cin >> a[i];
    for (i = 1; i <= n; i++)
        cin >> b[i], b_idx[b[i]] = i;

    while (p < n)
        p *= 2;
    for (i = 1; i <= n; i++)
    {
        idx = b_idx[a[i]];
        sum += find_sum(1, 1, p, idx); // count > idx
        // update segment tree
        idx += p - 1;
        while (idx)
        {
            seg[idx]++;
            idx /= 2;
        }
    }
    cout << sum;
    return 0;
}