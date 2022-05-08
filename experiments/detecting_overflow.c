#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

// From https://stackoverflow.com/questions/199333/how-do-i-detect-unsigned-integer-overflow
void	check_for_overflow(int x, char op, int y)
{
	bool overflow = false;
	if (op == '+')
	{
		overflow = y > 0 && x > INT_MAX - y || y < 0 && x < INT_MIN - y;
	}
	else if (op == '-')
	{
		overflow = y < 0 && x > INT_MAX + y || y > 0 && x < INT_MIN + y;
	}
	else if (op == '*')
	{
		overflow = y == -1 && x == INT_MIN || x == -1 && y == INT_MIN
			|| x > INT_MAX / y || x < INT_MIN / y;
	}
	if (overflow)
		printf("Overflow detected with operation %d %c %d\n", x, op, y);
	else
		printf("Operation successful\n");
}

int	main()
{
	printf("INT_MAX = %d\n", INT_MAX);
	printf("INT_MIN = %d\n\n", INT_MIN);

	int	x = INT_MIN + 10;
	int	y = -11;
	printf("x = %d\ny = %d\n", x, y);
	check_for_overflow(x, '+', y);
	int res = x + y;
	printf("Result is %d\n", res);
}

