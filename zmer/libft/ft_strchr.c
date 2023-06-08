/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:44:00 by mel-kabb          #+#    #+#             */
/*   Updated: 2023/05/31 20:14:33 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	int		j;
	char	*t;
	char	d;

	j = 0;
	t = (char *)str;
	d = (char)c;
	i = 0;
	if (d == 0)
	{
		while (t[i])
			i++;
		return (&t[i]);
	}
	while (t[i])
	{
		if (t[i] == d)
			return (&t[i]);
		i++;
	}
	return (0);
}

int 	ft_strchr1(char *t)
{
	int		i;

	i = 0;
	while (t[i])
	{
		if (ft_isalnum(t[i])  == 0)
			return (i);
		i++;
	}
	return (-1);
}
