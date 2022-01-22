/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:10:43 by hhouda            #+#    #+#             */
/*   Updated: 2022/01/22 16:44:20 by hhouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_line(char *s)
{
	size_t		i;
	char		*line;

	i = 0;
	if (s[i] == 0)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*get_remainder(char *s)
{
	int		i;
	int		j;
	char	*remainder;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == 0)
	{
		free (s);
		return (NULL);
	}
	remainder = (char *) malloc(sizeof(char) * ((ft_strlen(s) - i) + 1));
	if (!remainder)
		return (NULL);
	i++;
	j = 0;
	while (s[i])
		remainder[j++] = s[i++];
	remainder[j] = '\0';
	free (s);
	return (remainder);
}

static char	*free_and_null(char *s)
{
	if (s)
		free(s);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*content[FD_SETSIZE];
	int			ret;

	if (fd == -1 || BUFFER_SIZE <= 0 || fd > FD_SETSIZE)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	ret = 42;
	while (!ft_strchr(content[fd], '\n') && ret != 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
			return (free_and_null(buffer));
		buffer[ret] = '\0';
		content[fd] = ft_strjoin(content[fd], buffer);
	}
	free(buffer);
	line = get_line(content[fd]);
	content[fd] = get_remainder(content[fd]);
	return (line);
}
