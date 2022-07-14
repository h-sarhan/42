/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:04:53 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 14:05:11 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h" 
# include "printf/ft_printf.h" 

typedef struct s_stack
{
	struct s_stack	*prev;
	struct s_stack	*next;
	int				num;
}				t_stack;

// Stack
t_stack	*stack_new(int num);
void	stack_add_top(t_stack **lst, t_stack *new);
void	stack_add_bottom(t_stack **lst, t_stack *new);
void	stack_print(t_stack *lst);
void	stack_print_rev(t_stack *lst);

int		stack_size(t_stack *lst);
t_stack	*stack_bottom(t_stack *lst);
t_stack	*stack_top(t_stack *lst);
void	stack_delone(t_stack *lst);
void	stack_clear(t_stack **lst);

void	stack_iter(t_stack *lst, void (*f)(int));
t_stack	*stack_map(t_stack *lst, int (*f)(int));

// Stack
void	swap(t_stack **stack_a, t_stack **stack_b, char which);
void	push(t_stack **stack_a, t_stack **stack_b, char which);
void	rotate(t_stack **stack_a, t_stack **stack_b, char which);
void	reverse_rotate(t_stack **stack_a, t_stack **stack_b, char which);
void	move_to_bottom(t_stack *min);
void	move_to_top(t_stack *min);
void	stupid_sort(t_stack *stack_a, t_stack *stack_b);
int		is_sorted_desc(t_stack *stack);
int		is_sorted_asc(t_stack *stack);
void insertion_sort(t_stack *stack_a, t_stack *stack_b);
t_stack	*find_min(t_stack *list);
t_stack	*find_max(t_stack *list);
#endif