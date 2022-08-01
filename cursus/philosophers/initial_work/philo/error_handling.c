/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:28:56 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 12:31:12 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Writes a string to STDERR
void	write_to_stderror(const char *msg)
{
	if (write(STDERR_FILENO, msg, ft_strlen(msg)) == FAIL)
	{
		exit(EXIT_FAILURE);
	}
}
