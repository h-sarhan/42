/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:04:53 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 05:49:07 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h" 
# include "printf/ft_printf.h" 

typedef struct s_dlist
{
	struct s_dlist	*prev;
	struct s_dlist	*next;
	int				num;
}				t_dlist;

// Doubly linked list
// dll1.c
t_dlist	*ft_dlstnew(int num);
void	ft_dlstadd_front(t_dlist **lst, t_dlist *new);
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
void	ft_dlst_print(t_dlist *lst);
void	ft_dlst_print_reverse(t_dlist *lst);

// dll2.c
int		ft_dlstsize(t_dlist *lst);
t_dlist	*ft_dlstlast(t_dlist *lst);
t_dlist	*ft_dlstfirst(t_dlist *lst);
void	ft_dlstdelone(t_dlist *lst);
void	ft_dlstclear(t_dlist **lst);

// dll3.c
void	ft_dlstiter(t_dlist *lst, void (*f)(int));
t_dlist	*ft_dlstmap(t_dlist *lst, int (*f)(int));

// Stack
void	swap(t_dlist **stack_a, t_dlist **stack_b, char which);
#endif