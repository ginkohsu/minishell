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
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// execution entry
void	execute_ast(t_ast *ast);
void	ast_root(t_ast *ast);

// child process type splitting
void	only_child(t_command *cmd, int fd[3][2]);
void	first_child(t_command *cmd, int fd[3][2]);
void	last_child(t_command *cmd, int fd[3][2]);
void	middle_child(t_command *cmd, int fd[3][2]);

// non-builtin && builtin cmd execution
int		is_builtin(char *name);
int		parent_builtin(t_command *cmd);
void	execute_command(t_command *cmd);

// builtin functions
int		ft_cd(char **av, int f);
int		ft_exit(char **av, int f);
int		ft_echo(char **av, int f);
int		ft_export(char **av, int f);
int		ft_unset(char **av, int f);
int		ft_env(char **av, int f);
int		ft_pwd(char **av, int f);

// redirs
void	setup_redirections(t_redir *redirs);
void	heredoc(t_redir *redirs);
char	*make_tmpfile(void);

// env table management
int		initenv(char **src_env);
char	**fetchenv(char *key);
int		addenv(char *entry);
int		rmenv(char *key);

// utils
void	free_array(char **array);
int		preprocess(t_ast *ast);
int		exittool(char *msg, void *obj, int action, unsigned char code);
void	safe_close(int *fd);
void	safe_free(void **ptr);
bool	set_exit(int code);
void	wait_for_children(int *pid, int total);
bool	is_path(char *prog);

// array utils
int		arrlen(char **arr);
int		arrlcpy(char **dst, char **src, int dstsize);
char	**arrdup(char **src);
char	**arrndup(char **src, int n);
int		arrstr(char **arr, char *str);
int		arrstrn(char **arr, char *str, int n);
void	arrsort(char **arr);

#endif
