/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 14:07:52 by tosinga       #+#    #+#                 */
/*   Updated: 2022/04/05 14:07:53 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*my_b;

	my_b = b;
	while (len > 0)
	{
		*my_b = c;
		len--;
		my_b++;
	}
	return (b);
}
