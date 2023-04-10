#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int n;
char a[100002], b[100002], c[100002], w[100002];
int ab, bc, ca;

int MAX3(int x, int y, int z)
{
	if (x >= y && x >= z)
		return x;
	else if (y >= z)
		return y;
	else
		return z;
}

int main()
{
	int i;
	scanf("%s %s %s ", &a[1], &b[1], &c[1]);
	n = strlen(&a[1]);
	for (i = 1; i <= n; i++)
	{
		if (a[i] == b[i] && b[i] == c[i])
			w[i] = a[i]; // 'aaa'
		else if (a[i] == b[i])
			ab++; // 1 1 0 or 0 0 1
		else if (b[i] == c[i])
			bc++; // 0 1 1 or 1 0 0
		else if (c[i] == a[i])
			ca++; // 1 0 1 or 0 1 0
	}

	// 'aab', 'aba', 'baa'
	int bound, assign_major;
	if (ab == MAX3(ab, bc, ca))
	{
		bound = (bc >= ca ? ab + bc : ab + ca);
		bound = (bound + 1) / 2; //round up
		assign_major = 0;
		for (i = 1; i <= n; i++)
			if (w[i] == 0) //exclude 'aaa'
			{
				if (b[i] == c[i] || c[i] == a[i])
				{
					w[i] = c[i];
				}
				else if (a[i] == b[i])
				{
					if (assign_major <= bound)
						w[i] = a[i], assign_major++;
					else
						w[i] = c[i];
				}
			}
	}
	else if (bc == MAX3(ab, bc, ca))
	{
		bound = (ca >= ab ? bc + ca : bc + ab);
		bound = (bound + 1) / 2; //round up
		assign_major = 0;
		for (i = 1; i <= n; i++)
			if (w[i] == 0) //exclude 'aaa'
			{
				if (c[i] == a[i] || a[i] == b[i])
				{
					w[i] = a[i];
				}
				else if (b[i] == c[i])
				{
					if (assign_major <= bound)
						w[i] = b[i], assign_major++;
					else
						w[i] = a[i];
				}
			}
	}
	else
	{
		bound = (ab >= bc ? ca + ab : ca + bc);
		bound = (bound + 1) / 2; //round up
		assign_major = 0;
		for (i = 1; i <= n; i++)
			if (w[i] == 0) //exclude 'aaa'
			{
				if (a[i] == b[i] || b[i] == c[i])
				{
					w[i] = b[i];
				}
				else if (c[i] == a[i])
				{
					if (assign_major <= bound)
						w[i] = c[i], assign_major++;
					else
						w[i] = b[i];
				}
			}
	}
	// 'abc'
	int dist_a, dist_b, dist_c, max_dist;
	dist_a = dist_b = dist_c = 0;
	for (i = 1; i <= n; i++)
		if (w[i])
		{
			dist_a += (a[i] != w[i]);
			dist_b += (b[i] != w[i]);
			dist_c += (c[i] != w[i]);
		}
	for (i = 1; i <= n; i++)
		if (w[i] == 0)
		{
			max_dist = MAX3(dist_a, dist_b, dist_c);
			if (dist_a == max_dist)
			{
				w[i] = a[i];
				dist_b++, dist_c++;
			}
			else if (dist_b == max_dist)
			{
				w[i] = b[i];
				dist_c++, dist_a++;
			}
			else
			{
				w[i] = c[i];
				dist_a++, dist_b++;
			}
		}

	max_dist = MAX3(dist_a, dist_b, dist_c);
	printf("%d\n%s", max_dist, &w[1]);
	return 0;
}