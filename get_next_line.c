/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza-c <jsouza-c@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:25:20 by jsouza-c          #+#    #+#             */
/*   Updated: 2022/02/19 18:41:26 by jsouza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*g_lst;
int				g_buffer;
int				g_len;
char			*g_yank;
t_list			*g_hold;

static char	*glue(char *fd)
{
	char	*complete;

	complete = (char *)malloc((g_len + g_buffer + 1) * sizeof(char));
	if (complete == NULL)
		return (NULL);
	g_buffer = 0;
	while (g_lst && g_lst->content[g_buffer] != '\0')
	{
		complete[g_buffer] = g_lst->content[g_buffer];
		g_buffer++;
	}
	if (g_lst)
		free(g_lst);
	g_len = 0;
	while (fd[g_len] != '\0')
	{
		complete[g_buffer] = fd[g_len];
		g_buffer++;
		if (fd[g_len] == '\n')
			break ;
		g_len++;
	}
	complete[g_buffer] = '\0';
	return (complete);
}

static t_list	*next_node(char *fd)
{
	char	*hold;

	while (*fd != '\n')
		fd++;
	if (fd[1] != '\0')
		fd++;
	g_buffer = g_len;
	while (fd[g_len])
		g_len++;
	g_hold = (t_list *)malloc(sizeof(t_list));
	if (g_hold == NULL)
		return (NULL);
	hold= (char *)malloc((g_len + 1) * sizeof(char));
	if (hold == NULL)
		return (NULL);
	g_len = 0;
	while (fd[g_len] != '\0')
	{
		hold[g_len] = fd[g_len];
		g_len++;
	}
	hold[g_len] = '\0';
	g_hold->content = hold;
	g_lst->next = g_hold;
	return (g_hold);
}

static t_list	*nodes(char *line)
{
	t_list	*node;

	if (g_hold)
		g_lst = g_lst->next;
	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	g_len = 0;
	if (g_lst)
	{
		while (g_lst->content[g_len] != '\0')
			g_len++;
	}
	g_buffer = 0;
	while (line[g_buffer] != '\n' && line[g_buffer] != '\0')
		g_buffer++;
	g_buffer++;
	node->content = glue(line);
	g_lst = node;
	g_buffer = 0;
	while (line[g_buffer] != '\n' && line[g_buffer] != '\0')
		g_buffer++;
	if (line[g_buffer] == '\n')
		next_node(line);
	else
		g_hold = NULL;
	return (node);
}

static char	*creating_list(char *fd)
{
	char	*tmp;

	tmp = fd;
	if (!g_lst)
		g_lst = NULL;
	if (g_buffer < BUFFER_SIZE && !g_lst)
	{
		tmp = (char *)malloc((g_buffer + 1) * sizeof(char));
		if (tmp == NULL)
			return (NULL);
		g_len = 0;
		while (g_buffer--)
		{
			tmp[g_len] = fd[g_len];
			g_len++;
		}
		tmp[g_len] = '\0';
		free(fd);
		return (tmp);
	}
	fd[g_buffer] = '\0';
	nodes(tmp);
	free(fd);
	return (g_lst->content);
}

char	*get_next_line(int fd)
{
	g_buffer = 1;
	while (g_buffer)
	{
		g_len = BUFFER_SIZE;
		g_yank = (char *)malloc((g_len + 1) * sizeof(char));
		if (g_yank == NULL)
			return (NULL);
		g_buffer = read(fd, g_yank, g_len);
		if (g_buffer == 0)
			break ;
		else if (g_buffer < BUFFER_SIZE && !g_lst)
			return (creating_list(g_yank));
		creating_list(g_yank);
		g_len = 0;
		while (g_lst->content[g_len])
		{
			g_len++;
			if (g_lst->content[g_len] == '\n')
				return (g_lst->content);
		}
	}
	free(g_lst);
	free(g_hold);
	free(g_yank);
	return (NULL);
}

#include <fcntl.h>
#include <stdio.h>
int main(void)
{
	int     fd;
	int     i;
	char    *str;

	fd = open("text.txt", O_RDONLY);
	i = 4;
	while (i--)
	{
		str = get_next_line(fd);
		printf("%s", str);
		if (str != NULL)
		{
			free(str);
			str = NULL;
		}
	}
	close(fd);
	return (0);
}
