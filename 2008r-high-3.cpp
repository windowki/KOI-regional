#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX2(x,y) x>y ? x:y

int n, list[505][3], d[505][505], a[505][505];

int main()
{
	int i, j, k, p;
	scanf("%d ", &n);
	for (i = 1; i <= n; i++)
		for (j = 0; j < 3; j++)
			scanf("%d ", &list[i][j]);
	for (i = 1; i < n; i++)
		for (j = i+1; j <= n; j++)
		{
			if (list[i][0] + list[i][1] >= list[j][0])
				a[i][j] = 1;
			if (list[j][2] * list[i][2] == 1 && list[j][0] - list[j][1] <= list[i][0])
				a[j][i] = 1;
		}

	//main dp
	for (i = n; i >= 1; i--)
		for (j = n; j >= 1; j--)
		{
			if (i == n || j == n)
			{
				d[i][j] = a[i][n]|a[n][j];
				continue;
			}
			p = MAX2(i, j);
			for (k = p + 1; k < n; k++)
				d[i][j] += a[i][k] * d[k][j] + a[k][j] * d[i][k];
			d[i][j] += a[i][n]*a[n][j];
			d[i][j] %= 1000;
		}
	printf("%d", d[1][1]);
	
	return 0;
}