/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jev <jsouza-c@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 23:28:57 by Jev               #+#    #+#             */
/*   Updated: 2021/11/29 02:20:24 by Jev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*move_and_creat(char const *fd)
{
	int		w;
	size_t	i;
	char	*line;

	i = 0;
	w = 0;
	while (fd[i - 1] != '\n' && i <= BUFFER_SIZE && fd[i] != '\0')
	{
		i++;
	}
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

static	t_list	*nodes(t_list **lst, char *line)
{
	t_list	*new_line;
	t_list	*aux;

	aux = *lst;
	new_line = NULL;
	new_line = (t_list *)malloc(sizeof(t_list));
	if (new_line == NULL)
	{
		return (NULL);
	}
	*(char *)new_line->content = *line;
	new_line->next = NULL;
	if (*lst == NULL)
	{
		return (*lst = new_line);
	}
	while (aux->next)
		aux = aux->next;
	aux->next = new_line;
	return (aux);
}

static	t_list	*creating_list(char *fd)
{
	static t_list	*lst;
	size_t			buffer;

	if (!lst)
	{
		buffer = BUFFER_SIZE;
		lst = NULL;
		if (!fd || !buffer)
			return (NULL);
		while (buffer)
		{
			nodes(&lst, move_and_creat(fd));
			buffer -= len_fd(move_and_creat(fd));
			fd += len_fd(move_and_creat(fd));
			if (!*fd)
			{
				break ;
				free(fd);
			}
		}
		return (lst->content);
	}
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
		if (!(read(fd, file, BUFFER_SIZE)))
		{
			free(file);
			return (NULL);
		}
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

	/* fd = open("./gnlTester/files/empty", O_RDONLY); */
	fd = open("text.txt", O_RDONLY);
	i = 1;
	while(i--)
	{
		printf("%s", get_next_line(fd));
	}
	close(fd);
	return (0);
}
