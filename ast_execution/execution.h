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
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/types.h>

/* Pipe context for multi-command execution */
typedef struct s_pipe_ctx
{
	int	*pid;
	int	fd[3][2];
	int	index;
}		t_pipe_ctx;

/* Pipe/FD index defines */
# define NEXT 0
# define LAST 1
# define IOFD 2
# define READ 0
# define WRITE 1
# define INFILE 0
# define OUTFILE 1

/* ft_error action flags (can be combined with |) */
# define STAY     (1 << 0)  /* Don't exit, just return */
# define P_OBJ    (1 << 1)  /* Print obj in message */
# define F_OBJ    (1 << 2)  /* Free obj */
# define F_MSG    (1 << 3)  /* Free msg string */
# define P_ARRAY  (1 << 4)  /* Print array (unused) */
# define F_ARRAY  (1 << 5)  /* Free string array */
# define F_ARENA  (1 << 6)  /* Free arena allocator */
# define STRERROR (1 << 7)  /* Print errno string */
# define V_OBJ    (1 << 8)  /* Verbose obj (unused) */
# define F_AST    (1 << 9)  /* Free AST tree */
# define OPEN_FAIL    (1 << 10)  /* Free AST tree */

/* Main execution entry point */
void	execute_ast(t_ast *ast);
void	free_ast_root(void);

/* Child process handlers */
void	only_child(t_command *cmd, int fd[3][2]);
void	first_child(t_command *cmd, int fd[3][2]);
void	last_child(t_command *cmd, int fd[3][2]);
void	middle_child(t_command *cmd, int fd[3][2]);

/* Builtin detection and execution */
int		is_builtin(char *name);
void	execute_parent_builtin(t_command *cmd);
void	execute_command(t_command *cmd);
char	*get_path(char **prog);

/* Individual builtin implementations */
int		ft_cd(char **av);
int		ft_exit(char **av);
int		ft_echo(char **av);
int		ft_export(char **av);
int		ft_unset(char **av);
int		ft_env(char **av);
int		ft_pwd(char **av);

/* Redirection handling */
void	setup_redirections(t_redir *redirs);

/* Environment management */
void	initenv(char **src_env);
char	**fetchenv(char *str);
void	addenv(char *entry);
void	rmenv(char *key);
char	**get_sorted_env(void);

/* Utility functions */
void	free_array(char **array);
int		count_array(char **array);
void	ft_error(char *msg, void *obj, int action, unsigned char code);

/* FD debugging macro - shows all open FDs */
#define DEBUG_FDS() do { \
	int _fd; \
	for(_fd=0; _fd<1024; _fd++) { \
		if(fcntl(_fd, F_GETFD) != -1) \
			ft_fprintf(2, "==%-5d== FD %d is open\n", getpid(), _fd); \
	} \
} while(0)

/* Debug functions (prefix dbg_ for easy cleanup) */
void	dbg_print(char *msg);
void	dbg_print_ast(t_ast *ast, int depth);
void	dbg_trace_cmd(char *location, char *cmd_name);
void	dbg_trace_pipe(char *location, int index, int total);
void	dbg_trace_fds(char *location, int fd[3][2]);
void	dbg_trace_child(char *role, char *cmd_name);
void	dbg_trace_path(char *prog, char *path);
void	dbg_trace_env(char *operation, char *key);
void	dbg_toggle(void);
void	dbg_enable(void);
void	dbg_disable(void);

#endif
