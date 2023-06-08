/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kabb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:54:05 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/06/08 19:44:26 by mel-kabb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../minishell.h"

 char	*get_full_path(t_env *env)
{
	while (env)
	{
		if(!ft_strcmp(env->env, "PATH="))
			return (env->valu);
		env = env->next;
	}
	return (NULL);
}

char	*get_cmd_path(t_help *help)
{
	int		i;
	char	*save;
	char	*cmd_path;

	i = 0;

	if (!ft_strncmp(help->cmd[0], "/", 1))
		return (help->cmd[0]);
	// exit(0);
	while (help->paths[i] != NULL)
	{
		save = ft_strjoin2(help->paths[i], "/");
		cmd_path = ft_strjoin2(save,help->cmd[0]);
		free (save);
		if (access(cmd_path, 0) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

void	ft_dup(t_help *help , int **fd, int size, int idx)
{
	if (size == 1)
	{
		printf("kkkkk\n");
		if (help->fd_out > 1)
		{
			dup2(help->fd_out,1);
			return;
		}
		else if (help->fd_in > 1)
		{
			dup2(help->fd_in,0);
			return;
		}
		else
			return;
	}
	else
	{
		if (help->index == size - 1)
		{
			printf ("lekhar\n");
			// close (fd[1]);
			if (help->fd_in > 1)
			{
				dup2(help->fd_in,0);
				return;
			}
			if (help->fd_out > 1)
			{
				dup2(help->fd_out,1);
				return;
			}
			else
			{
				printf ("last %d     %d\n", fd[idx - 1][0], fd[idx - 1][1]);
				close(fd[idx - 1][1]);
				dup2(fd[idx - 1][0], 0);
				close(fd[idx - 1][0]);
				write (1, "salam\n", 6);
				return;
			}

		}
		else if (help->index == 0)
		{
			printf ("hhhh\n");
			// close (fd[0]);
			if (help->fd_in > 1)
			{
				write (1, "1\n", 2);
				dup2(help->fd_in ,0);
			}
			if (help->fd_out > 1)
			{
				dup2(help->fd_out,1);
				return;
			}
			else
			{
				printf ("ggg %d     %d\n", fd[idx][0], fd[idx][1]);
				close(fd[idx][0]);
				dup2(fd[idx][1], 1);
				// dup2(fd[0], 0);
				close(fd[idx][1]);
			}
		}
		else
		{
			printf ("nnnn\n");
			dup2(fd[idx - 1][0], 0);
			close(fd[idx - 1][0]);
			close(fd[idx - 1][1]);
			// close(fd[0]);
			if (help->fd_in > 1)
			{
				dup2(help->fd_in ,0);
				// dup2(fd[1],1);
			}
			if (help->fd_out > 1)
			{
				dup2(help->fd_out,1);
				// close (fd[1]);
			}
			else
			{
				close(fd[idx][0]);
				dup2(fd[idx][1],1);
				close(fd[idx][1]);
			}
		}
	 }
}

// ls > txt | grep lib | wc -l


void	execution(t_help **help, t_env *env, char **envp)
{
	int i;
	int j = 0;
	int **fd;
	int status;
	pid_t id;
	// int k = dup(0);
	// int g = dup(1);
	t_help *temp = *help;
	i = ft_lstsize(temp);
	if ((builtins(env, temp,envp)) && i == 1)
		return;
	fd = malloc(sizeof(int *) * i);
	int k = -1;
	while (++k < i)
		fd[k] = malloc(sizeof(int) * 2);
	while (temp)
	{
		if (temp->next != NULL)
			pipe(fd[j]);
		id = fork();
		if (id == 0)
		{
			temp->fullpath = get_full_path(env);
			temp->paths  = ft_split2(temp->fullpath, ':');
			temp->cmd_path = get_cmd_path(temp);
			ft_dup(temp, fd, ft_lstsize(*help), j);
			// close(fd[0]);
			fprintf(stderr, "%d-----\n", j);
			execve(temp->cmd_path, temp->cmd, envp);
			//perror("execve");
			exit(127);
		}
		// else
		// {
		// 	waitpid(-1,&status,0);
		// 	// dup2(fd[0], 0);
		// 	close(fd[1]);
		// 	close(fd[0]);
		// }
		if(j > 0)
		{
			fprintf(stderr, "csacasc  %d \n", j);
			close(fd[j - 1][0]);
			close(fd[j - 1][1]);
		}
		temp = temp->next;
			fprintf(stderr, "%d------>\n", j);
		j++;
	}
		while(wait(NULL) != -1);
	//wait(NULL);
	// dup2(k, 0);
	// dup2(g, 1);
			// close(fd[0]);
			// close(fd[1]);
}

// int main (int argc, char **argv, char **envp)
// {

// 		t_env	*env;
// 		t_help help;
// 		help.fd_in = -1;
// 		help.fd_out = -1;
// 		// t_mini	mini;
// 		g_gl = malloc(sizeof(t_g));
// 		g_gl->ex_status = 0;
// 		char *line;
// 		env = remp(envp);
// 		// print_env(env,envp);
// 		// if (!envp[0])
// 		// 	{
// 		// 		printf("kkkk=> %s\n", envp[0]);
// 		// 		exit (4);
// 		// 	}
// 		// printf ("============>%s\n",get_full_path(env));
// 		while((line = readline("minishell>")))
// 		{
// 				help.cmd = ft_split2(line, ' ');
// 				// int j = 0;
// 				// while (help.cmd[j])
// 				// {
// 				// 	printf ("help_cmd == %s\n", help.cmd[j]);
// 				// 	j++;
// 				// }


// 				// printf ("fullpath = %s\n", help.fullpath);
// 				// int i = 0;
// 				// while(help.paths[i] != NULL)
// 				// {
// 				// 	printf ("help.path == %s\n", help.paths[i]);
// 				// 	i++;
// 				// }

// 				// printf("cmd_path ==>%s\n",help.cmd_path);

// 				execution(&help, env, envp);

// 		}
// }
// // 		}
// // 		t_mini	mini;
// // 		mini.fullpath = get_full_path(env);
// // 		mini.paths  = ft_split2(mini.fullpath, ':');
// // 		printf ("fullpath = %s\n", mini.fullpath);
// // 		int i = 0;
// // 		while(mini.paths[i] != NULL)
// // 		{
// // 			printf ("mini.path == %s\n", mini.paths[i]);
// // 			i++;
// // 		}
// // 		help->cmd = ft_split2(argv[1],' ');
// // 		mini.cmd_path = get_cmd_path(mini.paths,help->cmd[0]);
// // 		printf("cmd_path ==>%s\n",mini.cmd_path);

// // 		int j = 0;
// // 		while (help->cmd[j])
// // 		{
// // 			printf ("help_cmd == %s\n", help->cmd[j]);
// // 			j++;
// // 		}
// // 	}

// // 	// if (pipe(mini.fd) < 0)
// // 	// 	ft_putstr_fd("error pipe\n", 2);
// // 	// mini.pid1 = fork();

// // }

