/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:36:32 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/03 05:04:26 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 64
#endif

#if BUFFER_SIZE < 0
# undef BUFFER_SIZE
# define BUFFER_SIZE 0
#endif

typedef struct s_str
{
	char	*data;
	size_t	len;
	size_t	size;
}	t_str;

static int		gnl_absorb_buffer(t_str *str, char buffer[BUFFER_SIZE]);
static ssize_t	gnl_read(t_str *str, int const fd, char buffer[BUFFER_SIZE]);
static char		*gnl_str_realloc(char src[], size_t const len, size_t const size);
static void		ft_strlcpy(char dest[], char const src[], size_t size);
static char		*ft_strchr(char const str[], char const c);

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);

	t_str		line;
	line.size = BUFFER_SIZE + 1;
	line.data = malloc(line.size * sizeof(char));
	if (line.data == NULL)
		return (NULL);
	if (gnl_absorb_buffer(&line, buffer))
		return (line.data);
	ssize_t const	bytes = gnl_read(&line, fd, buffer);
	if (bytes == -1 || line.len == 0)
	{
		free(line.data);
		return (NULL);
	}
	return (gnl_str_realloc(line.data, line.len, line.len + 1));
}

static int	gnl_absorb_buffer(t_str *str, char buffer[BUFFER_SIZE])
{
	char	*stash = ft_strchr(buffer, '\n');
	if (stash == NULL)
	{
		str->len = ft_strchr(buffer, '\0') - buffer;
		ft_strlcpy(str->data, buffer, str->len + 1);
		buffer[0] = '\0';
		return (0);
	}
	else
	{
		str->len = ++stash - buffer;
		ft_strlcpy(str->data, buffer, str->len + 1);
		ft_strlcpy(buffer, stash, BUFFER_SIZE);
		str->data = gnl_str_realloc(str->data, str->len, str->len + 1);
		return (1);
	}
}

static ssize_t	gnl_read(t_str *str, int const fd, char buffer[BUFFER_SIZE])
{
	ssize_t	bytes = -1;
	char	*stash = NULL;
	while (stash == NULL)
	{
		if (str->size <= str->len + BUFFER_SIZE)
		{
			str->size *= 2;
			str->data = gnl_str_realloc(str->data, str->len, str->size);
		}
		if (str->data == NULL)
			return (-1);
		bytes = read(fd, str->data + str->len, BUFFER_SIZE);
		if (bytes <= 0)
			return (bytes);
		str->data[str->len + bytes] = '\0';
		stash = ft_strchr(str->data + str->len, '\n');
		str->len += bytes;
	}
	str->len = ++stash - str->data;
	ft_strlcpy(buffer, stash, BUFFER_SIZE);
	return (bytes);
}

static char	*gnl_str_realloc(char src[], size_t const len, size_t const size)
{
	char	*new_str = malloc(size * sizeof(char));
	if (new_str != NULL)
		ft_strlcpy(new_str, src, len + 1);
	free(src);
	return (new_str);
}

static void	ft_strlcpy(char dest[], char const src[], size_t size)
{
	if (size == 0)
		return ;
	while (--size != 0 && *src != '\0')
		*(dest++) = *(src++);
	*dest = '\0';
}

static char	*ft_strchr(char const str[], char const c)
{
	while (*str != c)
	{
		if (*str == '\0')
			return (0);
		++str;
	}
	return ((char *)str);
}
