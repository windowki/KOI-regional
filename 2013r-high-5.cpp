#include <iostream>

using namespace std;
int n, v;
int a[101][1001], len[101], p[1001], fail[1001];

int main()
{
    int i, j, k, match;
    bool flag_i, flag;
    cin >> n >> v;
    for (i = 1; i <= n; i++)
    {
        cin >> len[i];
        for (j = 1; j <= len[i]; j++)
            cin >> a[i][j];
    }

    for (k = 1; k <= len[1] - v + 1; k++)
    {
        // new pattern
        for (i = 1; i <= v; i++)
            p[i] = a[1][k + i - 1];

        // calculate failure function
        fail[1] = 0;
        for (i = 2; i <= v; i++)
        {
            j = fail[i - 1];
            while (j && p[j + 1] != p[i])
                j = fail[j];
            if (p[j + 1] == p[i])
                fail[i] = j + 1;
            else
                fail[i] = 0;
        }
        // cout << "pattern: ";
        // for (i = 1; i <= v; i++)
        //     cout << p[i] << ' ';
        // cout << endl;
        // cout << "failure function: ";
        // for (i = 1; i <= v; i++)
        //     cout << fail[i] << ' ';
        // cout << endl;

        for (i = 2; i <= n; i++)
        {
            // kmp for forward
            match = 0;
            flag_i = false;
            for (j = 1; j <= len[i]; j++)
            {
                while (match && p[match + 1] != a[i][j])
                    match = fail[match];
                if (p[match + 1] == a[i][j])
                {
                    match++;
                    if (match == v)
                    {
                        flag_i = true;
                        break;
                    }
                }
            }
            if (flag_i) // find p in a[i]
                continue;

            // kmp for backward
            match = 0;
            flag_i = false;
            for (j = len[i]; j >= 1; j--)
            {
                while (match && p[match + 1] != a[i][j])
                    match = fail[match];
                if (p[match + 1] == a[i][j])
                {
                    match++;
                    if (match == v)
                    {
                        flag_i = true;
                        break;
                    }
                }
            }
            if (!flag_i) // no p in a[i] -> p is not virus
                break;
        }
        if (i == n + 1)
        {
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    return 0;
}