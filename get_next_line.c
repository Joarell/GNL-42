/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jev <jsouza-c@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 23:28:57 by Jev               #+#    #+#             */
/*   Updated: 2021/11/28 21:12:28 by Jev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>

static	char	*move_and_creat(char const *fd)
{
	int		w;
	size_t	i;
	char	*line;

	i = 0;
	w = 0;
	while (fd[i] != '\n' && i <= BUFFER_SIZE)
	{
		i++;
	}
	i++;
	line = (char *)malloc(i * sizeof(char));
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

static	t_list	*nodes(t_list **lst, void *line)
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
		return (*lst = new_line);
	}
	while (aux->next)
	{
		aux = aux->next;
	}
	aux->next = new_line;
	return (aux);
}

static	t_list	*creating_list(char *fd)
{
	static t_list	*lst;
	char			*new;
	size_t			buffer;

	if (!lst)
	{
		buffer = BUFFER_SIZE;
		lst = NULL;
		if (!fd || !buffer)
			return (NULL);
		while (buffer)
		{
			new = move_and_creat(fd);
			nodes(&lst, new);
			buffer -= len_fd(new);
			fd += len_fd(new);
			if (!*fd)
				break ;
		}
		return (lst->content);
	}
	free(fd);
	free(lst->content);
	lst = lst->next;
	return (lst->content);
}

char	*get_next_line(int fd)
{
	char	*file;
	if (BUFFER_SIZE)
	{
		file = (char *)malloc(BUFFER_SIZE * sizeof(char));
		if (file == NULL)
			return (NULL);
		read(fd, file, BUFFER_SIZE);
		return ((char *)creating_list(file));
	}
	return (NULL);
}

#include <stdio.h>
#include <fcntl.h>
int main (void)
{
	int		fd;
	int		i;

	fd = open("text.txt", O_RDONLY);
	i = 6;
	while(i--)
	{
		printf("%s", get_next_line(fd));
	}
	close(fd);
	return (0);
}
