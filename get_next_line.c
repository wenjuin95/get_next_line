/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:00:57 by welow             #+#    #+#             */
/*   Updated: 2025/04/19 21:55:23 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief join line with the buffer size given line
 * @param line line to be read
 * @param buffer buffer to be read
 * @return joined line and free the original line
*/
char	*ft_strjoin_free(char *line, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(line, buffer);
	free(line);
	return (tmp);
}

/**
 * @brief create line with the buffer size given
 * @param fd file descriptor from open file
 * @param line line to be read
 * @note 1. "read_byte" is set to 1 to prevent the loop stop
*/
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
	while (!ft_strchr(line, '\n') && read_byte != 0)
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

/**
 * @brief remove line after "\n" and return as "line with newline"
 * @param line line to be read
 * @return line with newline
*/
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

/**
 * @brief remove line before "\n" and return as "new line"
 * @param line line to be read
 * @return new line
 * @note 1. if found new line after "\n", copy the line to "str"
*/
char	*new_line(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	free(line);
	return (str);
}

/**
 * @brief read and return line from file descriptor
 * @param fd file descriptor from open file
 * @return line that read from file descriptor
 * @note 1. if no fd, fail buffer size, fail to read, return NULL
 * @note 2. after the "new_line" created, return the line to the "create_line" again
 *
*/
char	*get_next_line(int fd)
{
	static char	*line;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = create_line(fd, line);
	if (line == NULL)
		return (NULL);
	next_line = get_only_next_line(line);
	line = new_line(line);
	return (next_line);
}
