/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhumfrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:44:52 by mhumfrey          #+#    #+#             */
/*   Updated: 2020/11/17 17:50:56 by mhumfrey         ###   ########.fr       */
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

char	*check_rmr(char *rmr, char **line)
{
	char *pn;

	pn = NULL;
	if (rmr)
		if ((pn = ft_strchr(rmr, '\n')))
		{
			*pn = '\0';
			*line = ft_strdup(rmr);
			ft_strcpy(rmr, ++pn);
			free(line);
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

int		get_line(int fd, char **line, char **rmr)
{
	char		buf[BUFFER_SIZE + 1];
	int			bwr;
	char		*pn;
	char		*tmp;

	pn = check_rmr(*rmr, line);
	while (!pn && (bwr = read(fd, buf, BUFFER_SIZE)))
	{
		buf[bwr] = '\0';
		if ((pn = ft_strchr(buf, '\n')))
		{
			*pn = '\0';
			*rmr = ft_strdup(++pn);
		}
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buf)) || bwr < 0)
			return (-1);
		free(tmp);
	}
	return (bwr || ft_strlen(*line)) ? 1 : 0;
}

GNL		*new_l_l(int fd)
{
	GNL *new;

	new = (GNL *)malloc(sizeof(GNL));
	new->fd = fd;
	new->rmr = ft_strnew(BUFFER_SIZE);
	new->next = NULL;
	return (new);
}

int		get_next_line(int fd, char **line)
{
	static GNL	*head;
	GNL			*tmp;

	if (fd < 0 || line == NULL)
		return (-1);
	if (head == NULL)
		head = new_l_l(fd);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
			tmp->next = new_l_l(fd);
		tmp = tmp->next;
	}
	return (get_line(tmp->fd, line, &tmp->rmr));
}

int		main(void)
{
	int		fd;
	char	*line;
	int		count;
	int		fd2;

	count = 0;
	fd = open("text.txt", O_RDONLY);
	fd2 = open("text2.txt", O_RDONLY);
	while (get_next_line(fd, &line) && count < 2)
	{
		printf("%s\n\n", line);
		count++;
	}
	while (get_next_line(fd2, &line) && count < 4)
	{
		printf("%s\n\n", line);
		count++;
	}
	while (get_next_line(fd, &line) && count < 6)
	{
		printf("%s\n\n", line);
		count++;
	}
	while(1);
}
