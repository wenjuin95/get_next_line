/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:38:28 by welow             #+#    #+#             */
/*   Updated: 2023/11/10 17:52:43 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin_free(char *line, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(line, buffer);
	free(line);
	return (tmp);
}

char	*create_line(int fd, char *line)
{
	char	*buffer;
	int		read_byte;

	if (!line)
	{
		line = malloc(1);
		line[0] = '\0';
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_byte = 1;
	while (!ft_strchr(line, '\n') && read_byte > 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_byte] = '\0';
		line = ft_strjoin_free(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*get_only_next_line(char *line)
{
	int		i;
	char	*line_with_nl;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line [i] != '\n')
		i++;
	line_with_nl = ft_substr(line, 0, i + 1);
	if (!line_with_nl)
	{
		free(line_with_nl);
		return (NULL);
	}
	return (line_with_nl);
}

char	*new_line(char *line)
{
	char	*start_line;
	char	*str;

	start_line = ft_strchr(line, '\n');
	if (!start_line)
	{
		free(line);
		return (NULL);
	}
	str = ft_substr(start_line + 1, 0, ft_strlen(start_line + 1));
	free(line);
	if (!str)
	{
		return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line[fd] = create_line(fd, line[fd]);
	if (line[fd] == NULL)
		return (NULL);
	next_line = get_only_next_line(line[fd]);
	line[fd] = new_line(line[fd]);
	return (next_line);
}

#include <stdio.h>
int	main(void)
{
	int	fd1;
	int fd2;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	printf("%d| %s", fd1, get_next_line(fd1));
	printf("%d| %s", fd2,  get_next_line(fd2));
	printf("%d| %s", fd1, get_next_line(fd1));
	printf("%d| %s", fd2,  get_next_line(fd2));
	printf("%d| %s", fd1, get_next_line(fd1));
	printf("%d| %s", fd2,  get_next_line(fd2));
	printf("%d| %s", fd1, get_next_line(fd1));
	printf("%d| %s", fd2,  get_next_line(fd2));

	close(fd1);
	close(fd2);
	return (0);
} 