#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <memory.h>

long long int n, smaller, bigger;
int digit[71], length;
int digit_smaller[71], digit_bigger[71];

int main()
{
	int i;
	scanf("%lld", &n);
	while (n)
	{
		digit[length++] = n % 2;
		n /= 2;
	}
	memcpy(digit_smaller, digit, sizeof(digit));
	memcpy(digit_bigger, digit, sizeof(digit));
	
	//smaller
	int count = 0, index = -1;
	for (i = 0; i < length; i++)
	{
		if (!digit_smaller[i])
			count++;
		else if (count)
		{
			index = i;
			digit_smaller[i] = 0;
			count--;
			break;
		}
	}
	if (index == -1)
		printf("0 ");
	else
	{
		for (i = 0; i < count; i++)
			digit_smaller[i] = 0;
		for (i = count; i < index; i++)
			digit_smaller[i] = 1;

		long long int pow = 1;
		for (i = 0; i < length; i++)
			smaller += pow * digit_smaller[i], pow *= 2;
		printf("%lld ", smaller);
	}

	//bigger
	count = 0;
	for (i = 0; i <= length; i++)
	{
		if (digit_bigger[i])
			count++;
		else if (count)
		{
			index = i;
			digit_bigger[i] = 1;
			count--;
			break;
		}
	}
	for (i = 0; i < count; i++)
		digit_bigger[i] = 1;
	for (i = count; i < index; i++)
		digit_bigger[i] = 0;

	long long int pow = 1;
	for (i = 0; i <= length; i++)
		bigger += pow * digit_bigger[i], pow *= 2;
	printf("%lld ", bigger);
	return 0;
}