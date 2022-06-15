#include "ft_list.h"
#include <printf.h>
#include <string.h>

void	print_str(void *p)
{
	char	*str;

	str = p;
	printf("%s\n", str);
}



int	main()
{
	// t_list	*list;
	// int	i;
	// int	nums[5];

	// list = NULL;
	// i = 0;
	// while (i < 5)
	// {
	// 	nums[i] = i + 1;
	// 	i++;
	// }
	// i = 0;
	// while (i < 5)
	// {
	// 	ft_list_push_front(&list, &nums[i]);
	// 	i++;
	// }
	// t_list	*list2;
	// list2 = list;
	// while (list2 != NULL)
	// {
	// 	printf("%d->", *(int *)list2->data);
	// 	list2 = list2->next;
	// }
	// printf("NULL\n");
	// printf("Size of list is %d\n", ft_list_size(list));

	// char *strs[] = {"hi", "world", "lkhnlkjn", "oimo"};

	// t_list	*str_list = ft_list_push_strs(4, strs);
	// while (str_list != NULL)
	// {

	// 	printf("[%s]->", (char *)str_list->data);
	// 	str_list = str_list->next;
	// }
	// printf("NULL\n");

	// char	*strs[] = {"abc", "def", "ghi", "gyug", "jytfytgv"};
	// t_list	*lst = ft_list_push_strs(5, strs);
	// ft_list_reverse(&lst);
	// while (lst != NULL)
	// {
	// 	printf("[%s]->", lst->data);
	// 	lst = lst->next;
	// }
	// printf("NULL\n");

	// char	*strs[] = {"abc", "def", "ghi", "gyug", "jytfytgv", "abc"};
	// t_list	*lst = ft_list_push_strs(6, strs);
	// ft_list_foreach_if(lst, print_str, "abc", strcmp);


}