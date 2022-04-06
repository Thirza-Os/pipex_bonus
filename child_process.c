/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_process.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 13:59:52 by tosinga       #+#    #+#                 */
/*   Updated: 2022/04/06 10:49:35 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_child(t_vars *vars, int pipe_count)
{
	close(vars->fd[FILE_OUT]);
	close(vars->pipe_end[pipe_count][PIPE_IN_READ]);
	dup_in_out(vars->fd[FILE_IN], \
	vars->pipe_end[pipe_count][PIPE_OUT_WRITE]);
	close(vars->pipe_end[pipe_count][PIPE_OUT_WRITE]);
	close(vars->fd[FILE_IN]);
}

static void	last_child(t_vars *vars, int pipe_count)
{
	close(vars->fd[FILE_IN]);
	dup_in_out(vars->pipe_end[!pipe_count][PIPE_IN_READ], \
	vars->fd[FILE_OUT]);
	close(vars->pipe_end[!pipe_count][PIPE_IN_READ]);
	close(vars->fd[FILE_OUT]);
}

static void	mid_child(t_vars *vars, int pipe_count)
{
	close(vars->fd[FILE_OUT]);
	close(vars->fd[FILE_IN]);
	close(vars->pipe_end[pipe_count][PIPE_IN_READ]);
	dup_in_out(vars->pipe_end[!pipe_count][PIPE_IN_READ], \
	vars->pipe_end[pipe_count][PIPE_OUT_WRITE]);
	close(vars->pipe_end[!pipe_count][PIPE_IN_READ]);
	close(vars->pipe_end[pipe_count][PIPE_OUT_WRITE]);
}

static void	call_childs(t_vars *vars, int pipe_count, \
			int cmd_count, char **envp)
{
	if (vars->child_count == 0)
		first_child(vars, pipe_count);
	else if (vars->child_count == cmd_count - 1)
		last_child(vars, pipe_count);
	else
		mid_child(vars, pipe_count);
	check_cmd(vars, vars->split_cmd[vars->child_count], envp);
}

void	child_process(t_vars *vars, char **envp, int cmd_count)
{
	static int	pipe_count = 1;

	pipe_count = !pipe_count;
	if (vars->child_count < cmd_count - 1)
	{
		if (pipe(vars->pipe_end[pipe_count]) < 0)
		{
			perror("Pipe did not succeed\n");
			exit(1);
		}
	}
	vars->child = fork();
	if (vars->child < 0)
		fork_error();
	if (vars->child == 0)
		call_childs(vars, pipe_count, cmd_count, envp);
	if (vars->child_count < cmd_count - 1)
		close(vars->pipe_end[pipe_count][PIPE_OUT_WRITE]);
	if (vars->child_count != 0)
		close(vars->pipe_end[!pipe_count][PIPE_IN_READ]);
}
