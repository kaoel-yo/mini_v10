#include "minishell.h"

char 	*ft_addchar(char * str, char c)
{
	char *r_str;
	int i = 0;

	if (!str)
	{
		r_str = malloc(2);
		r_str[0] = c;
		r_str[1] = '\0';
		return r_str;
	}
	r_str = malloc (ft_strlen(str) + 2);
	while (str[i])
	{
		r_str[i] = str[i];
		i++;
	}
	if(c == ';')
		r_str[i] = '\0';
	else
	{
		r_str[i++] = c;
		r_str[i] = '\0';
	}
	return (r_str);
}

char *	ft_getenv(char *var, char **env)
{
	char *value;
	char *key;
	int j = 0;
	int i = 0;

	if (!var)
		return (NULL);
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		key = ft_substr(env[i], 0, j);
		if (ft_strlen(var) == j && !ft_strncmp(key, var, j))
			return ft_substr(env[i], j + 1, ft_strlen(env[i]));
		i++;
	}
	return (NULL);
}

char *skip_quote(char *line,char **env)
{
	int i = 0;
	int len;
	int j = 0;
	int flag = 0;
	char *str = NULL;
	char *s;

	while(line[i])
	{
		len = 0;
		flag = i;
		if(line[i] == '\'')
		{
			len = 1;
			flag = i + 1;
			j = flag;
			while(line[j] && line[j] != 39)
				j++;
			i = j + 1;
			j = j - 1;
		}
		else if(line[i] == '"')
		{
			len = 2;
			flag = i + 1;
			j = flag;
			while(line[j] && line[j] != '"')
				j++;
			i = j + 1;
			j = j - 1;
		}
		else
		{
			while(line[i] && (line[i] != '"' && line[i] != '\''))
			{
				j++;
				i++;
			}
		}
		s = ft_substr(line,flag,j - flag + 1);
		if (len != 0)
			j++;
		str = ft_strjoin1(str,update_cmd_line(s,env,len));
		free(s);
	}
	return(str);
}

char	*update_cmd_line(char *line , char **en, int l)
{
	char  *update_line = NULL;
	char  *var = NULL;
	char *ret;
	char *tmp;
	char *tmp1;
	char *tmp2;
	int j = 0;
	int i = 0;

	if(l == 1)
		return(line);
	while (line[i] != '\0')
	{
		if (line[i + 1] && line[i] == '$' && (ft_isalpha(line[i + 1]) || line[i + 1] == '_'))
		{
			i++;
			int end = 0;
			j = i;
			while (ft_isalnum(line[i]) || line[i] == '_')
			{
				i++;
				end++;
			}
			if(line[i] && line[i] == '_')
			{
				var = ft_substr(line,j,end);
				i++;
			}
			else
				var = ft_substr(line, j, end);
			printf(" var == %s\n", var);
			tmp1 = ft_getenv(var, en);
			if (var)
			{
				tmp2 = ft_strjoin1(update_line, tmp1);
				if (update_line)
					free (update_line);
				update_line = tmp2;
			}
			if (tmp1)
				free (tmp1);
			if (var)
				free (var);
		}
		else
		{
			tmp = ft_addchar(update_line, line[i]);
			if (update_line)
				free(update_line);
			update_line = tmp;
			i++;
		}
	}
	return(update_line);
}


// t_env	*ft_lstnew11(int content, char *ke, char *val)
// {
// 	t_env	*node;

// 	node = (t_env *)malloc(sizeof(*node));
// 	if (!(node))
// 		return (NULL);
// 	node->index = content;
// 	node->env = ke;
// 	node->next = NULL;
// 	node->valu = val;
// 	return (node);
// }
// t_env	*ft_lstlast11(t_env *lst)
// {
// 	while (lst)
// 	{
// 		if (!lst->next)
// 			return (lst);
// 		lst = lst->next;
// 	}
// 	return (lst);
// }

// void	ft_lstadd_back11(t_env **alst, t_env *new)
// {
// 	t_env	*last;

// 	if (alst)
// 	{
// 		if (*alst)
// 		{
// 			last = ft_lstlast11(*alst);
// 			last->next = new;
// 		}
// 		else
// 			*alst = new;
// 	}
// }

// int	cherch_equal(char *env)
// {
// 	int i;

// 	i = 0;
// 	while (env[i] != '\0')
// 	{
// 		if (env[i] == '=')
// 		{
// 			return (i);
// 		}
// 		i++;
// 	}
// 	return (-1);
// }

// t_env *user_expand(char **env)
// {
// 	char *ret;
// 	t_env *en = NULL;
// 	int i;
// 	int j;
// 	int m;

// 	i = 0;

// 	while (env[i] != '\0')
// 	{
// 		j = cherch_equal(env[i]);
// 		if (j != -1)
// 		{
// 			ret = malloc(sizeof(char) * (j + 1));
// 			m = 0;
// 			while (m < j)
// 			{
// 				ret[m] = env[i][m];
// 				m++;
// 			}
// 			ret[m] = '\0';
// 		}
// 		ft_lstadd_back11(&en, ft_lstnew11(i, ret, ft_strdup(env[i] + j + 1)));
// 		i++;
// 	}
// 	return (en);
// }
