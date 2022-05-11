#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int	main()
{
	FILE *fp = fopen("tests/test_output/putnbr.result", "w");
	int num = INT_MIN;
	while (num < INT_MIN + 1000)
	{
		fprintf(fp, "%d\n", num);
		num++;
	}
	num = -1000;
	while (num < 1000)
	{
		fprintf(fp, "%d\n", num);
		num++;
	}
	num = INT_MAX - 1000;
	while (num < INT_MAX)
	{
		fprintf(fp, "%d\n", num);
		num++;
	}
	fprintf(fp, "%d\n", num);
	fclose(fp);
}
