/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:04:46 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/15 12:15:41 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_stack	*stack_new(int num)
{
	t_stack	*node;

	node = ft_calloc(1, sizeof(t_stack));
	if (node == NULL)
		return (NULL);
	node->next = NULL;
	node->num = num;
	return (node);
}

void	stack_add_top(t_stack **lst, t_stack *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

void	stack_add_bottom(t_stack **lst, t_stack *new)
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
}

void	stack_print(t_stack *lst)
{
	// lst = lst;
	while (lst != NULL)
	{
		ft_printf("[%d]->", lst->num);
		lst = lst->next;
	}
	ft_printf("NULL\n");
}

int		main()
{
	int	nums[] = {-10, 10, 20, 30, 40, 50};
	t_stack	*stack = NULL;
	int i = 0;
	while (i < 6)
	{
		stack_add_top(&stack, stack_new(nums[i]));
		i++;
	}
	stack_print(stack);
	ft_printf("\n");
	ft_printf("SIZE == %d\n", stack_size(stack));
	ft_printf("FIRST ELEMENT == %d\n",stack->num);
	ft_printf("LAST ELEMENT == %d\n", stack_bottom(stack)->num);
}
