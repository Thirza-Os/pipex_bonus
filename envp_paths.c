/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp_paths.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 13:59:57 by tosinga       #+#    #+#                 */
/*   Updated: 2022/04/05 17:00:20 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strnstr_last(const char *haystack, \
			const char *needle, size_t len)
{
	unsigned long	a;
	unsigned long	b;

	a = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[a] && len > a)
	{
		if (haystack[a] == needle[0])
		{
			b = 0;
			while (haystack[a + b] == needle[b] && needle[b] && (a + b) < len)
			{
				if (needle[b + 1] == '\0')
					return ((char *)&haystack[b + 1]);
				b++;
			}
		}
		a++;
	}
	return (0);
}

void	envp_paths(t_vars *vars, char **envp)
{
	int		i;
	char	*start;
	int		len;

	i = 0;
	start = NULL;
	while (envp[i] && start == NULL)
	{
		len = ft_strlen(envp[i]);
		start = ft_strnstr_last(envp[i], "PATH=", len);
		i++;
	}
	vars->paths = ft_malloc_check(ft_split_add_slash(start, ':'));
}
