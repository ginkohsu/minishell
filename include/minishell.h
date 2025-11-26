/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:55:04 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/19 20:30:52 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include "ast.h"
# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

# define MAX_TOKENS 1000

extern volatile sig_atomic_t	g_signal;

// tokenizing
void							skip_whitespace(char **input);
int								ft_isspace(char c);
int								is_only_whitespace(char *str);
int								is_special_char(char c);
int								check_unclosed_quote(char *input);
char							*extract_word(char **input);
void							handle_quote_char(char **input,
									t_token *collected_tokens, int *count);
void							handle_redirect_char(char **input,
									t_token *collected_tokens, int *count);
void							handle_single_special_char(char **input,
									t_token *collected_tokens, int *count);
void							handle_env_var_char(char **input,
									t_token *collected_tokens, int *count);
char							*handle_env_var(char **input);

t_token							*tokenize(char *input, int *token_count);

void							free_tokens(t_token *tokens, int count);
void							cleanup_stack_tokens(t_token *tokens,
									int count);

// parsing
t_parser						parser_init(t_token *tokens, int count);
t_token							*parser_peek(t_parser *parser, int offset);
t_token							*parser_consume(t_parser *parser);
int								parser_check(t_parser *parser,
									t_token_type type);
int								is_redirection_token(t_token *token);
int								is_terminating_token(t_token *token);
int								is_string_token(t_token *token);
t_ast							*create_command_node(void);
t_ast							*create_pipe_node(t_ast *left, t_ast *right);
char							*expand_token_value_basic(t_token *token);
char							*expand_vars_dquote(char *src);
char							*getenvstr(char *var);
void							check_heredoc_quotes(t_parser *parser,
									t_token *token, int *quoted);
char							*handle_heredoc_filename(t_token *filename,
									int *quoted);
t_ast							*parse_pipeline(t_parser *parser);
t_ast							*parse_command(t_parser *parser);
int								add_argument_to_cmd(t_command *cmd, char *arg);
int								parse_redirection(t_parser *parser,
									t_command *cmd);
t_ast							*parse(char *input);
void							free_ast(t_ast *ast);
t_token							*copy_to_heap(t_token *collected, int count,
									int *token_count);
char							*merge_adjacent_tokens(t_parser *parser,
									char *current_arg, t_token *current_token);

// execution entry
void							execute_ast(t_ast *ast);
void							ast_root(t_ast *ast);

// child process type splitting
void							only_child(t_command *cmd, int fd[3][2]);
void							first_child(t_command *cmd, int fd[3][2]);
void							last_child(t_command *cmd, int fd[3][2]);
void							middle_child(t_command *cmd, int fd[3][2]);

// non-builtin && builtin cmd execution
int								is_builtin(char *name);
int								parent_builtin(t_command *cmd);
void							execute_command(t_command *cmd);

// builtin functions
int								ft_cd(char **av, int f);
int								ft_exit(char **av, int f);
int								ft_echo(char **av, int f);
int								ft_export(char **av, int f);
int								ft_unset(char **av, int f);
int								ft_env(char **av, int f);
int								ft_pwd(char **av, int f);

// redirs
void							setup_redirections(t_redir *redirs);
void							heredoc(t_redir *redirs);
char							*make_tmpfile(void);
bool							cleanup_heredocs(t_redir *start, t_redir *end);
void							heredoc_sighandler(int sig);
int								check_signal(void);
void							in_session(bool active,
									struct sigaction *old_sa);

// env table management
int								initenv(char **src_env);
char							**fetchenv(char *key);
int								addenv(char *entry);
int								rmenv(char *key);

// utils
int								preprocess(t_ast *ast);
int								exittool(char *msg, void *obj, int action,
									unsigned char code);
void							safe_close(int *fd);
void							safe_free(void **ptr);
bool							set_exit(int code);
void							wait_for_children(int *pid, int total);
bool							is_path(char *prog);

// signal
void							setup_signal_handlers(void);
void							sig_handler(int signum);

// shell runtime
bool							init_shell(char **env);
void							process_line(char *line, bool interactive);
bool							interactive_mode(bool tty);

#endif
