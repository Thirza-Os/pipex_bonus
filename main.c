/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 14:00:07 by tosinga       #+#    #+#                 */
/*   Updated: 2022/04/05 19:06:59 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exit_strategy(int counter, t_vars *vars)
{
	int	status;
	int	exit_code;

	exit_code = 1;
	while (counter < vars->child_count)
	{
		if (wait(&status) == vars->child)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
		}
		counter++;
	}
	exit(exit_code);
}

static int	pipex(t_vars *vars, char **envp, int cmd_count)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	vars->child_count = 0;
	while (vars->child_count < cmd_count)
	{
		child_process(vars, envp, cmd_count);
		vars->child_count++;
	}
	close(vars->fd[FILE_IN]);
	close(vars->fd[FILE_OUT]);
	exit_strategy(counter, vars);
	return (0);
}

static int	get_cmd(t_vars *vars, char **argv, int argc)
{
	int		cmd_count;
	int		i;

	vars->cmd = ft_malloc_check((char **)malloc((argc - 2) * sizeof(char *)));
	cmd_count = 0;
	while (cmd_count < argc - 3)
	{
		vars->cmd[cmd_count] = argv[cmd_count + 2];
		cmd_count++;
	}
	vars->cmd[cmd_count] = NULL;
	vars->split_cmd = ft_malloc_check((char ***)malloc((cmd_count + 1) \
					* sizeof(char **)));
	vars->split_cmd[cmd_count] = NULL;
	i = 0;
	while (i < cmd_count)
	{
		vars->split_cmd[i] = ft_malloc_check(ft_split(vars->cmd[i], ' '));
		i++;
	}
	return (cmd_count);
}

static void	open_files(t_vars *vars, char **argv, int argc)
{
	vars->fd[FILE_IN] = open(argv[1], O_RDONLY);
	vars->fd[FILE_OUT] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (vars->fd[1] < 0)
	{
		perror("Failed to open file\n");
		exit(1);
	}
	if (vars->fd[0] < 0)
	{
		perror("Failed to open file\n");
		exit(1);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;
	int		cmd_count;

	if (argc < 5)
	{
		write(2, "Not enough arguments\n", 21);
		exit(1);
	}
	cmd_count = get_cmd(&vars, argv, argc);
	open_files(&vars, argv, argc);
	envp_paths(&vars, envp);
	pipex(&vars, envp, cmd_count);
	ft_free(vars.paths);
	ft_free(vars.cmd);
	while (cmd_count > 0)
	{
		ft_free(vars.split_cmd[cmd_count]);
		cmd_count--;
	}
	return (0);
}
