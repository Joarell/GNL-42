/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jev <jsouza-c@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 23:28:57 by Jev               #+#    #+#             */
/*   Updated: 2021/11/20 21:14:09 by Jev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*lines;

	return (0);
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
