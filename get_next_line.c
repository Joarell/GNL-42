/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jev <jsouza-c@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 23:28:57 by Jev               #+#    #+#             */
/*   Updated: 2021/12/01 01:10:38 by Jev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*g_lst;

static	char	*move_and_creat(char const *fd)
{
	int		w;
	size_t	i;
	char	*line;

	i = 0;
	w = 0;
	line = NULL;
	while (fd[i] != '\n' && i <= BUFFER_SIZE && fd[i] != '\0')
	{
		i++;
	}
	i++;
	line = (char *)malloc(i * sizeof(char) + 1);
	if (line == NULL)
		return (NULL);
	while (i--)
	{
		line[w] = *fd;
		fd++;
		w++;
	}
	return (line);
}

static	size_t	len_fd(char *fd)
{
	int	len;

	len = 0;
	while (*fd != '\0')
	{
		fd++;
		len++;
	}
	return (len);
}

static	t_list	*nodes(t_list **lst, char *line)
{
	t_list	*new_line;
	t_list	*aux;

	aux = *lst;
	new_line = (t_list *)malloc(sizeof(t_list));
	if (new_line == NULL)
	{
		return (NULL);
	}
	new_line->content = line;
	new_line->next = NULL;
	if (*lst == NULL)
	{
		new_line->back = aux;
		return (*lst = new_line);
	}
	while (aux->next)
	{
		aux = aux->next;
	}
	new_line->back = aux;
	aux->next = new_line;
	return (aux);
}

static	char	*creating_list(char *fd)
{
	size_t		buffer;
	char		*new;
	char		*def;

	buffer = BUFFER_SIZE;
	g_lst = NULL;
	if (!fd || !buffer)
		return (NULL);
	def = fd;
	new = NULL;
	while (buffer && *fd != '\0')
	{
		new = move_and_creat(fd);
		nodes(&g_lst, new);
		buffer -= len_fd(new);
		fd += len_fd(new);
	}
	free(def);
	return (g_lst->content);
}

char	*get_next_line(int fd)
{
	char	*file;
	t_list	*erase;

	if (BUFFER_SIZE && !g_lst)
	{
		file = (char *)malloc(BUFFER_SIZE * sizeof(char));
		if (file == NULL)
			return (NULL);
		read(fd, file, BUFFER_SIZE);
		if (*file)
			return ((char *)creating_list(file));
		else
			free(file);
				return (NULL);
	}
	erase = NULL;
	if (g_lst->next != NULL)
	{
		g_lst = g_lst->next;
		erase = g_lst->back;
		free(erase->content);
		return (g_lst->content);
	}
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
