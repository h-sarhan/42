/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:04:46 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 11:10:42 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_stack	*ft_dlstnew(int num)
{
	t_stack	*node;

	node = ft_calloc(1, sizeof(t_stack));
	if (node == NULL)
		return (NULL);
	node->prev = NULL;
	node->next = NULL;
	node->num = num;
	return (node);
}

void	ft_dlstadd_front(t_stack **lst, t_stack *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	(*lst)->prev = new;
	new->next = *lst;
	*lst = new;
}

void	ft_dlstadd_back(t_stack **lst, t_stack *new)
{
	t_stack	*back;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	back = *lst;
	while (back->next != NULL)
		back = back->next;
	back->next = new;
	new->prev = back;
}

void	ft_dlst_print(t_stack *lst)
{
	while (lst != NULL)
	{
		ft_printf("[%d]->", lst->num);
		lst = lst->next;
	}
	ft_printf("NULL\n");
}

void	ft_dlst_print_reverse(t_stack *lst)
{
	if (lst == NULL)
		return ;
	while (lst->next != NULL)
		lst = lst->next;
	ft_printf("NULL");
	while (lst != NULL)
	{
		ft_printf("<-[%d]", lst->num);
		lst = lst->prev;
	}
	ft_printf("\n");
}

// int		main()
// {
// 	int	nums[] = {-10, 10, 20, 30, 40, 50};
// 	t_dlist	*list = NULL;
// 	int i = 0;
// 	while (i < 6)
// 	{
// 		ft_dlstadd_back(&list, ft_dlstnew(&nums[i]));
// 		i++;
// 	}
// 	ft_dlst_print_ints(list);
// 	ft_printf("\n");
// 	ft_dlst_print_ints_reverse(list);
// 	ft_printf("SIZE == %d\n", ft_dlstsize(list));
// 	ft_printf("FIRST ELEMENT == %d\n",*(int *) ft_dlstfirst(list)->content);
// 	ft_printf("LAST ELEMENT == %d\n", *(int *)ft_dlstlast(list)->content);
// }
