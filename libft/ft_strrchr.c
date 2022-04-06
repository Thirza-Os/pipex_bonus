/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 14:08:44 by tosinga       #+#    #+#                 */
/*   Updated: 2022/04/05 14:08:45 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*str;
	int				i;
	unsigned char	d;

	d = c;
	i = ft_strlen(s);
	str = (char *)s;
	while (i >= 0)
	{
		if (s[i] == d)
			return (str + i);
		--i;
	}
	return (0);
}
