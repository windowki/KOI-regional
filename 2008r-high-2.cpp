#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX2(x,y) x>y ? x:y

int a, b, d, n;
int s[1000005], birth[1000005], birth_sum[1000005];

int thousand(int num)
{
	while (num < 0)
		num += 1000;
	while (num >= 1000)
		num -= 1000;
	return num;
}

int main()
{
	int i;
	scanf("%d %d %d %d", &a, &b, &d, &n);
	s[0] = 1, birth[0] = birth_sum[0] = 1;
	for (i = 1; i <= n; i++)
	{
		if (i >= a)
			birth[i] = birth_sum[i - a];
		if (i >= b)
			birth[i] = birth_sum[i - a] - birth_sum[i - b];

		s[i] = s[i - 1] + birth[i];
		if (i >= d)
			s[i] -= birth[i - d];
		
		s[i] = thousand(s[i]);
		birth[i] = thousand(birth[i]);
		birth_sum[i] = thousand(birth_sum[i - 1] + birth[i]);
	}
	printf("%d", s[n]);
	return 0;
}