/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:55:04 by jinxu             #+#    #+#             */
/*   Updated: 2025/11/04 19:29:40 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include "execution.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>

# define MAX_TOKENS 1000

// tokenizing
void		skip_whitespace(char **input);
int			ft_isspace(char c);
int			is_only_whitespace(char *str);
int			is_special_char(char c);
int			check_unclosed_quote(char *input);
char		*extract_word(char **input);
void		handle_quote_char(char **input, t_token *collected_tokens,
				int *count);
void		handle_redirect_char(char **input, t_token *collected_tokens,
				int *count);
void		handle_single_special_char(char **input, t_token *collected_tokens,
				int *count);
void		handle_env_var_char(char **input, t_token *collected_tokens,
				int *count);
char		*handle_env_var(char **input);

t_token		*tokenize(char *input, int *token_count);

void		free_tokens(t_token *tokens, int count);
void		cleanup_stack_tokens(t_token *tokens, int count);

// parsing
t_parser	parser_init(t_token *tokens, int count);
t_token		*parser_peek(t_parser *parser, int offset);
t_token		*parser_consume(t_parser *parser);
int			parser_check(t_parser *parser, t_token_type type);
int			is_redirection_token(t_token *token);
int			is_terminating_token(t_token *token);
int			is_string_token(t_token *token);
t_ast		*create_command_node(void);
t_ast		*create_pipe_node(t_ast *left, t_ast *right);
char		*expand_simple_env_var(char *var_name);
char		*expand_token_value_basic(t_token *token);
char		*expand_vars_dquote(char *src);
char		*getexitstr(void);

t_ast		*parse_pipeline(t_parser *parser);
t_ast		*parse_command(t_parser *parser);
int			add_argument_to_cmd(t_command *cmd, char *arg);
int			parse_redirection(t_parser *parser, t_command *cmd);
t_ast		*parse(char *input);
void		free_ast(t_ast *ast);

t_token		*copy_to_heap(t_token *collected, int count, int *token_count);
char		*merge_adjacent_tokens(t_parser *parser, char *current_arg,
				t_token *current_token);

// for testing:
void		print_ast(t_ast *ast, int depth);
void		print_tokens_debug(t_token *tokens, int count);
const char	*get_token_type_name(t_token_type type);
const char	*get_node_type_name(t_node_type type);
#endif
