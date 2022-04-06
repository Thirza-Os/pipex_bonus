/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   childs_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 13:59:44 by tosinga       #+#    #+#                 */
/*   Updated: 2022/04/06 10:54:25 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	find_path(t_vars *vars, char **splitted, char **envp, int i)
{
	char	*cmd_tot;
	int		free_counter;

	free_counter = 0;
	cmd_tot = ft_strjoin(vars->paths[i], splitted[0]);
	if (access(cmd_tot, 0) == 0)
	{
		ft_free(vars->paths);
		free(vars->cmd);
		while (vars->split_cmd[free_counter])
		{
			if (vars->split_cmd[free_counter] != splitted)
				ft_free(vars->split_cmd[free_counter]);
			free_counter++;
		}
		execve(cmd_tot, splitted, envp);
	}
	free(cmd_tot);
}

char	*check_cmd(t_vars *vars, char **splitted, char **envp)
{
	int		i;

	i = 0;
	if (splitted[0][0] == '/' || splitted[0][0] == '.')
		execve(splitted[0], splitted, envp);
	while (vars->paths[i])
	{
		find_path(vars, splitted, envp, i);
		i++;
	}
	write(2, "Command not found\n", 18);
	exit (127);
}

void	dup_in_out(int make_in, int make_out)
{
	if (dup2(make_in, 0) < 0)
	{
		perror("Duplication failed\n");
		exit(1);
	}
	if (dup2(make_out, 1) < 0)
	{
		perror("Duplication failed\n");
		exit(1);
	}
}
