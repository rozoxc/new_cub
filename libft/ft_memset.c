/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:15:27 by selbouka          #+#    #+#             */
/*   Updated: 2025/11/01 16:00:51 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, int n)
{
	int					i;
	unsigned char		*ptr;

	ptr = (unsigned char *)str;
	i = 0;
	while (i < n)
		ptr[i++] = (unsigned char)c;
	return (str);
}
