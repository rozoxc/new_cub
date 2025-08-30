/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:38:54 by selbouka          #+#    #+#             */
/*   Updated: 2025/08/30 10:39:43 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t i = 0;
    size_t src_len = 0;

    while (src[src_len])
        src_len++;

    if (dstsize == 0)
        return src_len;

    while (i < dstsize - 1 && src[i])
    {
        dst[i] = src[i];
        i++;
    }

    dst[i] = '\0';

    return (src_len);
}