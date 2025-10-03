/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 02:57:35 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/03 16:56:29 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	is_whitespace_only(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	count_char(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	is_valid_rgb(char *str)
{
	int	i;
	int	value;

	value = -1;
	i = 0;
	if (!str || ft_strlen(str) == 0 || ft_strlen(str) > 3)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	value = ft_atoi(str);
	return (value >= 0 && value <= 255);
}

void	init_vars(t_vars *var)
{
	var->tex.north = NULL;
	var->tex.south = NULL;
	var->tex.west = NULL;
	var->tex.east = NULL;
	var->tex.door = NULL;
	var->floor.r = -1;
	var->floor.g = -1;
	var->floor.b = -1;
	var->sky.r = -1;
	var->sky.g = -1;
	var->sky.b = -1;
	var->map = NULL;
	var->fd = -1;
}
