/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:10:31 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/31 22:28:31 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, int n)
{
	char	*pd;
	char	*ps;
	int	i;

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
