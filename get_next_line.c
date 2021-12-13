/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza-c <jsouza-c@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:25:20 by jsouza-c          #+#    #+#             */
/*   Updated: 2021/12/12 22:59:41 by jsouza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*g_lst;
int				g_buffer;
int				g_len;
char			*g_aux;

/* static	char	*move_and_creat(char const *fd) */
/* { */
/*  */
/* } */

static	char	*glue(char *fd)
{
	char	*complete;

	g_len = 0;
	g_aux = g_lst->content;
	while (g_aux[g_len] != '\0')
		g_len++;
	complete = (char *)malloc((g_len + g_buffer) * sizeof(char) + 1);
	if (complete == NULL)
		return (NULL);
	g_len = 0;
	while (g_aux[g_len] != '\0')
	{
		complete[g_len] = g_aux[g_len];
		g_len++;
	}
	g_buffer = 0;
	free(g_lst->content);
	while (fd[g_buffer] != '\0')
	{
		complete[g_len] = fd[g_buffer];
		g_len++;
		g_buffer++;
	}
	complete[g_len] = '\0';
	return (complete);
}

static	t_list	*nodes(char *line)
{
	t_list	*new_line;

	new_line = NULL;
	new_line = (t_list *)malloc(sizeof(t_list));
	if (new_line == NULL)
		return (NULL);
	if (g_lst == NULL)
	{
		new_line->content = line;
		g_lst = new_line;
	}
	else
		new_line->content = glue(line);
	new_line->next = NULL;
	g_lst = new_line;
	return (g_lst);
}

static	char	*creating_list(char *fd)
{
	int	w;

	g_buffer = BUFFER_SIZE;
	if (!g_lst)
		g_lst = NULL;
	if (!fd || !g_buffer)
		return (NULL);
	while (fd[g_len] != '\n' && g_len <= BUFFER_SIZE && fd[g_len] != '\0')
		g_len++;
	g_len++;
	g_aux = (char *)malloc(g_len * sizeof(char) + 1);
	if (g_aux == NULL)
		return (NULL);
	w = 0;
	while (g_len--)
	{
		g_aux[w] = fd[w];
		w++;
	}
	g_aux[w] = '\0';
	nodes(g_aux);
	free(fd);
	return (g_lst->content);
}

char	*get_next_line(int fd)
{
	char	*yank;

	yank = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (yank == NULL)
		return (NULL);
	g_buffer = read(fd, yank, BUFFER_SIZE);
	if (*yank && g_buffer > 0)
	{
		while (g_buffer)
		{
			creating_list(yank);
			g_buffer = read(fd, yank, BUFFER_SIZE);
			g_len = 0;
			while (g_lst->content[g_len] != '\0')
			{
				g_len++;
				if (g_lst->content[g_len] == '\n')
					return (g_lst->content);
			}
		}
	}
	else
		free(yank);
	return (NULL);
}

#include <stdio.h>
#include <fcntl.h>
int main (void)
{
	int		fd;
	int		i;

	/* fd = open("./gnlTester/files/empty", O_RDONLY); */
	fd = open("text.txt", O_RDONLY);
	i = 6;
	while(i--)
	{
		printf("%s", get_next_line(fd));
	}
	free(get_next_line(fd));
	close(fd);
	return (0);
}
