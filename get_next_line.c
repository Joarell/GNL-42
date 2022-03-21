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

	if (g_lst)
		g_aux = g_hold->content;
	complete = (char *)malloc((g_len + g_buffer + 1) * sizeof(char));
	if (complete == NULL)
		return (NULL);
	g_buffer = 0;
	while (g_aux)
	{
		complete[g_buffer] = g_aux[g_buffer];
		g_buffer++;
	}
	if (g_lst)
		free(g_hold);
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

static char	*nodes(char *line)
{
	if (g_lst && g_lst->next)
		g_lst = g_lst->next;
	g_len = 0;
	g_hold = (t_list *)malloc(sizeof(t_list));
	if (g_hold == NULL)
		return (NULL);
	if (g_lst)
		g_lst->next = g_hold;
	if (!g_lst)
		g_hold->content = glue(line);
	else
	{
		while (g_lst->content[g_len] != '\0')
			g_len++;
		while (line[g_buffer] != '\0')
			g_buffer++;
		g_hold->content = glue(line);
	}
	g_hold->next = NULL;
	g_hold->back = NULL;
	if (g_lst)
		g_hold->back = g_lst;
	g_lst = g_hold;
	g_len = 0;
	return (g_lst->content);
}

static t_list	*next_node(char *fd)
{
	nodes(fd);
	while (fd[g_len] != '\n')
		g_len++;
	g_buffer = g_len;
	g_len = BUFFER_SIZE - (g_len + 1);
	g_aux = (char *)malloc((g_len + 1) * sizeof(char));
	if (g_aux == NULL)
		return (NULL);
	g_len = g_buffer + 1;
	g_buffer = 0;
	while (fd[g_len] != '\0')
	{
		g_aux[g_buffer] = fd[g_len];
		g_buffer++;
		g_len++;
	}
	g_aux[g_buffer] = '\0';
	g_hold = (t_list *)malloc(sizeof(t_list));
	if (g_hold == NULL)
		return (NULL);
	g_hold->content = g_aux;
	g_hold->next = NULL;
	g_lst->next = g_hold;
	return (g_lst);
}

static t_list	*creating_list(char *fd)
{
	if (!g_lst || !g_buffer)
		g_lst = NULL;
	if (!g_buffer)
	{
		free(fd);
		return (NULL);
	}
	fd[g_buffer] = '\0';
	g_buffer = 0;
	while (fd[g_buffer] != '\0')
	{
		if (fd[g_buffer] != '\n')
			g_buffer++;
		if (fd[g_buffer] == '\n')
			nodes(fd);
		while (fd[g_buffer] != '\0')
		{
			if (fd[g_buffer] != '\n')
				next_node(fd);
			g_buffer++;
		}
	}
	return (g_lst);
}

char	*get_next_line(int fd)
{
	char	*yank;

	g_buffer = 1;
	while (g_buffer)
	{
		g_len = BUFFER_SIZE;
		yank = (char *)malloc((g_len + 1) * sizeof(char));
		if (yank == NULL)
			return (NULL);
		g_buffer = read(fd, yank, g_len);
		creating_list(yank);
		if (!g_lst)
			return (NULL);
		g_len = 0;
		while (g_lst->content[g_len])
		{
			g_len++;
			if (g_lst->content[g_len] == '\n')
				return (g_lst->content);
			}
	}
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
	i = 3;
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
