/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:21:09 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/05/31 20:35:28 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int find_equal(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0' && str[i] != '=')
		i++;
    if ( str[i] == '=')
        i += 1;
	return i;
}

void	lstadd_back_env(t_env **env, t_env *new)
{
    t_env *ptr;

    if (!env || !new)
        return ;
    if (!*env)
        *env = new;
    else
    {
        ptr = *env;
        while (ptr->next)
            ptr = ptr->next;
        ptr->next = new;
    }
}

t_env *lstnew_env(char *key, char *value)
{
    t_env *list;

    list = malloc(sizeof(t_env));
    if (!list)
        return (NULL);
    list->env = key;
    list->valu = value;
    list->index = 0;
    list->next= NULL;
    return(list);
}
t_env *remp (char **envp)
{
    t_env *env;
    t_env *new;
    char *key;
    char *value;

    env = NULL;
    int i = 0;

    if (envp == NULL)
        return(env);
    while (envp[i] != NULL)
    {
		key = ft_substr(envp[i],0,find_equal(envp[i]));
		value = ft_substr(envp[i], find_equal(envp[i]), ft_strlen(envp[i]));
        new = lstnew_env(key, value);
		// free(value);
		// free(key);
        lstadd_back_env(&env, new);
        i++;
    }
    return (env);
}

void   print_env(t_env *env, char **envp)
{
    while (env)
    {
        if (env->env[ft_strlen(env->env)- 1] == '=')
            printf("%s%s\n", env->env, env->valu);
        env = env->next;
    }
}

// int main (int argc, char **argv, char **envp)
// {
//     (void) argc;
// 	t_env *env;
// 	char *line;

// 	while((line = readline("minishell>")))
// 	{
// 		printf("%s\n", line);
// 		print_env(env, envp);
// 	}
// }


