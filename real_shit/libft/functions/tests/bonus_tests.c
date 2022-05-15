/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:08:04 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/15 13:51:12 by hsarhan          ###   ########.fr       */
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
	assert_int_equal("Node content has been set correctly: ", *(int *)node->content, num);
	assert_is_null("Next node is NULL: ", node->next);
	free(node);
}

void	do_nothing(void *something)
{
	(void) something;
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
	ft_lstclear(&first, &do_nothing);
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
	ft_lstclear(&first, &do_nothing);
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
	ft_lstclear(&first, &do_nothing);
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
	ft_lstclear(&first, &do_nothing);
}

void	free_num(void *num)
{
	print_msg_color("Freeing ", WHITE);
	test_util_putnbr(*(int *)num, WHITE);
	write(1, "\n" RESET, 6);
	free(num);
}

void	test_ft_lstdelone()
{
	print_msg_color("\n---Testing ft_lstdelone---\n", BLUE);

	int	*num = malloc(sizeof(int));
	*num = 42;
	t_list	*node = ft_lstnew(num);
	
	print_msg_color("Should just free the element 42: \n", YELLOW);
	ft_lstdelone(node, &free_num);
}


void	test_ft_lstclear()
{
	print_msg_color("\n---Testing ft_lstclear---\n", BLUE);
	int *nums_in[10];
	int i = 0;
	while (i < 10)
	{
		nums_in[i] = malloc(sizeof(int));
		*nums_in[i] = i;
		i++;
	}
	t_list *first = ft_lstnew(nums_in[0]);
	i = 1;
	while (i < 10)
	{
		t_list *node = ft_lstnew(nums_in[i]);
		ft_lstadd_back(&first, node);
		i++;
	}
	print_msg_color("Should free elements of the list (should be 0 to 9): \n", YELLOW);
	ft_lstclear(&first, &free_num);
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

void	*add_one_to_int(void *void_num)
{
	int	*num;

	num = malloc(sizeof(int));
	*num = *(int*)void_num + 1;
	return (num);
}


void	test_ft_lstmap()
{
	print_msg_color("\n---Testing ft_lstmap---\n", BLUE);
	
	t_list	*first;
	t_list	*node;
	int *nums_in[10];
	int i = 0;
	while (i < 10)
	{
		nums_in[i] = malloc(sizeof(int));
		*nums_in[i] = i;
		i++;
	}
	first = ft_lstnew(nums_in[0]);
	i = 1;
	while (i < 10)
	{
		node = ft_lstnew(nums_in[i]);
		ft_lstadd_back(&first, node);
		i++;
	}
	print_msg_color("Freeing elements of old list: (should be 0 to 9) \n", YELLOW);
	t_list *new_list = ft_lstmap(first, &add_one_to_int, &free_num);
	print_msg_color("Printing elements of new list (should be 1 to 10): \n", YELLOW);
	ft_lstiter(new_list, &print_int);
	print_msg_color("\nThis should free the elements of the new list (1 to 10): \n", YELLOW);
	ft_lstclear(&new_list, &free_num);
	int	*element = malloc(sizeof(int));
	*element = 41;
	node = ft_lstnew(element);
	print_msg_color("This should free the element 41:\n", YELLOW);
	new_list = ft_lstmap(node, &add_one_to_int, &free_num);
	print_msg_color("This should free the element 42:\n", YELLOW);
	ft_lstclear(&new_list, &free_num);
}
