/* ************************************************************************** */
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
char			*g_aux;
t_list			*g_hold;

static char	*glue(char *fd)
{
	char	*complete;
	char	*tmp;

	tmp = g_lst->content;
	while (tmp[g_len] != '\0')
		g_len++;
	g_buffer = BUFFER_SIZE;
	complete = (char *)malloc((g_len + g_buffer) * sizeof(char) + 1);
	if (complete == NULL)
		return (NULL);
	g_buffer = 0;
	while (g_len--)
	{
		complete[g_buffer] = tmp[g_buffer];
		g_buffer++;
	}
	g_len++;
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

static t_list	*nodes(char *line)
{
	g_len = 0;
	while (line[g_len] != '\0')
	{
		if (g_lst && g_lst->next)
		{
			free (g_lst->content);
			g_lst = g_lst->next;
		}
		g_len++;
	}
	g_len = 0;
	g_hold = (t_list *)malloc(sizeof(t_list));
	if (g_hold == NULL)
		return (NULL);
	if (g_lst == NULL)
		g_hold->content = line;
	else
		g_hold->content = glue(line);
	g_hold->next = NULL;
	g_lst = g_hold;
	return (g_lst);
}

static t_list	*next_node(char *fd)
{
	int	i;

	nodes(fd);
	i = 0;
	g_len = BUFFER_SIZE;
	g_aux = (char *)malloc(g_len * sizeof(char *));
	if (g_aux == NULL)
		return (NULL);
	g_buffer = 0;
	while (fd[g_buffer] != '\0')
	{
		if (fd[g_buffer - i] == '\n')
		{
			g_aux[i] = fd[g_buffer + 1];
			i++;
		}
		g_buffer++;
	}
	g_hold = (t_list *)malloc(1 * sizeof(t_list));
	if (g_hold == NULL)
		return (NULL);
	g_hold->content = g_aux;
	g_hold->next = NULL;
	g_lst->next = g_hold;
	return (g_lst);
}

static t_list	*creating_list(char *fd)
{
	if (!g_lst)
		g_lst = NULL;
	if (!fd || !g_buffer)
		return (NULL);
	g_len = BUFFER_SIZE;
	g_aux = (char *)malloc(g_len * sizeof(char) + 1);
	if (g_aux == NULL)
		return (NULL);
	g_buffer = 0;
	fd[g_len] = '\0';
	while (g_len--)
	{
		if (fd[g_buffer] != '\n')
		{
			g_aux[g_buffer] = fd[g_buffer];
			g_buffer++;
		}
		else
			return (next_node(fd));
	}
	g_aux[g_buffer] = '\0';
	nodes(g_aux);
	free(fd);
	return (g_lst);
}

char	*get_next_line(int fd)
{
	char	*yank;

	g_buffer = 1;
	while (g_buffer)
	{
		yank = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
		if (yank == NULL)
			return (NULL);
		g_buffer = read(fd, yank, BUFFER_SIZE);
		if (!g_buffer)
			break ;
		creating_list(yank);
		g_len = 0;
		while (g_lst->content[g_len] != '\0')
		{
			g_len++;
			if (g_lst->content[g_len] == '\n')
				return (g_lst->content);
		}
	}
	free(yank);
	return (NULL);
}

#include <fcntl.h>
#include <stdio.h>
int main(void)
{
	int fd;
	int i;

	fd = open("text.txt", O_RDONLY);
	i = 6;
	while (i--)
	{
		printf("%s", get_next_line(fd));
	}
	free(get_next_line(fd));
	close(fd);
	return (0);
}
