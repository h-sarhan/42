/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:04:53 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 11:10:42 by hsarhan          ###   ########.fr       */
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

// Doubly linked list
// dll1.c
t_stack	*ft_dlstnew(int num);
void	ft_dlstadd_front(t_stack **lst, t_stack *new);
void	ft_dlstadd_back(t_stack **lst, t_stack *new);
void	ft_dlst_print(t_stack *lst);
void	ft_dlst_print_reverse(t_stack *lst);

// dll2.c
int		ft_dlstsize(t_stack *lst);
t_stack	*ft_dlstlast(t_stack *lst);
t_stack	*ft_dlstfirst(t_stack *lst);
void	ft_dlstdelone(t_stack *lst);
void	ft_dlstclear(t_stack **lst);

// dll3.c
void	ft_dlstiter(t_stack *lst, void (*f)(int));
t_stack	*ft_dlstmap(t_stack *lst, int (*f)(int));

// Stack
void	swap(t_stack **stack_a, t_stack **stack_b, char which);
void	push(t_stack **stack_a, t_stack **stack_b, char which);
void	rotate(t_stack **stack_a, t_stack **stack_b, char which);
void	reverse_rotate(t_stack **stack_a, t_stack **stack_b, char which);
t_stack	*find_min(t_stack *list);
#endif