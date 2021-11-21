/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jev <jsouza-c@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 21:13:17 by Jev               #+#    #+#             */
/*   Updated: 2021/11/20 21:13:22 by Jev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE
# define OPEN_MAX 256
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#	define BUFFER_SIZE 1
# endif
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
char	*get_next_line(int fd);

#endif
