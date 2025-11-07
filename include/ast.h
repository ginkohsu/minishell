/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:15:02 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/05 00:35:17 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../libft/include/libft.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SQUOTE,
	TOKEN_DQUOTE,
	TOKEN_ENV_VAR,
	TOKEN_EXIT_STATUS,
	TOKEN_EOF
}							t_token_type;

typedef struct s_token
{
	t_token_type			type;
	char					*value;
	int						no_space_after;
}							t_token;

typedef struct s_parser
{
	t_token					*tokens;
	int						token_count;
	int						current_pos;
}							t_parser;

typedef enum e_parse_status
{
	PARSE_SUCCESS,
	PARSE_SYNTAX_ERROR,
	PARSE_MALLOC_ERROR
}							t_parse_status;

typedef struct s_redir
{
	t_token_type			type;
	char					*filename;
	int						quoted;
	struct s_redir			*next;
}							t_redir;

typedef struct s_command
{
	char					**argv;
	t_redir					*redirs;
}							t_command;

typedef enum e_node_type
{
	CMD,
	PIPE
}							t_node_type;

typedef struct s_ast
{
	t_node_type				type;
	union
	{
		t_command			cmd;
		struct
		{
			struct s_ast	*left;
			struct s_ast	*right;
		} s_pipe;
	};
}							t_ast;

// pipex_bonus style multi-process file descriptor handling
typedef struct s_pipe_ctx
{
	int		*pid;
	int		fd[3][2];
	int		index;
	int		total;
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
	F_ARR = 1 << 4,
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
# define ERR_PERM_DENIED "%s: Permission denied\n"
# define ERR_CMD_NOT_FOUND "%s: command not found\n"
# define ERR_NO_SUCH_FILE "%s: No such file or directory\n"
# define ERR_NOT_EXECUTABLE "%s: not executable\n"
# define ERR_IS_DIR "%s: Is a directory\n"
# define ERR_CD_MANY_ARGS "minishell: cd: too many arguments\n"
# define ERR_CD_HOME_UNSET "minishell: cd: HOME not set\n"
# define ERR_CD_OLDPWD_UNSET "minishell: cd: OLDPWD not set\n"
# define ERR_CD_PATH "minishell: cd: %s: %s\n"
# define ERR_CD_CWD "minishell: cd: cwd: %s\n"
# define ERR_EXIT_MANY_ARGS "minishell: exit: too many arguments\n"
# define ERR_EXIT_NUMERIC "minishell: exit: %s: numeric argument required\n"
# define ERR_EXPORT_INVALID "minishell: export: `%s': not a valid identifier\n"
# define ERR_NO_SPACE "%s: no space left on device\n"
# define ERR_NO_FILE "%s: No such file or directory\n"
# define ERR_OPEN_UNDEF "%s: undefined error opening file\n"
# define ERR_SYNTAX "syntax error near unexpected token '%s'\n"
# define ERR_SYNTAX_NEAR "syntax error near unexpected token 'newline'\n"

#endif
