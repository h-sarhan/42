#include "ft_list.h"
#include <printf.h>
#include <string.h>

void	print_str(void *p)
{
	char	*str;

	str = p;
	printf("%s\n", str);
}

int	comp_int(void *num1, void *num2)
{
	if (*(int *)num1 > *(int *)num2)
		return (1);
	else if (*(int *)num1 == *(int *)num2)
		return (0);
	return (-1);
}

void print_int(void *p)
{
	printf("%d\n", *(int *)p);
}

int	main()
{
	int	arr[] = {64, 132, 4, -19, 132, 22, 1, -89880};
	t_list *list;

	list = NULL;
	int i = 0;
	while (i < 8)
	{
		ft_list_push_back(&list, &arr[i]);
		i++;
	}
	ft_list_sort(&list, comp_int);
	ft_list_foreach(list, print_int);
}

