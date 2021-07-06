/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhumfrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:51:01 by mhumfrey          #+#    #+#             */
/*   Updated: 2020/11/20 13:35:24 by mhumfrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ss;

	ss = (char *)s;
	while (*ss != c)
	{
		if (*ss == '\0')
			return (0);
		ss++;
	}
	return (ss);
}

char	*tail_checker(char *tail, char **line)
{
	char	*search_point;

	search_point = NULL;
	if (tail)
		if ((search_point = ft_strchr(tail, '\n')))
		{
			*search_point = '\0';
			*line = ft_strdup(tail);
			ft_strcpy(tail, ++search_point);
		}
		else
		{
			*line = ft_strdup(tail);
			if (tail)
				while (*tail)
					*tail++ = '\0';
		}
	else
		*line = ft_strnew(1);
	return (search_point);
}

int		get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*search_point;
	int			read_res;
	static char	*tail;
	char		*tempo;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	search_point = tail_checker(tail, line);
	while (!search_point && (read_res = read(fd, buffer, BUFFER_SIZE)))
	{
		if (read_res == -1)
			return (-1);
		buffer[read_res] = '\0';
		if ((search_point = ft_strchr(buffer, '\n')))
		{
			*search_point = '\0';
			tempo = tail;
			tail = ft_strdup(++search_point);
			free(tempo);
		}
		tempo = *line;
		*line = ft_strjoin(*line, buffer);
		free(tempo);
	}
	return (read_res || ft_strlen(tail)) ? 1 : 0;
}
