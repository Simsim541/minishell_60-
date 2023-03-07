/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:39:35 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/07 15:40:55 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdio.h"
# include "stdlib.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "libft/libft.h"
# include "unistd.h"
# include "fcntl.h"

typedef enum e_redirection_type
{
	RED_OUT,
	RED_DOUBLE_OUT,
	RED_INP,
	RED_DOUBLE_INP,
}t_redirection_type;

typedef struct s_redirection
{
	t_redirection_type		type;
	int						index;
	char					*file_name;
	struct s_redirection	*next;
}t_redirection;

typedef struct s_cmd
{
	char			*cmd;
	char			*option;
	char			**argument;
	t_redirection	*redirect;
	struct s_cmd	*next;
}t_cmd;

int				there_is_a_redirection(char *str);
t_redirection	*init_redirecttion(void);
t_cmd			*init_cmd(void);
void			fill_redirection(t_cmd *cmd, char *line, int *i);
int				is_option(char *line);
void			normal_parsing(t_cmd *cmd, char *line);
void			parsing_with_redirection(t_cmd *cmd, char *line);
t_cmd			*init_command(char **args);
int				check_redirect(char *line);
int				print_error(char *str);
int				check_append_in_out(char *str);
int				check_quotes(char *str);
char			*expand_env(char *str, char **env);
int				double_quotes(char *str, int i, int *db, int single);
int				check_in_out(char *str);
void			nbr_of_char(char *str, int *d, int *s, int i);
int				check_dollar(char *str, int *i, int status, char *cmd);
int				get_var_env(char *str, char **env, int *j, char *cmdline);
int				check_d(char *str, char *cmdline, int *i, int status);
void			fillcmd_and_incj(char *cmdline, int *j, int *l, int *i);
int				check_digit(char *str, char *cmdline);
void			init_var(int *var1, int *var2, int *var3, int *var4);
int				is_white_space(char c);
int				check_pipes(char *line);
int				number_of_pipes(char *line);
int				check_syntax_init(char *line);

#endif
