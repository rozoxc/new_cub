/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:48:09 by selbouka          #+#    #+#             */
/*   Updated: 2025/08/30 10:18:12 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n'
         || c == '\r' || c == '\v' || c == '\f');
}

char	*ft_strtrim(char const *s)
{
	int start;
    int end;
    char *out;
    int len;

    if (!s)
        return NULL;

    start = 0;
    while (s[start] && ft_isspace((unsigned char)s[start]))
        start++;

    end = ft_strlen(s) - 1;
    while (end >= start && ft_isspace((unsigned char)s[end]))
        end--;

    len = end - start + 1;

    out = ft_malloc(len + 1, 1);
    if (!out)
        return NULL;

    ft_memcpy(out, s + start, len);
    out[len] = '\0';

    return (out);
}
