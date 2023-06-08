/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:09:18 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/06/02 20:18:13 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_option(char *str)
{
	int i;
	int j;

	i = 0;

	if (str[i] == '-' )
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return(1);
		i++;
	}
	return (0);
}
void	exec_echo(char **str)
{
	int i;
	int n;

	i = 1;
	n = 0;

	while (str[i] && !check_option(str[i]))
	{
		n = 1;
		i++;
	}

	while (str[i])
	{
		ft_putstr_fd(str[i],1);
		if (str[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n == 0)
		write(1,"\n",1);
}
// int main (int argc, char **argv, char **envp)
// {
// 	int i;
// 	int j;

// 	if (argc > 1)
// 	{
// 		exec_echo(argv);

// 	}
// }