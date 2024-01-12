/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:59:48 by pnguyen-          #+#    #+#             */
/*   Updated: 2023/11/23 18:31:31 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	isendl(char const s[], int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (s[i] == '\n' || s[i] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

void	my_strlcpy(char dest[], char const src[], int size)
{
	int	i;

	i = 0;
	while (i + 1 < size && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	my_strlcat(char dest[], char const src[], int size)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	if (i >= size)
		return ;
	j = 0;
	while (j + i + 1 < size)
	{
		dest[j + i] = src[j];
		j++;
	}
	dest[i + j] = '\0';
}

int	my_strlen(char const str[])
{
	char const	*start;

	start = str;
	while (*str)
		str++;
	return (str - start);
}
