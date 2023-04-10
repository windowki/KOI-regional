#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int n;
long long a[305][2];
double p[305][305], peri, max_len[305], max_len1[305], max_len2[305];

double double_abs(double num)
{
	return num > 0 ? num : -num;
}

double process(int t1, int t2)
{
	int i, opp;
	double diag, peri1, peri2, temp, len;
	double maxi;

	diag = sqrt((double)((a[t1][0] - a[t2][0]) * (a[t1][0] - a[t2][0]) + (a[t1][1] - a[t2][1]) * (a[t1][1] - a[t2][1])));
	peri1=p[t1][t2]+diag, peri2=p[t2][t1]+diag, maxi = diag;
	
	//find max length from each point in t1~t2 cycle
	opp = t1, len = 0;
	for (i = t1; i <= t2; len -= p[i][i + 1], i++)
	{
		while (!(len > peri1 / 2))
		{
			opp++;
			if (opp > t2)
				opp = t1, len += diag;
			else
				len += p[opp - 1][opp];
		}
		temp = (opp == t1 ? diag : p[opp - 1][opp]);
		max_len1[i] = (len - temp > peri1 - len ? len - temp : peri1 - len);
		if (maxi < max_len1[i])
			maxi = max_len1[i];
	}
	//find max length from t2-t1 point to t1-t2 cycle
	for (i = t2; i != t1+1; i = i%n+1)
	{
		if (double_abs(p[t2][i] - p[i][t1]) > diag)
		{
			temp = (p[i][t1] + max_len1[t1] > p[t2][i] + max_len1[t2] ? p[t2][i] + max_len1[t2] : p[i][t1] + max_len1[t1]);
			if (maxi < temp)
				maxi = temp;
		}
		else
			if (maxi < max_len[i])
				maxi = max_len[i];
	}

	//find max length from each point in t2~t1 cycle
	opp = t2, len = 0;
	for (i = t2; i != t1 + 1; len -= p[i][i % n + 1], i = i % n + 1)
	{
		while (!(len > peri2 / 2))
		{
			opp = opp % n + 1;
			if (opp == t1 + 1)
				opp = t2, len += diag;
			else
				len += p[opp == 1 ? n : opp - 1][opp];
		}
		temp = (opp == t2 ? diag : p[opp == 1 ? n : opp - 1][opp]);
		max_len2[i] = (len - temp > peri2 - len ? len - temp : peri2 - len);
		if (maxi < max_len2[i])
			maxi = max_len2[i];
	}
	//find max length from t1-t2 point to t2-t1 cycle
	for (i = t1; i <= t2; i++)
	{
		if (double_abs(p[t1][i] - p[i][t2]) > diag)
		{
			temp = (p[i][t2] + max_len2[t2] > p[t1][i] + max_len2[t1] ? p[t1][i] + max_len2[t1] : p[i][t2] + max_len2[t2]);
			if (maxi < temp)
				maxi = temp;
		}
		else
			if (maxi < max_len[i])
				maxi = max_len[i];
	}
	return maxi;
}

int main()
{
	int i, j, t, t1, t2;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
		scanf("%lld %lld", &a[i][0], &a[i][1]);
	for (i = 1; i <= n; i++)
	{
		t = i % n + 1;
		p[i][t] = sqrt((double)((a[t][0] - a[i][0]) * (a[t][0] - a[i][0]) + (a[t][1] - a[i][1]) * (a[t][1] - a[i][1])));
		peri += p[i][t];
	}
	for (i = 1; i < n; i++)
		for (j = i + 1; j <= n; j++)
			p[i][j] = p[i][j-1]+p[j-1][j], p[j][i]=peri-p[i][j]; //always clockwise

	//find max length from each point in 1~n cycle
	int opp;
	double len, temp;
	opp = 1, len = 0;
	for (i = 1; i <= n; len -= p[i][i + 1], i++)
	{
		while (!(len > peri / 2))
		{
			opp++;
			if (opp > n)
				opp = 1, len += p[n][1];
			else
				len += p[opp - 1][opp];
		}
		temp = (opp == 1 ? p[n][1] : p[opp - 1][opp]);
		max_len[i] = (len - temp > peri - len ? len - temp : peri - len);
	}

	double mini = 9999999.9;
	temp = process(1, 4);
	for (i = 1; i < n; i++)
		for (j = i + 1; j <= n; j++)
		{
			if (j == i % n + 1 || i == j % n + 1)
				continue;
			temp = process(i, j);
			if (mini > temp)
				mini = temp, t1 = i, t2 = j;
		}
	printf("%lld %lld %lld %lld", a[t1][0], a[t1][1], a[t2][0], a[t2][1]);
	return 0;
}