/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:04:53 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/31 12:43:16 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h" 
# include "printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include <stdbool.h>

// Stack
typedef struct s_stack
{
	struct s_stack	*next;
	int				num;
	int				final_idx;
}				t_stack;

// Stack Functions
t_stack	*stack_new(int num);
void	stack_add_bottom(t_stack **lst, t_stack *new);
int		stack_size(t_stack *lst);
t_stack	*stack_bottom(t_stack *lst);
void	stack_clear(t_stack **lst);

// Stack Moves
void	swap(t_stack **stack_a, t_stack **stack_b, char which);
void	push(t_stack **stack_a, t_stack **stack_b, char which);
void	rotate(t_stack **a, t_stack **b, char which, bool q);
void	reverse_rotate(t_stack **a, t_stack **b, char which, bool q);

// Utils
bool	is_sorted_asc(t_stack *stack);
t_stack	*find_min(t_stack *stack);
void	get_final_positions(t_stack *stack);
void	free_split_array(char **split_array);

// Sorting and Chunking
int		forward_dist(t_stack **stack, int desired_idx);
int		reverse_dist(t_stack **stack, int desired_idx);
void	chunk(t_stack **stack_a, t_stack **stack_b, int chunk_size);
void	sort_after_chunking(t_stack **stack_a);
void	sort_small(t_stack **stack_a, t_stack **stack_b);

// Parsing
long	ft_atol(const char *str);
int		*parse_args(char *arg_string, int *num_args);
char	*join_arg(const char *str1, const char *str2);
char	*arg_joiner(char **argv);
void	fill_stack(t_stack **stack, char **argv);

#endif