#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <algorithm>

using namespace std;
typedef pair<pair<int, int>, int > ppair;
int n, m, root[100001], card[100001]; //cardinality of set whose root is i
long long int connected_pair, sum;
ppair e[100001];


bool compare(ppair& x, ppair& y)
{
	return (x.second > y.second);
}

int find_root(int v)
{
	if (v == root[v])
		return v;
	return root[v] = find_root(root[v]); //compress path
}

int main()
{
	int i;
	scanf("%d %d", &n, &m);
	for (i = 1; i <= m; i++)
		scanf("%d %d %d", &e[i].first.first, &e[i].first.second, &e[i].second);
	sort(e + 1, e + m + 1, compare);
	for (i = 1; i <= n; i++)
		root[i] = i, card[i] = 1;

	int v1, v2;
	for (i = 1; i <= m; i++)
	{
		v1 = find_root(e[i].first.first);
		v2 = find_root(e[i].first.second);
		if (v1 != v2)
		{
			root[v2] = v1;
			connected_pair += ((long long int) card[v1]) * card[v2];
			connected_pair %= 1000000000;
			card[v1] += card[v2];
		}
		sum += connected_pair * e[i].second;
		sum %= 1000000000;
	}
	printf("%lld", sum);
	return 0;
}