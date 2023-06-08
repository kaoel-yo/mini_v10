#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_glob {
	int ex_status;
}				t_g;

typedef struct s_add
{
	int type;
	char *file;
	char *limit;
	char *sep;
	char *str;
	struct s_add *next;
	struct s_add *pre;

}				t_add;

typedef struct s_help
{
	int		index;
	char	**cmd;
	char	*fullpath;
	char	**paths;
	char	*cmd_path;
	char	*herdoc;
	int		fd_in;
	int		fd_out;
	t_add 	*m;
	int 	exit;
	struct s_help *next;
	struct s_help *pre;
	int k;
	int g;

}				t_help;

typedef struct  s_env
{
	char *env;
	char *valu;
	int index;
	struct s_env *next;

} 				t_env;


int ft_check_error1(char *str);
int	ft_checkpoint(char *str);
char	*update_cmd_line(char *line , char **en, int l);
char *skip_quote(char *line,char **env);
char *	ft_getenv(char *var, char **env);
char 	* ft_addchar(char * str, char c);
void	execution(t_help **help, t_env *env, char **envp);
t_help	*ft_lstnew(int content);
t_add	*ft_lstnew1(int content);
void	ft_lstadd_back(t_help **alst, t_help *new);
int		ft_lstsize(t_help *lst);
t_help	*ft_lstlast(t_help *lst);
void	ft_lstadd_back1(t_add **alst, t_add *new);
t_add	*ft_lstlast1(t_add *lst);
t_env *user_expand(char **env);
t_env	*ft_lstnew11(int content, char *ke, char *val);
void	ft_lstadd_back11(t_env **alst, t_env *new);
t_env	*ft_lstlast11(t_env *lst);
void 	delete_node(t_env **env, char* key);
void	exec_echo(char **str);
int		exec_cd(t_env *env, t_help *help);
char 	*ft_env_value(t_env *en, char **cmd);
t_env 	*remp (char **envp);
int		exec_pwd();
void	exec_export(t_env *env ,char **str);
t_env 	*lstnew_env(char *key, char *value);
void	lstadd_back_env(t_env **env, t_env *new);
void 	Sort_env(t_env *env);
int 	find_equal(char *str);
int		ft_lstsize_env(t_env *lst);
void   print_env(t_env *env, char **envp);
void 	exec_unset(t_env * env, char **str);
void	ft_exit(t_help *help);
int		builtins(t_env *env, t_help *help, char **envp);
char	*ft_strjoin2(char *s1, char *s2);
char	*update_cmd_line(char *line , char **en, int l);
char	**ft_split2(char const *s, char c);
char	*get_full_path(t_env *env);
t_g		*g_gl;

#endif
