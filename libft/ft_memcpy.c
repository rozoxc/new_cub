/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:10:31 by selbouka          #+#    #+#             */
/*   Updated: 2025/11/01 15:59:43 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, int n)
{
	char	*pd;
	char	*ps;
	int		i;

	i = 0;
	pd = (char *)dest;
	ps = (char *)src;
	if (pd == ps)
		return (dest);
	while (i < n)
	{
		pd[i] = ps[i];
		i++;
	}
	return (dest);
}
