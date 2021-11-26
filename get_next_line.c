/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jev <jsouza-c@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 23:28:57 by Jev               #+#    #+#             */
/*   Updated: 2021/11/26 01:23:59 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Copiar a quantidade de bites mediante o BUFFER_SIZE.
 * Retornar a linha mediante o \n, encontrado
 * Caso não tenha nada para ser lido, retorne (NULL)
 * /home/coder/Jev/GNL-42/get_next_line.h
 */
#include "get_next_line.h"
#include <stddef.h>

static	char	*move_and_creat(char const *fd)
{
	int		j;
	size_t	i;
	char	*line;

	i = 0;
	j = 0;
	while (fd[i] != '\n' && i <= BUFFER_SIZE)
	{
		i++;
	}
	line = (char *)malloc(i * sizeof(char) + 1);
	if (line == NULL)
		return (NULL);
	while (--i)
	{
		line[j] = *fd;
		fd++;
		j++;
	}
	line[j] = '\0';
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

static	t_list	*lstadd_back(const char *fd)
{
	t_list	*lst;
	char	*new;
	size_t	buffer;
	t_list	*new_line;

	buffer = BUFFER_SIZE;
	lst = NULL;
	if (!fd || !buffer)
		return (NULL);
	while (buffer)
	{
		new = move_and_creat(fd);
		new_line = (t_list *)malloc(sizeof(t_list));
		if (new_line == NULL)
			return (NULL);
		new_line->content = new;
		new_line->next = NULL;
		lst = new_line;
		buffer -= len_fd(new);
	}
	return (lst);
}

char	*get_next_line(int fd)
{
	char	*file;
	
	file = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (file == NULL)
		return (NULL);
	read(fd, file, BUFFER_SIZE);
	lstadd_back(file);

	return (NULL);
}

#include <stdio.h>
#include <fcntl.h>
int main (void)
{
	int		fd;
	/* cap = (char *)malloc(sizeof(char) * BUFFER_SIZE); */
	/* if (cap == NULL) */
	/* 	NULL; */
	fd = open("text.txt", O_RDONLY);
	get_next_line(fd);
	close(fd);
	return (0);
}
