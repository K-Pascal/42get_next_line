/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:36:32 by pnguyen-          #+#    #+#             */
/*   Updated: 2023/11/23 20:28:44 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "get_next_line.h"

static char	*absorb_buffer(char *buffer, int size, int *len)
{
	char	*line;
	int		pos;
	int		isnl;

	if (buffer[0] == '\0')
		return (NULL);
	pos = isendl(buffer, size);
	isnl = buffer[pos] == '\n';
	line = malloc((pos + 1 + isnl) * sizeof(char));
	if (line == NULL)
		return (NULL);
	if (pos != -1)
	{
		*len = pos + isnl;
		my_strlcpy(line, buffer, *len + 1);
		my_strlcpy(buffer, buffer + pos + isnl, size - pos);
	}
	else
	{
		*len = my_strlen(buffer);
		my_strlcpy(line, buffer, *len + 1);
		buffer[0] = '\0';
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	static ssize_t	bytes;
	char			*line;
	char			*temp;
	int				len;
	int				i;
	int				isnl;

	if (fd < 0)
		return (NULL);
	len = 0;
	line = absorb_buffer(buffer, BUFFER_SIZE + 1, &len);
	if (line != NULL && buffer[0] != '\0')
		return (line);
	bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		i = isendl(buffer, bytes);
		if (bytes < BUFFER_SIZE)
		{
			if (i == -1)
			{
				temp = malloc((len + bytes + 1) * sizeof(char));
				if (temp == NULL)
				{
					free(line);
					return (NULL);
				}
				my_strlcpy(temp, line, len + 1);
				free(line);
				line = temp;
				len += bytes;
				my_strlcat(line, buffer, len - bytes, len + 1);
				buffer[0] = '\0';
			}
			else
			{
				isnl = buffer[i] == '\n';
				temp = malloc((len + i + 1 + isnl) * sizeof(char));
				if (temp == NULL)
				{
					free(line);
					return (NULL);
				}
				my_strlcpy(temp, line, len + 1);
				free(line);
				line = temp;
				len += i + isnl;
				my_strlcat(line, buffer, len - (i + isnl), len + 1);
				my_strlcpy(buffer, buffer + i + 1, BUFFER_SIZE - i);
				buffer[BUFFER_SIZE - i] = '\0';
			}
			break ;
		}
		else
		{
			if (i == -1)
			{
				temp = malloc((len + bytes + 1) * sizeof(char));
				if (temp == NULL)
				{
					free(line);
					return (NULL);
				}
				my_strlcpy(temp, line, len + 1);
				free(line);
				line = temp;
				len += bytes;
				my_strlcat(line, buffer, len - bytes, len + 1);
				buffer[0] = '\0';
			}
			else
			{
				isnl = buffer[i] == '\n';
				temp = malloc((len + i + 1 + isnl) * sizeof(char));
				if (temp == NULL)
				{
					free(line);
					return (NULL);
				}
				my_strlcpy(temp, line, len + 1);
				free(line);
				line = temp;
				len += i + isnl;
				my_strlcat(line, buffer, len - (i + isnl), len + 1);
				my_strlcpy(buffer, buffer + i + 1, BUFFER_SIZE - i );
				buffer[BUFFER_SIZE - i] = '\0';
				break ;
			}
		}
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes <= 0 && len == 0)
		return (NULL);
	return (line);
}
