/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:59:48 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/01/27 20:41:59 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//int	isendl(char const s[], int n)
//{
//	int	i;
//
//	i = 0;
//	while (i < n)
//	{
//		if (s[i] == '\n' || s[i] == '\0')
//			return (i);
//		i++;
//	}
//	return (-1);
//}

void	ft_strlcpy(char dest[], char const src[], size_t size)
{
	size_t	i;

	i = 0;
	while (i++ + 1 < size && *src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}

char	*ft_strchr(char str[], char c)
{
	while (*str != c)
	{
		if (*str == '\0')
			return (0);
		str++;
	}
	return (str);
}

//void	my_strlcat(char dest[], char const src[], int start, int size)
//{
//	int	i;
//
//	if (start >= size)
//		return ;
//	i = 0;
//	while (i + start + 1 < size)
//	{
//		dest[start + i] = src[i];
//		i++;
//	}
//	dest[start + i] = '\0';
//}

//int	my_strlen(char const str[])
//{
//	char const	*start;
//
//	start = str;
//	while (*str)
//		str++;
//	return (str - start);
//}
//
