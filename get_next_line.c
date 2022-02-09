/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:jsouza-c <jsouza-c@student.42sp.org.br      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:25:20 by jsouza-c          #+#    #+#             */
/*   Updated: 2022/02/08 22:52:43 by jsouza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*g_lst;
int				g_buffer;
int				g_len;
char			*g_aux;
t_list			*g_new_line;

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
	while (fd[g_buffer - 1] != '\n' && fd[g_buffer] != '\0')
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
	g_len = 0;
	while (g_lst && g_aux[g_len] != '\0')
	{
		if (g_aux[g_len] == '\n')
		{
			free(g_lst->content);
			g_lst = g_lst->next;
		}
		/* else if (g_lst->content[g_len] == '\0') */
		/* 	break ; */
		g_len++;
	}
	g_new_line = (t_list *)malloc(sizeof(t_list));
	if (g_new_line == NULL)
		return (NULL);
	if (g_lst == NULL)
	{
		g_new_line->content = line;
		g_lst = g_new_line;
	}
	else
		g_new_line->content = glue(line);
	g_new_line->next = NULL;
	g_lst = g_new_line;
	return (g_lst);
}

static	t_list	*next_node(char *fd)
{
	t_list	*hold;

	g_buffer = 0;
	g_len = BUFFER_SIZE;
	g_aux = (char *)malloc(g_len * sizeof(char *) + 1);
	if (g_aux == NULL)
		return (NULL);
	g_buffer = 0;
	while (g_len--)
	{
		if (g_aux[g_buffer - 1] == '\n')
			nodes(g_aux);
		g_aux[g_buffer] = fd[g_buffer];
		g_aux[g_buffer + 1] = '\0';
		g_buffer++;
	}
	g_aux[g_buffer] = '\0';
	hold = (t_list *)malloc(1 * sizeof(t_list));
	if (hold == NULL)
		return (NULL);
	hold->content = g_aux;
	hold->next = NULL;
	g_lst->next = hold;
	return (g_lst);
}

static	char	*creating_list(char *fd)
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
		if (fd[g_buffer - 1] != '\n')
		{
			g_aux[g_buffer] = fd[g_buffer];
			g_buffer++;
		}
		else
			next_node(fd);
	}
	g_aux[g_buffer] = '\0';
	nodes(g_aux);
	free(fd);
	return (g_lst->content);
}

char	*get_next_line(int fd)
{
	char	*yank;

	yank = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (yank == NULL)
		return (NULL);
	g_buffer = 1;
	while (g_buffer)
	{
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
