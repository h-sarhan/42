/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:28:56 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/08 09:52:20 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Writes a string to STDERR
void	write_to_stderror(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}
