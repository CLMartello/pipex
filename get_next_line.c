/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:37:35 by clumertz          #+#    #+#             */
/*   Updated: 2025/08/22 13:09:06 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i] != '\0')
	{
		if (str[i] == '\n')
			return (++i);
		i++;
	}
	return (i);
}

static int	new_line(char *line)
{
	if (!line)
		return (0);
	while (*line)
	{
		if (*line == '\n')
			return (1);
		line++;
	}
	return (0);
}

static char	*gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	if (!s1 && s2[0] == '\0')
		return (free(s1), NULL);
	result = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!result)
		return (free(s1), NULL);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	free(s1);
	j = 0;
	while (s2 && j < gnl_strlen(s2))
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

static void	ft_movbuf(char *buffer)
{
	int	i;
	int	size;

	i = 0;
	size = gnl_strlen(buffer);
	while (buffer[size] != '\0')
	{
		buffer[i] = buffer[size];
		i++;
		size++;
	}
	while (i < BUFFER_SIZE +1)
	{
		buffer[i] = '\0';
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*next;
	ssize_t		bytes_read;

	next = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (new_line(next) == 0)
	{
		if (buffer[0] == '\0')
			bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (buffer[0] == '\0' && bytes_read == -1)
			return (free(next), NULL);
		if (buffer[0] == '\0' && bytes_read == 0)
			return (next);
		next = gnl_strjoin(next, buffer);
		if (!next)
			return (NULL);
		ft_movbuf(buffer);
	}
	return (next);
}
