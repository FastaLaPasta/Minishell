/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:01:20 by sboulogn          #+#    #+#             */
/*   Updated: 2023/06/22 16:08:11 by jgiampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <termios.h>
# include "Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_command
{
	char				*name;
	char				**value;
	char				*limiter;
	int					input_file;
	int					output_file;
	int					*quotes;
	struct s_command	*next;
}				t_command;

typedef struct s_minishell
{
	char		**cpip;
	char		**path;
	char		*input;
	char		**env;
	int			nbr_cmd;
	int			**fd;
	int			etat;
	pid_t		*child;
	t_command	*cmd;
}				t_minishell;

int			ft_exit(t_minishell *arg, t_command *cmd);
int			ft_pwd(void);
int			ft_cd(char *path, t_minishell *arg);
int			ft_echo(t_command *cmd);
int			ft_unset(char *av, char **envp);
int			ft_env(char **envp);
int			ft_export(char **value, char **env, t_minishell	*arg);

int			handle_quotes(int *i, char *str);
int			*fill_quotes(char *value);
int			nbr_cmd(t_minishell *a);
int			accesserr(t_command	*cmd);
int			statuscode(int etat);
int			fill_struct(t_minishell *minishell, char **env);
int			exec_built_in(t_minishell *arg, t_command *cmd);
int			ft_analize(char	*cmd, t_command *chaine);
int			verif_syntax(char *str);
int			ft_strlenfw1(char *str);
int			exec(t_minishell *arg, t_command *cmd, int i);
int			access_path(t_minishell *arg, t_command	*cmd);
int			strlen_mallocsize(char *str);
int			exec_bash(t_minishell *arg, t_command *cmd);
int			ft_skip(char c);
int			ft_opensimple(char *file, int how_many_chvr);
int			ft_strncmpmaj(const char *s1, const char *s2, size_t n);
int			choise(t_minishell *arg, t_command *cmd);
int			interogation_after_dollar(char *str, char **file, int *d, int *i);
int			dollaroutquote(char *file, char *str, int *d, int q);
int			dollarinquote(char *file, char *str, int *d, int q);
int			ft_increase_i(char *str, int i);
int			ft_experr0(char **splt, char **value, t_minishell *arg, int j);
int			exp_exec(int *i, char **splt, char **env);
int			exp_only(char **env);
char		*ft_clearchevron(char *org);
char		*ft_first_word(char *str);
char		*true_dollars(char	*str);
char		**free_tab(char **tab);
char		**ft_split_for_quotes(char const *s, char c);
char		*true_file(char *str, int q);
void		the_while(char const **s, int i[2], char *ptr);
void		init_struct(t_minishell *minishell);
void		fill_path(t_minishell	*all, char **env);
void		write_errn(char *s, char *t);
void		ft_lstadd_back(t_command **lst, t_command *new);
void		ft_here_doc(t_minishell *arg, t_command *all);
void		close_everything(t_minishell *arg, int i);
void		ft_structfree2(t_minishell *arg);
void		ft_mallocpip(t_minishell *all);
void		ft_structfree(t_minishell *arg);
void		sort_environment(char **env);
void		print_environment(char **env);
void		ft_getenv(char *tmp, int	*len);
void		ft_i_file(char *str, int q, char *file);
void		can_we_exec(t_minishell *arg, t_command *cmd);
void		ft_movein_dollar(char *dollar, char *file, int *d);
void		ft_wrernoexp(char *value);
t_command	*ft_lstnew(char	*content);
t_command	*ft_lstlast(t_command *lst);
char		*ft_free2_join(char *s1, char *s2);
char		*dollarintmp(t_command *start, t_minishell *minishell,
				int i, int j);
void		ft_fake_heredoc(t_command *all);
int			ft_replacedollar(t_command *start, t_minishell *minishell);
char		*ft_replacedollar_heredoc(char *tmp, t_minishell *minishell);
char		*dollarinhdoc(char *start, t_minishell *minishell, int j);
char		*true_file_heredoc(char *str, int q);
char		*len_dollar(int	*len, char *str, int q);
char		*len_dollar2(int	*len, char *str, int q);
char		*return_char(char *str, char *tmp);
int			nbr_slash(char *str);
int			error_bck_slash(char *str);
void		handle_signal3(int signal);
void		ft_signal(void);

#endif