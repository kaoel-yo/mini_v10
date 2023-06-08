/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 02:58:52 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/06/08 16:11:15 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void exec_unset(t_env *env, char **str)
{
    int i;
    int j;

    i = 1;
    while (str[i] != NULL)
    {
        j = 0;
        if (!ft_isalpha(str[i][0]) && str[i][0] != '_'){
            perror(str[i]);
        }
        else
        {
            j++;
            while(str[i][j] != '\0')
            {
                if (!ft_isalpha(str[i][j]) && !ft_isdigit(str[i][j] && str[i][j] != '_'))
                {
                    perror(str[i]);
                    break;
                }
                j++;
            }
            if (str[i][j] == '\0')
            {
                //printf("sodirg \n");
                delete_node(&env, str[i]);
            }
        }
        i++;
    }
}

// int main(int argc, char **argv, char **envp)
// {
//     (void) argc;
// 	t_env *env;
// 	env = remp(envp);
//     exec_unset(env, argv);
//     exec_export(env ,argv);

// }

