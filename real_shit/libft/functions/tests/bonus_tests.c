/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:08:04 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/13 18:08:13 by hsarhan          ###   ########.fr       */
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
	print_msg_color("This is not being freed i'm sorry\n", YELLOW);
}

void	test_ft_lstsize()
{
	print_msg_color("\n---Testing ft_lstsize---\n", BLUE);
	
	
	t_list	*first;
	t_list	*node;
	int nums_in[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	first = ft_lstnew(&nums_in[0]);
	int i = 1;
	while (i < 10)
	{
		node = ft_lstnew(&nums_in[i]);
		ft_lstadd_front(&first, node);
		first = node;
		i++;
	}
	
	assert_int_equal("Check that the number of nodes is correct : ", ft_lstsize(first), 10);
	print_msg_color("This is not being freed i'm sorry\n", YELLOW);
}

void	test_ft_lstlast()
{
	print_msg_color("\n---Testing ft_lstlast---\n", BLUE);
	
	t_list	*first;
	t_list	*node;
	int nums_in[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	first = ft_lstnew(&nums_in[0]);
	int i = 1;
	while (i < 10)
	{
		node = ft_lstnew(&nums_in[i]);
		ft_lstadd_front(&first, node);
		first = node;
		i++;
	}
	assert_int_equal("Check that the last node has been retreived: ", *(int *)ft_lstlast(first)->content, 0);
	print_msg_color("This is not being freed i'm sorry\n", YELLOW);
}

void	test_ft_lstadd_back()
{
	print_msg_color("\n---Testing ft_lstadd_back---\n", BLUE);

	t_list	*first;
	t_list	*node;
	int nums_in[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int nums_out[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	first = ft_lstnew(&nums_in[0]);
	int i = 1;
	while (i < 10)
	{
		node = ft_lstnew(&nums_in[i]);
		ft_lstadd_back(&first, node);
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
	print_msg_color("This is not being freed i'm sorry\n", YELLOW);
}

void	test_ft_lstdelone()
{
	print_msg_color("\n---Testing ft_lstdelone---\n", BLUE);
	print_msg_color("Test this later\n", YELLOW);
}


void	test_ft_lstclear()
{
	print_msg_color("\n---Testing ft_lstclear---\n", BLUE);
	print_msg_color("Test this later\n", YELLOW);
}

void	print_int(void *num)
{
	ft_putnbr_fd(*(int *)num, 1);
	ft_putstr_fd(", ", 1);
}

void	test_ft_lstiter()
{
	print_msg_color("\n---Testing ft_lstiter---\n", BLUE);

	t_list	*first;
	t_list	*node;
	int nums_in[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	first = ft_lstnew(&nums_in[0]);
	int i = 1;
	while (i < 10)
	{
		node = ft_lstnew(&nums_in[i]);
		ft_lstadd_back(&first, node);
		i++;
	}
	print_msg_color("This should print numbers from 0 to 9: \n", YELLOW);
	ft_lstiter(first, &print_int);
}


void	test_ft_lstmap()
{
	print_msg_color("\n---Testing ft_lstmap---\n", BLUE);
	print_msg_color("Test this later\n", YELLOW);

}
