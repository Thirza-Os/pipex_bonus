/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 14:00:48 by tosinga       #+#    #+#                 */
/*   Updated: 2022/04/05 14:00:49 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_malloc_check(void *s)
{
	if (s == 0)
	{
		ft_putstr_fd("Error\n", 1);
		exit(1);
	}
	return (s);
}

void	fork_error(void)
{
	perror("Fork did not succeed\n");
	exit (1);
}
