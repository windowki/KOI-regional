#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#define INF -9999999

using namespace std;
int n, m, l;
int d[1005][505], ans;
char c[1005];
vector<pair<int, char>> a[505];

void process(void)
{
	int i, j, k, len, prev;
	for (i = 2; i <= m; i++)
		d[0][i] = INF;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
		{
			d[i][j]=INF;
			len = a[j].size();
			for (k = 0; k < len; k++)
			{
				prev = d[i - 1][a[j][k].first];
				if (prev == INF)
					continue;

				if (a[j][k].second == c[i] && d[i][j] < prev + 10)
					d[i][j] = prev + 10;
				else if(d[i][j] < prev)
					d[i][j] = prev;
			}
		}
	for (i = 1; i <= m; i++)
		if (ans < d[n][i])
			ans = d[n][i];
}


int main()
{
	int i, t1, t2;
	char t3;
	scanf("%d ", &n);
	for (i = 1; i <= n; i++)
		scanf("%c ", &c[i]);
	scanf("%d %d", &m, &l);
	for (i = 1; i <= l; i++)
	{
		scanf("%d %d %c ", &t1, &t2, &t3);
		a[t1].push_back(make_pair(t2,t3));
		a[t2].push_back(make_pair(t1,t3));
	}
	process();
	printf("%d", ans);
	return 0;
}