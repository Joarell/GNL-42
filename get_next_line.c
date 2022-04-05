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
char			*g_yank;
t_list			*g_hold;

static char	*glue(char *fd)
{
	char	*complete;

	if (g_lst)
		g_yank = g_hold->content;
	complete = (char *)malloc((g_len + g_buffer + 1) * sizeof(char));
	if (complete == NULL)
		return (NULL);
	g_buffer = 0;
	while (g_yank)
	{
		complete[g_buffer] = g_yank[g_buffer];
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

static t_list	*nodes(char *line)
{
	t_list	*node;

	g_len = 0;
	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	if (g_lst)
	{
		while (g_lst->content[g_len] != '\0')
			g_len++;
	}
	g_buffer = 0;
	while (line[g_buffer] != '\n')
		g_buffer++;
	g_buffer++;
	node->content = glue(line);
	node->next = NULL;
	node->back = NULL;
	g_len = 0;
	return (node);
}

static t_list	*next_node(char *fd)
{
	if (!fd)
		return (NULL);
	if (!g_lst)
		return (g_lst = nodes(fd));
	else
	{
		if (!g_hold)
			g_hold = g_lst;
		g_hold->next = nodes(fd);
		if (!g_lst->back)
			g_hold->back = g_lst;
		else
			g_hold->back = g_hold;
		g_hold = g_hold->next;
	}
    while (*fd != '\n')
		fd++;
	fd++;
	return (next_node(fd));
}

static t_list	*creating_list(char *fd)
{
    char    *tmp;

    tmp = fd;
	if (!g_lst || !g_buffer)
		g_lst = NULL;
	fd[g_buffer] = '\0';
    g_buffer = 0;
	next_node(tmp);
    free(fd);
	return (g_lst);
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
		g_len = 0;
		while (g_yank[g_len] != '\0')
			g_len++;
		if (g_len <= BUFFER_SIZE)
			return (g_yank);
		creating_list(g_yank);
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
