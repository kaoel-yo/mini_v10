/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:34:58 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/06/02 18:59:49 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_env_value(t_env *env, char *key)
{
    while (env != NULL)
    {
        if(!ft_strncmp(key, env->env, ft_strlen(key)) && env->env[ft_strlen(key)] == '=')
        {
            return (env->valu) + 1;
        }
        env = env->next;
    }
    return NULL;
}

void change_env_value(t_env *env, char *key, char *new_value)
{
    while(env != NULL)
    {
        if(!ft_strncmp(key, env->env, ft_strlen(key)) && env->env[ft_strlen(key)] == '=')
        {
            env->valu = new_value;
        }
        env = env->next;
    }
}

int exec_cd(t_env *env, t_help *help)
{
    int i;
    char *home;
    char *pwd;
    int cd;

    i = 1;
    pwd = get_env_value(env, "PWD");
    home = get_env_value(env, "HOME");
    //printf("=====%s\n",home);
    if (help->cmd[i] == NULL)
    {
        if (!home)
            write(2, "minishell: cd: Home not set\n", 29);
        else
        {
            // char pp[100];
            chdir(home);
            //     printf("%d\n", chdir(home));
            // getcwd(pp, sizeof(pp));
            // printf("pp == > %s\n", home);
            change_env_value(env, "OLDPWD", pwd);
            change_env_value(env, "PWD", home);
        }
    }
    else
    {
        cd = chdir(help->cmd[i]);
        if (!cd)
        {
            change_env_value(env, "OLDPWD", pwd);
            change_env_value(env, "PWD", help->cmd[i]);
        }
        else
            perror(help->cmd[i]);
    }
    return 0;
}

// int main (int argc, char **argv, char **envp)
// {
//         t_env *env;
//         env = exec_env(envp);
//         exec_cd (env,argv);
//         exec_pwd();
// }
