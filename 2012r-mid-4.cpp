#include <iostream>
#include <vector>

using namespace std;
int n, d[1000001];
bool visit[1000001];
vector<int> adj[1000001];

int dfs(int root) // size of optimal vertex cover of subtree with root root
{
    if (d[root] != -1) // already calculated
        return d[root];

    visit[root] = true;
    int i, j, son, grandson, sum_o = 1, sum_x = 0;
    for (i = 0; i < adj[root].size(); i++)
    {
        son = adj[root][i];
        if (!visit[son])
        {
            sum_o += dfs(son);
            sum_x += 1;
            for (j = 0; j < adj[son].size(); j++)
            {
                grandson = adj[son][j];
                if (!visit[grandson])
                    sum_x += dfs(grandson);
            }
        }
    }
    visit[root] = false;
    return d[root] = (sum_o < sum_x ? sum_o : sum_x);
}

int main()
{
    int i, u, v;
    cin >> n;
    for (i = 1; i < n; i++)
    {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        d[i] = -1;
    }
    d[n] = -1;
    cout << dfs(1);
    return 0;
}