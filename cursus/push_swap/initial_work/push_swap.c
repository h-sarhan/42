/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 06:42:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/31 12:41:52 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Push swap
// * For testing: ./push_swap `ruby -e "puts (-50..50).to_a.shuffle.join(' ')"`
int	main(int argc, char **argv)
{
	t_stack	*stacks[2];
	int		chunk_size;

	stacks[0] = NULL;
	stacks[1] = NULL;
	if (argc == 1)
		return (EXIT_SUCCESS);
	fill_stack(&stacks[0], argv);
	get_final_positions(stacks[0]);
	if (is_sorted_asc(stacks[0]))
	{
		stack_clear(&stacks[0]);
		return (0);
	}
	if (stack_size(stacks[0]) <= 5)
		sort_small(&stacks[0], &stacks[1]);
	else
	{
		chunk_size = 0.1075 * stack_size(stacks[0]) + 6.25;
		chunk(&stacks[0], &stacks[1], chunk_size);
		sort_after_chunking(stacks);
	}
	stack_clear(&stacks[0]);
}
