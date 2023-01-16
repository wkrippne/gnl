/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkrippne <wkrippne@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 21:08:30 by vziegler          #+#    #+#             */
/*   Updated: 2023/01/08 23:28:09 by wkrippne         ###   ########.fr       */
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
	static char	*steady;
	char		*out;

	if (fd < 0)
		return (NULL);
	steady = ft_read(fd, steady);
	if (!steady)
		return (NULL);
	out = ft_line(steady);
	if (!out)
		return (NULL);
	steady = ft_clean(steady);
	return (out);
}

int main(void)
{
  int fd;
  char *line;
  
  fd = open("empty.txt", O_RDONLY);
  line = get_next_line(fd);
  if (line == NULL) {
    printf("Test passed: get_next_line returned NULL as expected\n");
  } else {
    printf("Test failed: get_next_line did not return NULL as expected\n");
  }
  close(fd);
  return 0;
}

// 27 Check für den Fall EOF, direkt nach '\n'
// 41 Funktioniert auch, wenn nur nach neuer Zeile gesucht wird.
// 41 Vergleiche Z. 24, warum ist unklar.
// 43 p beinhaltet die Adresse von '\n', steady den Anfang des Strings.
// 43 i entspricht der Länge des Strings, steady[i] ist die Stelle nach '\n'.
// 43 Falls kein '\n' enthalten ist, braucht man eine Stelle weniger, 
// 43 da substr automatisch terminiert.
// 43 Würde aber auch ohne das if-else-Statement funktionieren.
// 47 Substring beendet den String mit '\0'.
// 66 Wird initialisiert, damit strchr weiß bis wo es suchen muss.
// 67 Bricht ab, falls EOF oder '\n' innerhalb der kopierten Buffersize ist.
// 69 Liefert die Zahl gelesener Bytes, 
// 69 0 bei only EOF oder -1 bei Fehler.
// 69 p wird in der Loop immer wieder überschrieben und an steady angehängt.
// 69 read speichert die Stelle des Dateizeigers und 
// 69 weiß dadurch wo es weiterlesen muss.
// 73 strjoin freed steady nach der Stringerstellung, 
// 73 weil steady das in der vorigen Loop gemallocede p ist.
// 76 Der mit malloc() für p reservierte Speicherbereich wird gefreed,
// 76 weil p (anders als steady) nicht returned wird.
// 76 Der Speicherbereich für steady wurde in ft_strjoin gemalloced.
// 87 Die static-Variable wird gebraucht, 
// 87 weil die Funktion get_next_line mehrmals aufgerufen wird.
// 87 static wird dadurch nur beim ersten Mal initialisiert und 
// 87 behält seinen Wert über die Aufrufe hinweg.
// 93 Danach wird nicht !steady geprüft, 
// 93 weil steady im Fall der letzten Zeile den Wert NULL returned bekommt.
// 96 out wurde in line gemalloced und wird nicht gefreed, da es returned wird.
// 96 steady wurde in read gemalloced und wird in in jedem Fall clean gefreed.