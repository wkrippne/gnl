/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkrippne <wkrippne@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:49:26 by vziegler          #+#    #+#             */
/*   Updated: 2023/01/08 23:25:32 by wkrippne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

char	*ft_clean(char *steady)
{
	char	*out;
	char	*p;
	int		i;

	p = ft_strchr(steady, '\n');
	if (!p)
		return (ft_free(steady));
	i = p - steady + 1;
	if (!steady[i])
		return (ft_free(steady));
	out = ft_substr(steady, i, ft_strlen(steady) - i);
	free(steady);
	return (out);
}

char	*ft_line(char *steady)
{
	char	*out;
	char	*p;
	int		i;

	p = steady;
	while (*p != '\n' && *p)
		p++;
	if (*p == '\n')
		i = p - steady + 1;
	else
		i = p - steady;
	out = ft_substr(steady, 0, i);
	return (out);
}

void	*ft_free(char *steady)
{
	free(steady);
	return (NULL);
}

char	*ft_read(int fd, char *steady)
{
	int		i;
	char	*p;

	i = 1;
	p = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!p)
		return (NULL);
	*p = '\0';
	while (i > 0 && !ft_strchr(p, '\n'))
	{
		i = read(fd, p, BUFFER_SIZE);
		if (i > 0)
		{
			p[i] = '\0';
			steady = ft_strjoin(steady, p);
		}
	}
	free(p);
	if (i == -1)
		return (ft_free(steady));
	return (steady);
}

char	*get_next_line(int fd)
{
	static char	*steady[10000];
	char		*out;

	if (fd < 0)
		return (NULL);
	steady[fd] = ft_read(fd, steady[fd]);
	if (!steady[fd])
		return (NULL);
	out = ft_line(steady[fd]);
	if (!out)
		return (NULL);
	steady[fd] = ft_clean(steady[fd]);
	return (out);
}

// 85 Das Makro OPEN_MAX gibt die maximale Anzahl von Dateihandles an, 
// 85 die ein Prozess gleichzeitig geöffnet haben kann. Der Wert hängt von der 
// 85 Implementierung der C-Sprache und dem Betriebssystem ab, 
// 85 auf dem das Programm ausgeführt wird.
// 85 steady wird hier zum Doppelpointer auf ein int-Array,
// 85 dadurch werden die einzelnen Lesepunkte der fd-Dateien gespeichert.