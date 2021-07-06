/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhumfrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 20:23:31 by mhumfrey          #+#    #+#             */
/*   Updated: 2020/11/18 20:36:08 by mhumfrey         ###   ########.fr       */
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

char	*rmr_checker(char *rmr, char **line)
{
	char *pn;

	pn = NULL;
	if (rmr)
		if ((pn = ft_strchr(rmr, '\n')))
		{
			*pn = '\0';
			*line = ft_strdup(rmr);
			ft_strcpy(rmr, ++pn);
		}
		else
		{
			*line = ft_strdup(rmr);
			if (rmr)
				while (*rmr)
					*rmr++ = '\0';
		}
	else
		*line = ft_strnew(1);
	return (pn);
}

int		get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			bwr;
	char		*pn;
	static char	*rmr;
	char		*temp;

	pn = rmr_checker(rmr, line);
	while (!pn && (bwr = read(fd, buf, BUFFER_SIZE)))
	{
		buf[bwr] = '\0';
		if ((pn = ft_strchr(buf, '\n')))
		{
			*pn = '\0';
			temp = rmr;
			rmr = ft_strdup(++pn);
			free(temp);
		}
		temp = *line;
		*line = ft_strjoin(*line, buf);
		free(temp);
	}
	return (bwr || ft_strlen(*line) || ft_strlen(rmr)) ? 1 : 0;
}
