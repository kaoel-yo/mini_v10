/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:24:35 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/05/31 20:35:44 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exec_pwd()
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	else
		write(1, cwd, ft_strlen(cwd));
	return 0;
}

// int main(int argc, char **argv)
// {
// 	if (argc == 2)
// 		exec_pwd();
// }