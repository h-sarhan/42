/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:28:56 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 14:22:42 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Writes a string to STDERR
void	write_to_stderror(const char *msg, bool *success)
{
	if (write(STDERR_FILENO, msg, ft_strlen(msg)) == FAIL && success != NULL)
		*success = false;
	else if (success != NULL)
		*success = true;
}
