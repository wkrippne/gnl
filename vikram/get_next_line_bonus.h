/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vziegler <vziegler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:50:37 by vziegler          #+#    #+#             */
/*   Updated: 2023/01/08 14:58:42 by vziegler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char	*get_next_line(int fd);
char	*ft_read(int fd, char *steady);
void	*ft_free(char *steady);
char	*ft_line(char *steady);
char	*ft_clean(char *steady);
char	*ft_strchr(char *s, int c);
size_t	ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);

#endif