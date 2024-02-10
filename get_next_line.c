/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:36:32 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/02/10 11:40:11 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "get_next_line.h"

//static char	gnl_absorb_buffer(t_line *line, char buffer[BUFFER_SIZE + 1]);
static void	*gnl_str_realloc(char *src, size_t len, size_t size);

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*save;
	ssize_t		bytes;
	t_line		line;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
//	if (gnl_absorb_buffer(&line, buffer))
//		return (line.content);
	bytes = 0;
	line.size = BUFFER_SIZE + 1;
	line.content = malloc(line.size * sizeof(char));
	if (line.content == NULL)
		return (NULL);
	ft_strlcpy(line.content, buffer, BUFFER_SIZE + 1);
	save = line.content;
	while (*save != '\0')
		save++;
	line.len = save - line.content;
	buffer[0] = '\0';
	save = ft_strchr(line.content, '\n');
	while (save == NULL)
	{
		if (line.size <= line.len + BUFFER_SIZE)
		{
			line.size *= 2;
			line.content = gnl_str_realloc(line.content, line.len, line.size);
		}
		if (line.content == NULL)
			return (NULL);
		bytes = read(fd, line.content + line.len, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		line.content[line.len + bytes] = '\0';
		save = ft_strchr(line.content + line.len, '\n');
		line.len += bytes;
	}
	if (save != NULL)
	{
		line.len = (save - line.content) + 1;
		ft_strlcpy(buffer, save + 1, BUFFER_SIZE);
	}
	if (bytes == -1 || line.len == 0)
	{
		free(line.content);
		return (NULL);
	}
	line.content = gnl_str_realloc(line.content, line.len, line.len + 1);
	return (line.content);
}

//static char	gnl_absorb_buffer(t_line *line, char buffer[BUFFER_SIZE + 1])
//{
//	char	*save;
//
//	line->len = 0;
//	line->size = BUFFER_SIZE + 1;
//	line->content = malloc(line->size * sizeof(char));
//	if (line->content == NULL)
//		return (1);
//	if (buffer[0] == '\0')
//		return (0);
//	save = buffer;
//	while (*save != '\0')
//		save++;
//	line->len = save - buffer;
//	save = ft_strchr(buffer, '\n');
//	if (save == NULL)
//	{
//		ft_strlcpy(line->content, buffer, line->len + 1);
//		buffer[0] = '\0';
//		return (0);
//	}
//	line->len = save - buffer + 1;
//	ft_strlcpy(line->content, buffer, line->len + 1);
//	ft_strlcpy(buffer, save + 1, BUFFER_SIZE + 1);
//	line->content = gnl_str_realloc(line->content, line->len, line->len + 1);
//	return (1);
//}

//char	*get_next_line(int fd)
//{
//	static char	buffer[BUFFER_SIZE + 1];
//	ssize_t		bytes;
//	t_line		line;
//	int			i;
//
//	if (fd < 0 || BUFFER_SIZE == 0)
//		return (NULL);
//	line.content = absorb_buffer(buffer, BUFFER_SIZE + 1, &line.len);
//	if (line.content != NULL && buffer[0] != '\0')
//		return (line.content);
//	line.size = line.len + 1;
//	bytes = read(fd, buffer, BUFFER_SIZE);
//	while (bytes > 0)
//	{
//		buffer[bytes] = '\0';
//		i = isendl(buffer, bytes);
//		if (append_line(&line, buffer, bytes, i) <= 0)
//			break ;
//		bytes = read(fd, buffer, BUFFER_SIZE);
//	}
//	if (bytes <= 0 && line.len == 0)
//		return (NULL);
//	line.content = my_alloccpy(&line, line.len + 1);
//	return (line.content);
//}

//static char	*absorb_buffer(char *buffer, int size, int *len)
//{
//	char	*line;
//	int		pos;
//	int		isnl;
//
//	*len = 0;
//	if (buffer[0] == '\0')
//		return (NULL);
//	pos = isendl(buffer, size);
//	isnl = buffer[pos] == '\n';
//	line = malloc((pos + 1 + isnl) * sizeof(char));
//	if (line == NULL)
//		return (NULL);
//	if (pos != -1)
//	{
//		*len = pos + isnl;
//		my_strlcpy(line, buffer, *len + 1);
//		my_strlcpy(buffer, buffer + pos + isnl, size - pos);
//	}
//	else
//	{
//		*len = my_strlen(buffer);
//		my_strlcpy(line, buffer, *len + 1);
//		buffer[0] = '\0';
//	}
//	return (line);
//}

//static int	append_line(t_line *line, char buffer[], int bytes, int i)
//{
//	int	isnl;
//
//	i = isendl(buffer, bytes);
//	if (i == -1)
//	{
//		my_realloc(line, line->len + bytes + 1);
//		if (line->content == NULL)
//			return (-1);
//		line->len += bytes;
//		my_strlcat(line->content, buffer, line->len - bytes, line->len + 1);
//		buffer[0] = '\0';
//		return (1);
//	}
//	else
//	{
//		isnl = buffer[i] == '\n';
//		my_realloc(line, line->len + i + isnl + 1);
//		if (line->content == NULL)
//			return (-1);
//		line->len += i + isnl;
//		my_strlcat(line->content, buffer, line->len - i - isnl, line->len + 1);
//		my_strlcpy(buffer, buffer + i + 1, BUFFER_SIZE - i);
//		buffer[BUFFER_SIZE - i] = '\0';
//		return (0);
//	}
//}

//static char	*my_realloc(char *line, int len, int *size, int new_size)
//{
//	while (*size < new_size)
//	{
//		*size *= 2;
//		if (*size < new_size)
//			continue ;
//		return (my_alloccpy(line, len, *size));
//	}
//	return (line);
//}
//

static void	*gnl_str_realloc(char *src, size_t len, size_t size)
{
	char	*new_str;

	new_str = malloc(size * sizeof(char));
	if (new_str != NULL)
		ft_strlcpy(new_str, src, len + 1);
	free(src);
	return (new_str);
}
