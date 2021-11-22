/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jev <jsouza-c@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 23:28:57 by Jev               #+#    #+#             */
/*   Updated: 2021/11/21 23:52:55 by Jev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Copiar a quantidade de bites mediante o BUFFER_SIZE.
 * Retornar a linha mediante o \n, encontrado
 * Caso não tenha nada para ser lido, retorne (NULL)
 *
 */
#include "get_next_line.h"

static t_list	*new_line(int fd)
{
	t_list	*new_l;

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
	
	
	file = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (file == NULL)
		return (NULL);
	read(fd, file, BUFFER_SIZE);

	return (NULL);
}

#include <stdio.h>
#include <fcntl.h>
int main (void)
{
	int		fd;
	char	*cap;

	cap = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (cap == NULL)
		NULL;
	fd = open("text.txt", O_RDONLY);
	read(fd, cap, BUFFER_SIZE);
	printf("%s\n", cap);
	close(fd);
	return (0);
}
