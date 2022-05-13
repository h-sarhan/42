/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:08:04 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/13 14:43:06 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	test_ft_lstnew()
{
	print_msg_color("\n---Testing ft_lstnew---\n", BLUE);
	
	t_list	*node;
	int num = 4;
	node = ft_lstnew(&num);

	assert_is_not_null("Node is not NULL: ", node);
	assert_int_equal("Node content has been set correctly: ", *(int *)node->content, 4);
	assert_is_null("Next node is NULL: ", node->next);
	free(node);
}

void	test_ft_lstadd_front()
{
	print_msg_color("\n---Testing ft_lstadd_front---\n", BLUE);

	t_list	*first;
	t_list	*node;
	int nums_in[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int	nums_out[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	first = ft_lstnew(&nums_in[0]);
	int i = 1;
	while (i < 10)
	{
		node = ft_lstnew(&nums_in[i]);
		ft_lstadd_front(&first, node);
		first = node;
		i++;
	}
	int	nums_in_list[10];
	i = 0;
	while (first != NULL)
	{
		nums_in_list[i] = *(int *)first->content;
		first = first->next;
		i++;
	}
	assert_int_array_equal("Check that all nodes have been added to the list properly: ",
			nums_in_list, nums_out, 10);
}
