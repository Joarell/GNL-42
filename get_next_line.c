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

static t_list	*nodes(char *line)
{
	t_list	*node;

	g_len = 0;
	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	if (!g_lst)
		node->content = glue(line);
	else
	{
		while (g_lst->content[g_len] != '\0')
			g_len++;
		while (line[g_buffer] != '\0')
			g_buffer++;
		node->content = glue(line);
	}
	node->next = NULL;
	node->back = NULL;
	g_len = 0;
	return (node);
}

static void	next_node(char *fd)
{
	t_list	*cargo;

	cargo = NULL;
	if (!fd)
		return ;
	if (!g_lst)
		g_lst = nodes(fd);
	else
	{
		if (!g_hold)
			g_hold = g_lst;
		cargo = nodes(fd);
		g_hold->next = cargo;
		if (!g_lst->back)
			g_hold->back = g_lst;
		else
			g_hold->back = g_hold;
		g_hold = g_hold->next;
	}
	g_lst->back = g_lst;
    while (*fd != '\n')
		fd++;
	fd++;
	return (next_node(fd));
	/* nodes(fd); */
    /* fd += g_buffer; */
	/* while (fd[g_len] != '\n') */
	/* 	g_len++; */
	/* g_aux = (char *)malloc((g_len + 1) * sizeof(char)); */
	/* if (g_aux == NULL) */
	/* 	return (NULL); */
	/* g_len = 0; */
	/* while (fd[g_len] != '\0') */
	/* { */
    /*     g_aux[g_len] = fd[g_len]; */
    /*     if (fd[g_len] == '\n') */
    /*         break ; */
	/* 	g_len++; */
	/* } */
	/* g_aux[g_buffer] = '\0'; */
	/* g_hold = (t_list *)malloc(sizeof(t_list)); */
	/* if (g_hold == NULL) */
	/* 	return (NULL); */
	/* g_hold->content = g_aux; */
	/* g_hold->next = NULL; */
	/* g_lst->next = g_hold; */
	/* return (g_lst); */
}

static t_list	*creating_list(char *fd)
{
    /* int     count; */
    char    *tmp;

    tmp = fd;
    /* count = 0; */
	if (!g_lst || !g_buffer)
		g_lst = NULL;
	fd[g_buffer] = '\0';
    g_buffer = 0;
	next_node(tmp);
	/* while (*tmp != '\0') */
	/* { */
	/* 	if (tmp[g_buffer] == '\n') */
	/* 	{ */
    /*         count = g_buffer; */
    /*         count++; */
	/* 		next_node(tmp); */
    /*         g_buffer = count + g_len; */
	/* 	} */
	/* 	g_buffer++; */
	/* } */
    free(fd);
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
