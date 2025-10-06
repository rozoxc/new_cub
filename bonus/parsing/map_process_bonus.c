/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_process_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:15:52 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/06 19:30:29 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_inner_cells(t_game *game)
{
	char	**map;
	int		i;
	int		j;
	char	cell;

	map = game->vars->map;
	i = 1;
	while (i < game->vars->map_h - 1)
	{
		j = 0;
		while (j < game->vars->map_w)
		{
			cell = map[i][j];
			if (cell == '0' || is_player_char(cell) || cell == 'D'
				|| cell == 'd')
			{
				if (!ft_check_zero_surroundings(map, i, j, game->vars))
					return (err("Map is not properly enclosed by walls.\n"), 0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map_walls_optimized(t_game *game)
{
	char	**map;

	map = game->vars->map;
	if (!ft_only_ones(map[0]))
		return (err("Top boundary must contain only walls and spaces.\n"), 0);
	if (!ft_only_ones(map[game->vars->map_h - 1]))
		return (err("Bottom boundary must contain only walls and spaces.\n"), \
			0);
	if (!ft_start_with_one(game->vars))
		return (err("Each map line must start with a wall.\n"), 0);
	if (!ft_end_with_one(game->vars))
		return (err("Each map line must end with a wall.\n"), 0);
	if (!check_inner_cells(game))
		return (0);
	return (1);
}

int	validate_door_placement(char **map, int x, int y, \
	int map_w, int map_h)
{
	int	horizontal_walls;
	int	vertical_walls;

	if (x <= 0 || x >= map_w - 1 || y <= 0 || y >= map_h - 1)
		return (0);
	horizontal_walls = (map[y][x - 1] == '1' && map[y][x + 1] == '1');
	vertical_walls = (map[y - 1][x] == '1' && map[y + 1][x] == '1');
	if (!horizontal_walls && !vertical_walls)
		return (0);
	if (horizontal_walls && vertical_walls)
		return (0);
	return (1);
}

int	validate_all_doors(t_game *game)
{
	int		x;
	int		y;
	char	cell;

	y = 0;
	while (y < game->vars->map_h)
	{
		x = 0;
		while (x < game->vars->map_w)
		{
			cell = game->vars->map[y][x];
			if (cell == 'D' || cell == 'd')
			{
				if (!validate_door_placement(game->vars->map, x, y,
						game->vars->map_w, game->vars->map_h))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	parse_map(t_game *game)
{
	char	**tmp_lines;

	tmp_lines = read_map_lines(game->vars, &game->vars->map_h,
			&game->vars->map_w);
	if (!tmp_lines)
		return (0);
	if (!create_padded_map(game->vars, tmp_lines))
		return (err("Map creation failed.\n"), 0);
	if (!process_map_content(game))
		return (0);
	if (!validate_map_walls_optimized(game))
		return (0);
	if (!validate_all_doors(game))
		return (err("Invalid door placement detected.\n"), 0);
	return (1);
}
