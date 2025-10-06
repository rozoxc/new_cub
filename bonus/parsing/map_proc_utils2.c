/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_proc_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:30:31 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/06 21:31:27 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int process_map_cell(t_game *vars, size_t x, size_t y, int *player_count)
{
	char c;

	c = vars->vars->map[y][x];
	if (c == '\0')
		return (err("Map contains null character.\n"), 0);
	if (c == '\n')
		return (err("Map contains newline character.\n"), 0);
	if (!is_valid_map_char(c))
		return (err("Invalid character in map.\n"), 0);
	if (is_player_char(c))
		if (!handle_player_position(vars, x, y, player_count))
			return (0);
	return (1);
}

int process_map_content(t_game *vars)
{
	size_t	x; size_t	y; int player_count;

	player_count = 0;
	y = 0;
	while (y < vars->vars->map_h)
	{
		x = 0;
		while (x < vars->vars->map_w)
		{
			if (vars->vars->map[y][x] == ' ')
			{
				x++;
				continue ;
			}
			if (!process_map_cell(vars, x, y, &player_count))
				return (0);
			x++;
		}
		y++;
	}
	if (player_count == 0)
		return (err("No player start position found in map.\n"), 0);
	return (1);
}

int	ft_only_ones(char *str)
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

int	ft_start_with_one(t_vars *vars)
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
