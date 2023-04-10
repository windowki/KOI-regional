#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <algorithm>

using namespace std;
int n, p, a[100001], order[100001], ans[100001];
int tree[400001];

void tree_reset(int node)
{
	if (node)
	{
		tree[node]--;
		tree_reset(node / 2);
	}
}

int find_element(int node, int top)
{
	if (node >= p) //leaf node
	{
		tree_reset(node);
		return a[node - p + 1];
	}
	else
	{
		int left_count = tree[node * 2];
		if (top < left_count)
			return find_element(node * 2, top);
		else return find_element(node * 2 + 1, top - left_count);
	}
}

int main()
{
	int i;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
		scanf("%d ", &a[i]);
	for (i = 1; i <= n; i++)
		scanf("%d ", &order[i]);
	sort(a + 1, a + n + 1);
	
	p = 1;
	while (p <= n)
		p *= 2;
	for (i = p; i < p + n; i++)
		tree[i] = 1;
	for (i = p - 1; i >= 1; i--)
		tree[i] = tree[2 * i] + tree[2 * i + 1];

	for (i = n; i >= 1; i--)
		ans[i] = find_element(1, order[i]);
	for (i = 1; i <= n; i++)
		printf("%d\n", ans[i]);
	return 0;
}