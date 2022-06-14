#include "ft_list.h"
#include <printf.h>

int	main()
{
	t_list	*list;
	int	i;
	int	nums[5];

	list = NULL;
	i = 0;
	while (i < 5)
	{
		nums[i] = i + 1;
		i++;
	}
	i = 0;
	while (i < 5)
	{
		ft_list_push_front(&list, &nums[i]);
		i++;
	}
	t_list	*list2;
	list2 = list;
	while (list2 != NULL)
	{
		printf("%d->", *(int *)list2->data);
		list2 = list2->next;
	}
	printf("NULL\n");
	printf("Size of list is %d\n", ft_list_size(list));

	char *strs[] = {"hi", "world", "lkhnlkjn", "oimo"};

	t_list	*str_list = ft_list_push_strs(4, strs);
	while (str_list != NULL)
	{

		printf("[%s]->", (char *)str_list->data);
		str_list = str_list->next;
	}
	printf("NULL\n");
}