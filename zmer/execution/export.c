/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 22:46:08 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/05/31 20:37:46 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_index(t_env *env)
{
	t_env *tmp;
	t_env *tmp2;
	int size;

	tmp2 = env;
	size = 0;
	while (env)
	{
		tmp = tmp2;
		while (tmp)
		{
			if (ft_strcmp(env->env, tmp->env) > 0)
				size++;
			tmp = tmp->next;

		}
		env->index = size;
		size = 0;
		env = env->next;
	}
}

void	strjoin_export(t_env *env, char *s1)
{
	int i;
	char *p;
	char *p2;
	t_env *tmp;

	tmp = env;
	i = 0;
	while (s1[i] != '+')
		i++;
	p = ft_substr(s1, 0, i);
	p2 = ft_strjoin2(p ,ft_strdup("="));
	while (env)
	{
		if (!ft_strcmp(env->env, p) || !ft_strcmp(env->env, p2) || !ft_strcmp(p, p2))
		{
			free(env->valu);
			if (!ft_strcmp(env->env, p))
				env->env = p2;
			else
				free(p2);
			env->valu = ft_strjoin2(env->valu,ft_substr(s1,i+2,ft_strlen(s1)));
			free(p);
			return;
		}
		env = env->next;
	}
	t_env *new = lstnew_env(p2,ft_substr(s1,i+2,ft_strlen(s1)));
	lstadd_back_env(&tmp, new);
}

int	is_key_already_exist(t_env *env, char *key, char *value)
{
	char *str;
	char *str2;

	while (env)
	{
		str = ft_strjoin2(env->env, ft_strdup("="));
		str2 = ft_strjoin2(key, ft_strdup("="));
		if (!strcmp (str, key))
		{
			free(env->valu);
			free(env->env);
			env->env = str;
			env->valu = value;
			return(1);
		}
		else if (!strcmp (env->env, key))
		{
			free(env->valu);
			env->valu = value;
			free(str);
			return(1);
		}
		else if (!strcmp (str2,env->env))
		{
			free(env->env);
			env->env = str2;
			return (1);
		}
		free(str);
		env = env->next;
	}
	return(0);
}


void exec_export(t_env *env ,char **str)
{

	t_env *new;
	int	i;
	int len;
	int size;

	i = 0;
	size = 0;
	len = ft_lstsize_env(env);
	t_env *tmp;

	if (str[i + 1] == NULL)
	{
		sort_index(env);
		while (size < len)
		{
			tmp = env;
			while (tmp)
			{
				if (tmp->index == size)
				{
					if (tmp->env[ft_strlen(tmp->env) - 1] == '=')
						printf("declare -x %s\"%s\"\n",tmp->env, tmp->valu);
					else
						printf("declare -x %s\n",tmp->env);
					break ;
				}
				tmp = tmp->next;
			}
			size++;
		}
	}
	else
	{
		i++;
		while (str[i] != NULL )
		{
			int j = 1;
			if (!ft_isalpha(str[i][0]) && str[i][0] != '_')
			{
				printf("export: `%s': not a valid identifier\n",str[i]);
				return ;
			}
			while (str[i][j] != '\0' && str[i][j] != '=')
			{
				if (str[i][j] == '+' && str[i][j + 1] == '=')
					break;
				if (!ft_isalpha(str[i][j]) && !ft_isdigit(str[i][j]) && str[i][j] != '_')
				{
					printf ("export: `%s': not a valid identifier\n",str[i]);
					return ;
				}
				j++;
			}
			if (str[i][j] == '=' || str[i][j] == '\0')
			{
				char * key = ft_substr(str[i], 0, find_equal(str[i]));
				char * value = ft_substr(str[i],  find_equal(str[i]), ft_strlen(str[i]));
				if (!is_key_already_exist(env,key,value))
				{
					t_env *new = lstnew_env(key, value);
					lstadd_back_env(&env, new);
				}
			}
			else if (str[i][j] == '+' && str[i][j+1] == '=')
			{
				strjoin_export(env,str[i]);
			}
			i++;
		}
	}
}

// int main (int argc, char **argv, char **envp)
// {
// 	(void) argc;
// 	t_env *env;
// 	char *line;
// 	 env = remp(envp);
// 	// print_env(env);
// 	while((line = readline("minishell>")))
// 	{
// 		printf("%s\n", line);
// 		exec_export(env ,ft_split(line, ' '));
// 	}
// }
