/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jev <jsouza-c@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 23:28:57 by Jev               #+#    #+#             */
/*   Updated: 2021/11/23 22:57:56 by Jev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Copiar a quantidade de bites mediante o BUFFER_SIZE.
 * Retornar a linha mediante o \n, encontrado
 * Caso não tenha nada para ser lido, retorne (NULL)
 *
 */
#include "get_next_line.h"

static	char	*move_n(char const *fd)
{
	int i;

	i = 0;
	while (fd[i] == '\n')
	{

	}
	return ((char *)fd);
}

static t_list	*new_line(char *fd)
{
	t_list	*new_l;
	
	if (!fd)
		return(NULL);
	while (BUFFER_SIZE)
	{
		
	}

	return (new_l);
}
static void	lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
}

char	*get_next_line(int fd)
{
	static	t_list	*lines;
	char	*file;
	
	lines = NULL;
	file = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (file == NULL)
		return (NULL);
	read(fd, file, BUFFER_SIZE);
	new_line(file);
	free(file);

	return (NULL);
}

#include <stdio.h>
#include <fcntl.h>
int main (void)
{
	int		fd;
	char	*cap;

	/* cap = (char *)malloc(sizeof(char) * BUFFER_SIZE); */
	/* if (cap == NULL) */
	/* 	NULL; */
	fd = open("text.txt", O_RDONLY);
	get_next_line(fd);
	printf("%s\n", cap);
	close(fd);
	return (0);
}
