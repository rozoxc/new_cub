/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_process_Utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:03:04 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/03 17:05:57 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || \
			c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	create_padded_map(t_vars *vars, char **tmp_lines)
{
	size_t	i;

	vars->map = ft_malloc(sizeof(char *) * (vars->map_h + 1), 1);
	if (!vars->map)
		return (0);
	i = 0;
	while (i < vars->map_h)
	{
		vars->map[i] = ft_malloc(sizeof(char) * (vars->map_w + 1), 1);
		if (!vars->map[i])
			return (0);
		ft_memset(vars->map[i], ' ', vars->map_w);
		ft_memcpy(vars->map[i], tmp_lines[i], ft_strlen(tmp_lines[i]));
		vars->map[i][vars->map_w] = '\0';
		i++;
	}
	vars->map[i] = NULL;
	return (1);
}

static int	ft_only_ones(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_start_with_one(t_vars *vars)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = vars->map;
	while (i < vars->map_h)
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] != '1')
			return (0);
		i++;
	}
	return (1);
}
