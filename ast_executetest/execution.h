/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:40:28 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/09 13:40:28 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "ast.h"
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// pipex_bonus style multi-process file descriptor handling
typedef struct s_pipe_ctx
{
	int		*pid;
	int		fd[3][2];
	int		index;
}			t_pipe_ctx;

// env table
typedef struct s_table
{
	size_t	count;
	char	**env;
}			t_table;

// pipe_ctx fd[][] defines
# define NEXT 0
# define LAST 1
# define IOFD 2
# define READ 0
# define WRITE 1
# define INFILE 0
# define OUTFILE 1

// ft_error action flags (bitwise flags for ft_error)
enum	e_error_action
{
	STAY = 1 << 0,
	P_OBJ = 1 << 1,
	F_OBJ = 1 << 2,
	F_MSG = 1 << 3,
	F_ARRAY = 1 << 4,
	F_ARENA = 1 << 5,
	F_AST = 1 << 6,
	STRERROR = 1 << 7,
	OPEN_FAIL = 1 << 9
};

// execution entry
void		execute_ast(t_ast *ast);
void		free_ast_root(void);

// child process type splitting
void		only_child(t_command *cmd, int fd[3][2]);
void		first_child(t_command *cmd, int fd[3][2]);
void		last_child(t_command *cmd, int fd[3][2]);
void		middle_child(t_command *cmd, int fd[3][2]);

// non-builtin && builtin cmd execution
int			is_builtin(char *name);
int			execute_parent_builtin(t_command *cmd);
void		execute_command(t_command *cmd);

// builtin functions
int			ft_cd(char **av);
int			ft_exit(char **av);
int			ft_echo(char **av);
int			ft_export(char **av);
int			ft_unset(char **av);
int			ft_env(char **av);
int			ft_pwd(char **av);

// redirs
void		setup_redirections(t_redir *redirs);

// env table management
void		initenv(char **src_env);
char		**fetchenv(char *key);
void		addenv(char *entry);
void		rmenv(char *key);
char		**get_sorted_env(void);

// utils
void		free_array(char **array);
int			count_array(char **array);
int			count_ast_commands(t_ast *ast);
void		ft_error(char *msg, void *obj, int action, unsigned char code);

#endif
