/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:54:51 by selbouka          #+#    #+#             */
/*   Updated: 2025/08/16 03:01:19 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"

char	*get_next_line(int fd);
char	*joining(char const *s1, char const *s2);
char	*search(const char *str, int c);
int		len(const char *str);
char	*duplicate(const char *src);
void	*ft_malloc(size_t size, int mode);

#endif