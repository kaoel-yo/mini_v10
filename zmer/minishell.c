
#include "minishell.h"

int	calc_space(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (s[i - 1] != ' ')
			{
				j += 1;
			}
			if (s[i + 1] != ' ' && s[i + 1] != '\0')
			{
				j += 1;
			}
		}
		i++;
	}
	return (j + i);
}

char	*ft_add_space(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*src;

	i = 0;
	j = 0;
	len = calc_space(s, '|');
	src = ft_calloc(sizeof(char) * len + 1, 1);
	while (s[i] && i < len)
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			src[j++] = s[i++];
			while (s[i]  && (s[i] != '"' && s[i] != '\''))
			{
				src[j++] = s[i++];
			}
			if (!s[i])
				break;
			src[j++] = s[i++];
		}

		if (s[i] == '|' && s[i - 1] == ' ' && s[i + 1] == ' ')
			src[j++] = s[i++];
		if (s[i] == '|' && s[i - 1] != ' ')
		{
			src[j++] = ' ';
			src[j++] = '|';
			i++;
		}
		if (i != 0 && (s[i - 1] == '|' && s[i] != ' '))
			src[j++] = ' ';
		src[j++] = s[i++];
	}
	//src[j] = '\0';
	return (src);
}

int calc_re(char *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(str[i])
	{
		if(str[i] == c)
		{
			if(str[i] != c && str[i - 1] != ' ')
				j++;
			else if(str[i + 1] == c && str[i + 2] != ' ')
				j++;
			else if(str[i + 1] != c && str[i] != ' ')
				j++;
		}
		i++;
	}
	return (i + j);
}

char	*ft_add_space2(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*src;

	i = 0;
	j = 0;
	len = calc_re(s,'<');
	src = ft_calloc(sizeof(char) * len +1, 1);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			src[j++] = s[i++];
			while (s[i]  && (s[i] != '"' && s[i] != '\''))
			{
				src[j++] = s[i++];
			}
			if (!s[i])
				break;
			src[j++] = s[i++];
		}
		if (s[i] == '<')
		{
			if (i != 0 && s[i - 1] != ' ' && (s[i + 1] != '<' || s[i + 1] == '<'))
				src[j++] = ' ';
			src[j++] = s[i++];
			if (s[i] == '<')
				src[j++] = s[i++];
			if (s[i] != ' ')
				src[j++] = ' ';
		}
		src[j++] = s[i++];
	}
	src[j] = '\0';
	return (src);
}

char	*ft_add_space3(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*src;

	i = 0;
	j = 0;
	len = calc_re(s,'>');
	src = ft_calloc(sizeof(char) * len +1, 1);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			src[j++] = s[i++];
			while (s[i]  && (s[i] != '"' && s[i] != '\''))
			{
				src[j++] = s[i++];
			}
			if (!s[i])
				break;
			src[j++] = s[i++];
		}
		if (s[i] == '<')
		{
			if (i != 0 && s[i - 1] != ' ' && (s[i + 1] != '<' || s[i + 1] == '>'))
				src[j++] = ' ';
			src[j++] = s[i++];
			if (s[i] == '>')
				src[j++] = s[i++];
			if (s[i] != ' ')
				src[j++] = ' ';
		}
		src[j++] = s[i++];
	}
	src[j] = '\0';
	return (src);
}


int	ft_send(char *s, t_add **l)
{
	int		i;
	t_add	*p;

	p = *l;
	if (ft_strncmp(s, "<<", 3) == 0)
		p->type = 4;
	else if (ft_strncmp(s, ">>",3) == 0)
		p->type = 2;
	else if (ft_strncmp(s, "<",2) == 0)
		p->type = 1;
	else if (ft_strncmp(s, ">",2) == 0)
		p->type = 3;
	else
		return (0);
	return (1);
}

// void	ft_help1(int signum)
// {
// 	if(signum == SIGINT)
// 		unlink("/tmp/heredoc");
// }

t_help *herdoc(t_help *p,char *str, char *line, char **env)
{
	if(fork() == 0)
	{
		p->fd_in = open("/tmp/heredoc", O_CREAT | O_TRUNC | O_WRONLY,0666);
		line = readline("> ");
		//signal(SIGINT, SIG_DFL);
		while (line != NULL)
		{
			ft_putstr_fd(line, p->fd_in);
			if (!ft_strcmp(line, p->m->limit))
				break ;
			skip_quote(line,env);
			free(line);
			line = readline("> ");
		}
	}
	// signal(SIGINT,ft_help1);
	wait(NULL);
	if(access("/tmp/heredoc",F_OK | R_OK))
	{
		close(p->fd_in);
		p->fd_in = -2;
	}
	return(p);
}


t_help	*rempl(char *m, t_help **l, char **env)
{
	int		i;
	int		j;
	t_help	*p;
	char	**str;
	char	*line;

	i = 0;
	p = *l;
	j = 0;
	p->m = ft_lstnew1(0);
	str = ft_split(m, ' ');
	while (str[i])
	{
		if (ft_send(str[i], &p->m) == 1)
		{
			// printf("str[i] == (%s)\n",str[i]);
			p->m->sep = str[i];
			if (p->m->type == 3 && str[i + 1])
			{
				// printf("out\n");
				p->m->file = str[i + 1];
				p->fd_out = open(str[i + 1], O_CREAT | O_TRUNC | O_WRONLY,0644);
				if (p->fd_out == -1)
					perror(p->m->file);
			}
			else if (p->m->type == 1 && str[i + 1])
			{
				// printf("in\n");
				p->m->file = str[i + 1];
				p->fd_in = open(str[i + 1], O_RDONLY);
				if (p->fd_out == -1)
					perror(p->m->file);
			}
			else if (p->m->type == 2 && str[i + 1])
			{
				// printf("app\n");
				p->m->file = str[i + 1];
				p->fd_out = open(str[i + 1], O_CREAT | O_APPEND | O_WRONLY,0644);
				if (p->fd_out == -1)
					perror(p->m->file);
			}
			else if (p->m->type == 4 && str[i + 1])
			{
				// printf("herd\n");
				p->m->limit = str[i + 1];
				p = herdoc(p,str[i],line, env);
			}

			i++;
			if (!str[i])
				break ;
			j++;
			ft_lstadd_back1(&p->m, ft_lstnew1(j));
			p->m = p->m->next;
			p->m->str = p->m->pre->str;
		}
		else
		{
			//printf("str=======%s===first=======\n", p->m->str);
			//printf("str ==== {%s}\n",str[i]);
			line = ft_strjoin(p->m->str, skip_quote(str[i], env));
			// printf("line ==== {%s}\n",line);
			p->m->str = line;
		}
		i++;
	}
	return (p);
}

int ft_check_error2(char *str)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while(str[i])
	{
		if(str[i] == '\'')
		{
			i++;
			while(str[i] && str[i] != '\'')
				i++;
			if(str[i] == '\0')
			{
				printf("bash: syntax error near unexpected token `\''\n");
				g_gl->ex_status = 258;
				return 1;
			}
			i++;
		}
		else
			i++;
	}
	return 0;
}

int	ft_checkpoint(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str) - 1;
	i = 0;

	while (str[i])
	{
		if(str[i] == '"')
			while(str[i + 1] && str[++i] != '"');
		if(str[i] == ';')
		{
			i++;
			if(str[i] == ' ')
				i++;
			if(str[i] == ';')
			{
				printf("bash: syntax error near unexpected token `;;'\n");
				g_gl->ex_status = 258;
				return(1);
			}
		}
		if(str[i])
			i++;
	}
	return(0);
}

int ft_check_error1(char *str)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	// if(ft_checkpoint(str) == 1)
	// 	return(1);
	if(ft_check_error2(str) == 1)
		return(1);
	while(str[i])
	{
		if(str[i] == '"')
		{
			i++;
			while(str[i] && str[i] != '"')
				i++;
			if(str[i] == '\0')
			{
				printf("error == %c",str[i]);
				printf("bash: syntax error near unexpected token `\"'\n");
				g_gl->ex_status = 258;
				return 1;
			}
			i++;
		}
		else
			i++;
	}
	return 0;
}



int	ft_checkerror(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str) - 1;
	i = 0;
	if(ft_check_error1(str))
		return(1);
	while (str[i])
	{
		if(str[i] == '"')
			while(str[i + 1] && str[++i] != '"');
		if (str[0] == '|')
		{
			printf("bash: syntax error near unexpected token `|'\n");
			g_gl->ex_status = 258;
			return(1);
		}
		if(str[i] == '|' && str[i + 1] == '\0')
		{
			printf("bash: syntax error near unexpected token `|'\n");
			g_gl->ex_status = 258;
			return(1);
		}
		if(str[i] == '|')
		{
			i++;
			if(str[i] == ' ')
				i++;
			else if(str[i] == '|')
			{
				printf("bash: syntax error near unexpected token `||'\n");
				g_gl->ex_status = 258;
				return(1);
			}
		}
		if(str[i])
			i++;
	}
	return(0);
}

int	calcu_upper(char *cmd)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (cmd[i])
	{
		if (cmd[i] >= 'A' && cmd[i] <= 'Z')
		{
			k++;
		}
		i++;
	}
	return (k);
}

void	ft_printf_les_node(t_help *sa)
{
	while(sa)
	{
		int i;
		i = 0;
		while (sa->cmd[i])
		{
			// printf("cmd[%d] ==== %s\n",i, sa->cmd[i]);
			i++;
		}
		// printf ("infile = %d\n", sa->fd_in);
		// printf ("outfile = %d\n", sa->fd_out);
		sa = sa->next;
	}
}

int check_space(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(str[i])
	{
		if(str[i] == ' ')
		{
			i++;
		}
		else
			break;
	}
	return(i);
}

int	main(int ac, char **av, char **envp)
{
	char	*buff;
	char	**tmp;
	t_help	*m;
	t_help	*sa;
	t_env	*en;
	char	*user;
	char	*value;
	char	*s;
	int		i;
	int		j;

	(void)ac;
	(void)av;
	g_gl = malloc(sizeof(t_g));
	while (1)
	{
		m = NULL;
		j = 0;
		i = 0;
		buff = readline("minishell>");
		if (buff == NULL)
		{
			printf("hna\n");
			break;
		}
		add_history(buff);
		if(check_space(buff) == ft_strlen(buff))
		{
			free(buff);
			continue;
		}
		if (buff[0] == '\0')
		{
			free(buff);
			continue;
		}
		if(ft_checkpoint(buff) == 1)
		{
			free(buff);
			continue;
		}
		if(ft_checkerror(buff))
		{
			free(buff);
			continue;
		}
		while (buff[i])
		{
			if (buff[i] == '|' || buff[i] == '<' || buff[i] == '>')
			{
				if (buff[i] == '|')
					buff = ft_add_space(buff);
				else if (buff[i] == '<' || (buff[i] == '<' && buff[i + 1] == '<'))
						buff = ft_add_space2(buff);
				else if (buff[i] == '>' || (buff[i] == '>' && buff[i + 1] == '>'))
						buff = ft_add_space3(buff);
			}
			i++;
		}
		int k = -1;
		sa = m;
		tmp = ft_split(buff, '|');
		i = -1;
		en = remp(envp);
		while (tmp[++i])
		{
			m = ft_lstnew(i);
			ft_lstadd_back(&sa, m);
			m->index = i;
			k = -1;

			rempl(tmp[i], &m,envp);
			m->cmd = ft_split(m->m->str,'\n');

			// if(m->cmd)
			// 	while(m->cmd[++k])
					// printf("cmd == {%s}\n",m->cmd[0]);
			//ft_lstadd_back(&m, ft_lstnew(i))
			//m = m->next;
			//m->next = NULL;
		}

		m->next = NULL;
		m = sa;
		// printf ("///////////////////////////\n");
		// ft_printf_les_node(sa);
		execution(&m, en,envp);
	}
	printf("exit11\n");
	exit(0);
}
