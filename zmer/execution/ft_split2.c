/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:27:18 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/06/01 11:29:02 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_count(const char *str, char c)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && ((i == 0) || (str[i - 1] == c)))
			j++;
		i++;
	}
	return (j);
}

static int	ft_free(char ***tab, int i)
{
	char	**t;

	t = *tab;
	if (!t[i])
	{
		while (i >= 0)
		{
			free(t[i]);
			i--;
		}
		free(t);
		return (1);
	}
	return (0);
}

static char	**rempl(char const *s, char c, char **tab)
{
	size_t	i;
	size_t	j;
	size_t	start;

	start = 0;
	i = 0;
	j = 0;
	while (i < ft_count(s, c))
	{
		while (s[j] && s[j] == c)
			j++;
		start = j;
		while (s[j] && s[j] != c)
			j++;
		tab[i] = ft_substr(s, start, j - start);
		if (ft_free(&tab, i))
			return (0);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split2(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!tab)
		return (NULL);
	return (rempl(s, c, tab));
}
