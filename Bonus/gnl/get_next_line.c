/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseiv <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:42:07 by eseiv             #+#    #+#             */
/*   Updated: 2021/12/13 01:41:50 by eseiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(int fd, char *r)
{
	char	*buff;
	int		bytes_read;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff == 0)
		return (0);
	bytes_read = 1;
	while (!ft_strchr(r, '\n') && bytes_read)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (buff);
			return (0);
		}
		buff[bytes_read] = '\0';
		r = ft_strjoin(r, buff);
	}
	free (buff);
	return (r);
}

char	*lire_ligne(char *r)
{
	int		i;
	char	*line;

	i = 0;
	if (!r[i])
		return (0);
	while (r[i] != '\n' && r[i])
		i++;
	if (r[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (0);
	i = -1;
	while (r[++i] && r[i] != '\n')
		line[i] = r[i];
	if (r[i] == '\n')
	{
		line[i] = r[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_re(char *r)
{
	int		i;
	int		j;
	int		h;
	char	*p;

	i = 0;
	j = 0;
	while (r[i] != '\n' && r[i])
		i++;
	if (!r[i])
	{
		free (r);
		return (0);
	}
	h = (ft_strlen(r) - i);
	p = (char *)malloc(sizeof(char) * (h + 1));
	if (!p)
		return (0);
	i++;
	while (r[i])
		p[j++] = r[i++];
	p[j] = '\0';
	free (r);
	return (p);
}

char	*get_next_line(int fd)
{
	static char	*r;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	r = ft_get_line(fd, r);
	if (r == NULL)
		return (NULL);
	line = lire_ligne(r);
	r = ft_re(r);
	return (line);
}
