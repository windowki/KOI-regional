#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <algorithm>

using namespace std;
typedef pair<int, pair<int, int> > ppair;
int n, m, a[505][505], d[505][505];
ppair p[250005], temp;

bool compare(ppair x, ppair y)
{
	return x.first > y.first;
}

int main()
{
	int i, j, x, y;
	scanf("%d %d", &n, &m);
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
		{
			scanf("%d ", &a[i][j]);
			temp = ppair(a[i][j], pair<int, int>(i, j));
			p[(i - 1) * m + j] = temp;
		}
	sort(p + 1, p + n * m + 1, compare);
	
	d[1][1] = 1;
	for (i = 1; i <= n * m; i++)
	{
		x = p[i].second.first, y = p[i].second.second;
		if (a[x][y] < a[x - 1][y])
			d[x][y] += d[x - 1][y];
		if (a[x][y] < a[x + 1][y])
			d[x][y] += d[x + 1][y];
		if (a[x][y] < a[x][y - 1])
			d[x][y] += d[x][y - 1];
		if (a[x][y] < a[x][y + 1])
			d[x][y] += d[x][y + 1];
	}
	printf("%d", d[n][m]);
	return 0;
}