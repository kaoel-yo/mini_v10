/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:11:56 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/06/08 16:10:11 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtins(t_env *env, t_help *help, char **envp)
{
	int i;
	
	i = 0;
	if (help->cmd)
	{
		if (!strcmp(help->cmd[i], "cd"))
			exec_cd(env,help); //done
		else if (!strcmp(help->cmd[i], "echo"))
			exec_echo(help->cmd); // done
		else if (!strcmp(help->cmd[i],"pwd"))
			exec_pwd(); //done
		else if (!strcmp(help->cmd[i], "env"))
			print_env(env, envp); //done
		else if (!strcmp(help->cmd[i], "export"))
			exec_export(env,help->cmd); //done
		else if (!strcmp(help->cmd[i], "unset"))
			exec_unset(env,&help->cmd[i]); //done
		else if (!strcmp(help->cmd[i], "exit"))
			ft_exit(help);//done
		else
			return (0);

	}
	return (1);
}

// int main (int argc, char **argv, char **envp)
// {
// 	(void) argc;
// 	t_env	*env;
// 	t_help help;
// 	g_gl = malloc(sizeof(t_g));
// 	g_gl->ex_status = 0;
// 	char *line;
// 	if (!envp[0])
// 		{
// 			printf("kkkk=> %s\n", envp[0]);
// 			exit (4);
// 		}
// 	env = remp(envp);
// 	// print_env(env);
// 	while((line = readline("minishell>")))
// 	{
// 		help.cmd = ft_split(line, ' ');
// 		// printf("%s\n", line);
// 		builtins(env,&help, envp);
// 	}
//}
