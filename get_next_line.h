/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:36:56 by pnguyen-          #+#    #+#             */
/*   Updated: 2023/11/24 11:54:42 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifdef BUFFER_SIZE 
#  if BUFFER_SIZE < 0
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 0
#  endif
# else
#  define BUFFER_SIZE 43	
# endif

# include <stddef.h>

char	*get_next_line(int fd);

int		isendl(char const s[], int n);
void	my_strlcpy(char dest[], char const src[], int size);
void	my_strlcat(char dest[], char const src[], int start, int size);
int		my_strlen(char const str[]);

#endif
