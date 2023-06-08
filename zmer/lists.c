

#include "minishell.h"

t_help	*ft_lstnew(int content)
{
	t_help	*node;

	node = (t_help *)malloc(sizeof(*node));
	if (!(node))
		return (NULL);
	node->index = content;
	node->cmd = NULL;
	node->next = NULL;
	node->paths = NULL;
	node->fullpath = NULL;
	node->cmd_path = NULL;
	node->pre = NULL;
	return (node);
}

t_add	*ft_lstnew1(int content)
{
	t_add	*node;

	node = (t_add *)malloc(sizeof(*node));
	if (!(node))
		return (NULL);
	node->file = NULL;
	node->type = -1;
	node->sep = NULL;
	node->str = NULL;
	node->limit = NULL;
	node->next = NULL;
	node->pre = NULL;
	return (node);
}
int	ft_lstsize_env(t_env *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_lstdelone(t_list **lst)
{
	t_list	*tmp;

	if (lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}
int	ft_lstsize(t_help *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}


void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst)
	{
		if (*alst)
			new->next = *alst;
		*alst = new;
	}
}
void	ft_lstadd_back(t_help **alst, t_help *new)
{
	t_help	*last;

	if (alst)
	{
		if (*alst)
		{
			last = ft_lstlast(*alst);
			last->next = new;
		}
		else
			*alst = new;
		new->pre = last;
	}
}

t_help	*ft_lstlast(t_help *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back1(t_add **alst, t_add *new)
{
	t_add	*last;

	if (alst)
	{
		if (*alst)
		{
			last = ft_lstlast1(*alst);
			last->next = new;
		}
		else
			*alst = new;
		new->pre = last;
	}
}


t_add	*ft_lstlast1(t_add *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*p;
	int				i;
	int j;

	i = 0;
	if(!s2)
		return (NULL);
	if(!s1)
		return(s2);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while(s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	while(s2[i])
	{
		p[j++] = s2[i++];
	}
	p[j] = '\0';
	// free(s2);
	return (p);
}

void 	delete_node(t_env **env, char* key)

{
	char *str;
    t_env *temp;
	temp = (*env);
	t_env *del;

	str = ft_strjoin2(key, ft_strdup("="));
	if (!(*env))
		return ;
	if (!ft_strcmp(temp->env, str) || !ft_strcmp(temp->env, key))
	{
		del = temp;
		*env = (*env)->next;
		free(del);
		free(str);
		return;
	}
	while (temp->next)
	{
		if (!ft_strcmp(temp->next->env, str) || !ft_strcmp(temp->next->env, key))
		{
			del = temp->next;
			temp->next = temp->next->next;
			free(del);
			return;
		}
		temp = temp->next;
	}
	free(str);
}
