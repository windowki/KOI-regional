#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <memory.h>
#define INF 99999

int n, m, adj[101][101], check[101];
int queue[10001], front, rear, dist[101];
int count, head[101], check_head[101];

void group(int v)
{
	int i, j, node;
	count++;
	front = rear = 0;
	queue[++rear] = v, check[v] = count;
	do {
		front++;
		node = queue[front];
		for (i = 1; i <= n; i++)
			if (adj[node][i] && !check[i])
				queue[++rear] = i, check[i] = count;
	} while (front != rear);

	int min = INF, max;
	for(i=1 ; i<=n ; i++)
		if (check[i] == count)
		{
			memset(dist,0,sizeof(dist));
			front = rear = max = 0;
			queue[++rear] = i, dist[i] = 1;
			do {
				front++;
				node = queue[front];
				for (j = 1; j <= n; j++)
					if (adj[node][j] && !dist[j])
					{
						queue[++rear] = j, dist[j] = dist[node] + 1;
						if (max < dist[j])
							max = dist[j];
					}
			} while (front!=rear);
			if (min > max)
				min = max, head[count] = i;
		}
}

int main()
{
	int i, v1, v2;
	scanf("%d %d", &n, &m);
	for (i = 1; i <= m; i++)
		scanf("%d %d", &v1, &v2), adj[v1][v2] = adj[v2][v1] = 1;

	for (i = 1; i <= n; i++)
		if (!check[i])
			group(i);

	printf("%d\n", count);
	for (i = 1; i <= count; i++)
		check_head[head[i]] = 1;
	for (i = 1; i <= n; i++)
		if(check_head[i])
			printf("%d\n", i);
	return 0;
}