/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_process_Utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:08:44 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/06 14:36:22 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	init_player_direction(t_player *player, char dir)
{
	if (dir == 'N')
	{
		1 && (player->dir_x = 0, player->dir_y = -1);
		1 && (player->plan_x = 0.66, player->plan_y = 0);
	}
	else if (dir == 'S')
	{
		1 && (player->dir_x = 0, player->dir_y = 1);
		player->plan_x = -0.66;
		player->plan_y = 0;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plan_x = 0;
		player->plan_y = 0.66;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plan_x = 0;
		player->plan_y = -0.66;
	}
}

int	fill_player_info__check_char(t_game *vars, int *player_count, int x, int y)
{
	if (!is_valid_map_char(vars->vars->map[y][x]))
		return (err("Invalid character in map.\n"), 0);
	if (is_player_char(vars->vars->map[y][x]))
	{
		if (*player_count > 0)
			return (err("Multiple player positions found.\n"), 0);
		vars->player->posX = x + 0.5;
		vars->player->posY = y + 0.5;
		init_player_direction(vars->player, vars->vars->map[y][x]);
		vars->player->player_dir = vars->vars->map[y][x];
		*player_count = 1;
		vars->vars->map[y][x] = '0';
	}
	return (1);
}

int	process_map_content(t_game *vars)
{
	size_t	x;
	size_t	y;
	int		player_count;

	player_count = 0;
	y = -1;
	while (++y < vars->vars->map_h)
	{
		x = -1;
		while (++x < vars->vars->map_w)
		{
			if (vars->vars->map[y][x] == '\0')
				return (err("Map contains null character.\n"), 0);
			if (vars->vars->map[y][x] == '\n')
				return (err("Map contains newline character.\n"), 0);
			if (vars->vars->map[y][x] == ' ')
				continue ;
			if (!fill_player_info__check_char(vars, &player_count, x, y))
				return (0);
		}
	}
	if (player_count == 0)
		return (err("No player start position found in map.\n"), 0);
	return (1);
}
