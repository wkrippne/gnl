/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkrippne <wkrippne@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:51:07 by vziegler          #+#    #+#             */
/*   Updated: 2023/01/08 23:07:57 by wkrippne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	size_t	len;
	size_t	c;
	size_t	i;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		*s1 = '\0';
	}
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = malloc (len);
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, len);
	c = -1;
	i = ft_strlen(p);
	while (s2[++c])
		p[i + c] = s2[c];
	p[i + c] = '\0';
	free(s1);
	return (p);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	if (*s == (char) c)
		return ((char *) s);
	return (NULL);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	slen;

	slen = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start > slen)
	{
		p = malloc(sizeof(char));
		if (!p)
			return (NULL);
		*p = '\0';
		return (p);
	}
	if (start + len > slen)
		len = slen - start;
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s + start, len + 1);
	return (p);
}
