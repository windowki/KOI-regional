#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int n, a[1005], idx[1005];
int path[5][2];

void reverse(int s, int e)
{
	int temp;
	while (s < e)
	{
		temp = a[s], a[s] = a[e], a[e] = temp;
		temp = idx[a[s]], idx[a[s]] = idx[a[e]], idx[a[e]] = temp;
		s++, e--;
	}
}

int completed(void)
{
	int i;
	for (i = 1; i <= n; i++)
		if (a[i] != i)
			return 0;
	return 1;
}

void process(int lev)
{
	int i, t1, t2, temp;
	if (completed())
	{
		for (i = 1; i < lev; i++)
			printf("%d %d\n", path[i][0], path[i][1]);
		for (i = lev; i <= 3; i++)
			printf("1 1\n");
		exit(0);
	}
	if (lev <= 3)
	{
		for (i = 1; i <= n + 1; i++)  //value, not index
			if (abs(idx[i] - idx[i - 1]) != 1)
			{
				if (i == 1)
				{
					t1 = 1, t2 = idx[1];
					path[lev][0] = t1, path[lev][1] = t2;
					reverse(t1, t2);
					process(lev + 1);
					reverse(t1, t2);
				}
				else if (i == n + 1)
				{
					t1 = idx[n], t2 = n;
					path[lev][0] = t1, path[lev][1] = t2;
					reverse(t1, t2);
					process(lev + 1);
					reverse(t1, t2);
				}
				else
				{
					t1 = idx[i], t2 = idx[i - 1];
					if (t1 > t2)
						temp = t1, t1 = t2, t2 = temp;

					path[lev][0] = t1, path[lev][1] = t2 - 1;
					reverse(t1, t2 - 1);
					process(lev + 1);
					reverse(t1, t2 - 1);

					path[lev][0] = t1 + 1, path[lev][1] = t2;
					reverse(t1 + 1, t2);
					process(lev + 1);
					reverse(t1 + 1, t2);
				}
			}
	}
}

int main()
{
	int i;
	scanf("%d", &n), a[0] = idx[0] = 0, a[n + 1] = idx[n + 1] = n + 1;
	for (i = 1; i <= n; i++)
		scanf("%d", &a[i]), idx[a[i]] = i;
	process(1);
	return 0;
}