#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int n, a[105][2];
int p[105][105], max;

int find_area(int r, int c)
{
	int i, j, ubound=100, line_area, area=0, max_area=0, flag;
	for (i = r; i<=100 ; i++)
	{
		line_area=flag=0;
		for (j = c; j<=ubound ; j++)
		{
			line_area += p[i][j];
			if (!p[i][j])
			{
				flag = 1;
				break;
			}
		}
		if (flag)
		{
			if (max_area < area)
				max_area = area;
			ubound = j - 1;
			area = line_area * (i - r + 1);
		}
		else
			area += line_area;
	}
	return max_area;
}

void process(void)
{
	int i, j, area;
	for (i = 1; i <= 99; i++)
		for (j = 1; j <= 99; j++)
		{
			area = find_area(i,j);
			if (max < area)
				max = area;
		}
}

int main()
{
	int i, j, k;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		scanf("%d %d", &a[i][0], &a[i][1]);
		for (j = a[i][0]; j < a[i][0] + 10; j++)
			for (k = a[i][1]; k < a[i][1] + 10; k++)
				p[j][k] = 1;
	}
	process();
	printf("%d", max);
	return 0;
}