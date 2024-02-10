/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:36:56 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/10 12:04:21 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# include <stddef.h>

typedef struct s_str
{
	char	*data;
	size_t	len;
	size_t	size;
}	t_str;

char	*get_next_line(int fd);

void	ft_strlcpy(char dest[], char const src[], size_t size);
char	*ft_strchr(char str[], char c);

#endif
