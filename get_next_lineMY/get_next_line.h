/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhumfrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 20:44:03 by mhumfrey          #+#    #+#             */
/*   Updated: 2020/11/18 17:01:40 by mhumfrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>

int					get_next_line(int fd, char **line);

size_t				ft_strlen(const char *s);

char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strnew(size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(char *src);
char				*ft_strcpy(char *dest, char *src);

#endif
