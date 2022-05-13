/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:08:04 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/13 14:14:26 by hsarhan          ###   ########.fr       */
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
