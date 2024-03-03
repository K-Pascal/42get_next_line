/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:59:48 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/03 04:37:07 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strlcpy(char dest[], char const src[], size_t size)
{
	if (size == 0)
		return ;
	while (--size != 0 && *src != '\0')
		*(dest++) = *(src++);
	*dest = '\0';
}

char	*ft_strchr(char str[], char c)
{
	while (*str != c)
	{
		if (*str == '\0')
			return (0);
		++str;
	}
	return (str);
}
