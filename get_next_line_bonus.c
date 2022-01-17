#include "get_next_line_bonus.h"
#define FD_MAX 257

char	*get_line(char *s)
{
	size_t	i;
	char	*line;

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

char	*get_remainder(char *s)
{
	int i;
	int j;
	char *remainder;

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
	{
		remainder[j] = s[i];
		j++;
		i++;
	}
	remainder[j] = '\0';
	free (s);
	return (remainder);
}

char *get_next_line(int fd)
{
	char *buffer;
	char *line;
	static char *content[FD_MAX];
	int ret;

	if (fd == -1 || BUFFER_SIZE <= 0 || fd > FD_MAX)
		return(NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	ret = 42;
	while (!ft_strchr(content[fd], '\n') && ret != 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[ret] = '\0';
		content[fd] = ft_strjoin(content[fd], buffer);
	}
	free(buffer);
	line = get_line(content[fd]);
	content[fd] = get_remainder(content[fd]);
	return (line);
}
