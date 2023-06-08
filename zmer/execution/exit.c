/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:36:39 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/05/31 20:35:54 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_status(int ex_stat, int x)
{
	g_gl->ex_status = ex_stat;
	if (x == 1)
		exit (ex_stat);
}

void	ft_exit(t_help *help)
{
	int i;
	int j;
	i = 1;
	j = 0;

	if (help->cmd[i] == NULL)
	{
		ft_putstr_fd("exit\n",2);
		ft_exit_status(g_gl->ex_status, 1);
	}
	if (help->cmd[i + 1] == NULL)
	{
		while (help->cmd[i][j])
		{
			if (!ft_isdigit(help->cmd[i][j]))
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(help->cmd[i], 2);
				ft_putstr_fd(": numeric argument required\n",2);
				ft_exit_status(255, 1);
			}
			else if(ft_isdigit(help->cmd[i][j]))
			{
				ft_putstr_fd("exit\n",2);
				ft_exit_status(ft_atoi(help->cmd[i]), 1);
			}
			j++;
		}
	}
	else
	{
		while (help->cmd[i])
		{
			while (help->cmd[i][j])
			{
				if (!ft_isdigit(help->cmd[i][j]))
				{
					ft_putstr_fd("exit\n", 2);
					ft_putstr_fd("minishell: exit: ", 2);
					ft_putstr_fd(help->cmd[i], 2);
					ft_putstr_fd(": numeric argument required\n",2);
					ft_exit_status(255, 1);
				}
				j++;
			}
			if( help->cmd[i][j] == '\0')
			{
				ft_putstr_fd("exit\n",2);
				ft_putstr_fd("minishell: exit: too many arguments\n", 2);
				ft_exit_status(1, 0);
				break;
			}
			i++;
		}

	}

}



