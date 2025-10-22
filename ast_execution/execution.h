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
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <dirent.h>
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
	int		size;
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

// exittool action flags (bitwise flags for exittool)
enum		e_error_action
{
	STAY = 1 << 0,
	P_OBJ = 1 << 1,
	F_OBJ = 1 << 2,
	F_MSG = 1 << 3,
	F_ARRAY = 1 << 4,
	F_ARENA = 1 << 5,
	F_AST = 1 << 6,
	STRERR = 1 << 7,
	OPEN_FAIL = 1 << 8,
	F_ENV = 1 << 9,
	PPROC = 1 << 10,
	TRUE_EXIT = 1 << 11,
	EXEC_FAIL = 1 << 12
};

// error message macros
# define ERR_ENV_CORRUPT "minishell: environment table corrupted\n"
# define ERR_DUP2 "dup2 failed"
# define ERR_MALLOC "malloc failed"
# define ERR_PIPE "pipe failed"
# define ERR_FORK "fork failed"
# define ERR_EXECVE "execve failed"
# define ERR_OPEN "open: %s"
# define ERR_PERM_DENIED "%s: permission denied\n"
# define ERR_CMD_NOT_FOUND "%s: command not found\n"
# define ERR_NO_SUCH_FILE "%s: no such file or directory\n"
# define ERR_NOT_EXECUTABLE "%s: not executable\n"
# define ERR_IS_DIR "%s: is a directory\n"
# define ERR_CD_MANY_ARGS "minishell: cd: too many arguments\n"
# define ERR_CD_HOME_UNSET "minishell: cd: HOME not set\n"
# define ERR_CD_OLDPWD_UNSET "minishell: cd: OLDPWD not set\n"
# define ERR_CD_PATH "minishell: cd: %s: %s\n"
# define ERR_CD_CWD "minishell: cd: cwd: %s\n"
# define ERR_EXIT_MANY_ARGS "minishell: exit: too many arguments\n"
# define ERR_EXIT_NUMERIC "minishell: exit: %s: numeric argument required\n"
# define ERR_EXIT_OVERFLOW "minishell: exit: %s: overflow\n"
# define ERR_NO_SPACE "%s: no space left on device\n"
# define ERR_NO_FILE "%s: no such file\n"
# define ERR_OPEN_UNDEF "%s: undefined error opening file\n"

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
int			parent_builtin(t_command *cmd);
void		execute_command(t_command *cmd);

// builtin functions
int			ft_cd(char **av, int f);
int			ft_exit(char **av, int f);
int			ft_echo(char **av, int f);
int			ft_export(char **av, int f);
int			ft_unset(char **av, int f);
int			ft_env(char **av, int f);
int			ft_pwd(char **av, int f);

// redirs
void		setup_redirections(t_redir *redirs);

// env table management
int			initenv(char **src_env);
char		**fetchenv(char *key);
int			addenv(char *entry);
int			rmenv(char *key);

// utils
void		free_array(char **array);
int			count_ast_commands(t_ast *ast);
int			exittool(char *msg, void *obj, int action, unsigned char code);
void		safe_close(int *fd);
void		wait_for_children(int *pid, int total);

// array utils
int			arrlen(char **arr);
int			arrlcpy(char **dst, char **src, int dstsize);
char		**arrdup(char **src);
char		**arrndup(char **src, int n);
int			arrstr(char **arr, char *str);
int			arrstrn(char **arr, char *str, int n);
void		arrsort(char **arr);

#endif
