/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:04:53 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/26 14:17:05 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h" 
# include "printf/ft_printf.h"
# include "get_next_line/get_next_line.h"

typedef struct s_stack
{
	struct s_stack	*next;
	int				num;
	int				idx;
	int				final_idx;
}				t_stack;

// Stack
t_stack	*stack_new(int num);
void	stack_add_top(t_stack **lst, t_stack *new);
void	stack_add_bottom(t_stack **lst, t_stack *new);
void	stack_print(t_stack *lst);

int		stack_size(t_stack *lst);
t_stack	*stack_bottom(t_stack *lst);


// Stack
void	swap(t_stack **stack_a, t_stack **stack_b, char which);
void	push(t_stack **stack_a, t_stack **stack_b, char which);
void	rotate(t_stack **stack_a, t_stack **stack_b, char which, int q);
void	reverse_rotate(t_stack **stack_a, t_stack **stack_b, char which, int q);
void	move_to_bottom(t_stack *min);
// void	move_to_top(t_stack *min);
void	stupid_sort(t_stack *stack_a, t_stack *stack_b);
int		is_sorted_desc(t_stack *stack);
int		is_sorted_asc(t_stack *stack);
void	insertion_sort(t_stack **stack_a, t_stack **stack_b);
t_stack	*find_min(t_stack *stack);
t_stack	*find_max(t_stack *stack);
int		kind_of_sorted_asc(t_stack *stack);
int		kind_of_sorted_desc(t_stack *stack);
void	partition_start(t_stack **stack_a, t_stack **stack_b);
void	print_stacks_side_by_side(t_stack *stack_a, t_stack *stack_b);

void	experiment(t_stack *stack);
// void	bubble_sort_stack(t_stack **stack, char which);
void	bubble_sort_stack(t_stack **stacka, t_stack** stackb, char which);
void	get_final_positions(t_stack *stack);
void	chunk(t_stack **stack_a, t_stack **stack_b, int chunk_size);
void	sort_after_chunking(t_stack **stack_a, t_stack **stack_b, int chunk_size);
#endif