/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 06:42:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 11:10:42 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main()
{
	int	nums[] = {2, 1, 3, 6, 5, 8};
	t_stack	*stack_a = NULL;
	t_stack	*stack_b = NULL;
	int i = 0;
	while (i < 6)
		ft_dlstadd_back(&stack_a, ft_dlstnew(nums[i++]));


	ft_printf("%d\n", find_min(stack_a)->num);
	// ! EXAMPLE SORT
	// swap(&stack_a, &stack_b, 'a');
	// push(&stack_a, &stack_b, 'b');
	// push(&stack_a, &stack_b, 'b');
	// push(&stack_a, &stack_b, 'b');
	// rotate(&stack_a, &stack_b, 'c');
	// reverse_rotate(&stack_a, &stack_b, 'c');
	// swap(&stack_a, &stack_b, 'a');
	// push(&stack_a, &stack_b, 'a');
	// push(&stack_a, &stack_b, 'a');
	// push(&stack_a, &stack_b, 'a');
	// ft_dlst_print(stack_a);
	// ft_dlst_print(stack_b);
}
