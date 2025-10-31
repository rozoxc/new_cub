/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:35:54 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/31 22:07:40 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int content)
{
	t_list	*p;

	p = ft_malloc(sizeof(t_list), 1);
	if (!p)
		err("Allocation failed\n");
	p->content = content;
	p->next = NULL;
	return (p);
}
