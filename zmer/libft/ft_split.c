/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kabb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:00:30 by mel-kabb          #+#    #+#             */
/*   Updated: 2023/06/02 17:17:25 by mel-kabb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int    count(const char *s1, char c)
{
    int    i;
    int    w;
    int    set;

    set = 0;
    i = 0;
    w = 0;
    if(!s1 || !s1[i])
        return(0);
    while (s1[i])
    {
        while (s1[i] == c && s1[i])
            i++;
        if ((s1[i] != c && s1[i]) && (s1[i] != '"' && s1[i] != '\''))
            w += 1;
        while ((s1[i] != c && s1[i]) && (s1[i] != '"' && s1[i] != '\''))
            i++;
        if (s1[i] == '"' || s1[i] == '\'')
        {
            i++;
            while((s1[i] != '"' && s1[i] != '\'') && s1[i])
                i++;
            if (s1[i] == '"' || s1[i] == '\'')
                w++;
            while ((s1[i] != c && s1[i]) && (s1[i] != '"' && s1[i] != '\''))
                i++;
        }
        if (i >= ft_strlen(s1))
            break;
        i++;
    }
    //printf("w ==== {%d}\n",w);
    return (w);
}

static char    ft_free(int iny, char **x)
{
    while (iny--)
        free(x[iny]);
    free(x);
    return (0);
}

static char    **pip(char **p, char const *str, char c)
{
    int    i;
    int    ind;
    int    j;
    int    k;

    i = 0;
    ind = -1;
    while (str[i] && ++ind < count(str, c))
    {
        while (str[i] && str[i] == c)
            i++;
        j = i;
        while ((str[i] && str[i] != c) && (str[i]!= '"' && str[i] != '\''))
            i++;
        while (str[i] == '"' || str[i] == '\'')
        {
            i++;
            while(str[i] && (str[i] != '"'  && str[i] != '\''))
                i++;
            if (str[i] == '"' || str[i] == '\'')
                i++;
            while ((str[i] != c && str[i]) && (str[i] != '"' && str[i] != '\''))
                i++;
        }
        p[ind] = ft_calloc((i - j + 1), 1);
        if (!p)
        {
            ft_free(ind, p);
            return (0);
        }
        k = 0;
        while (j < i)
            p[ind][k++] = str[j++];
    }
    return (p);
}

char    **ft_split(char *s1, char c)
{
    char    **p;
    int        i;

    i = 0;
    if (!s1)
        return (NULL);
    p = ft_calloc((count(s1, c) + 2), sizeof(char *));
    if (!p)
        return (0);
    p = pip(p, s1, c);
    return (p);
}
