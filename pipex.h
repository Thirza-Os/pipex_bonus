/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 14:00:18 by tosinga       #+#    #+#                 */
/*   Updated: 2022/04/05 18:04:25 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>

# define PIPE_OUT_WRITE 1
# define PIPE_IN_READ 0

# define FILE_OUT 1
# define FILE_IN 0

typedef struct s_vars
{
	int		fd[2];
	pid_t	child;
	int		pipe_end[2][2];
	char	**cmd;
	char	***split_cmd;
	char	**paths;
	int		child_count;
}	t_vars;

char			**ft_split_add_slash(char const *s, char c);
void			envp_paths(t_vars *vars, char **envp);
void			*ft_malloc_check(void *s);
void			fork_error(void);
char			*check_cmd(t_vars *vars, char **test, char **envp);
void			dup_in_out(int make_in, int make_out);
void			child_process(t_vars *vars, char **envp, int cmd_count);

#endif