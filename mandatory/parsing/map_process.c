/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:15:52 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/03 17:12:30 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	ft_end_with_one(t_vars *vars)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = vars->map;
	while (i < vars->map_h)
	{
		j = vars->map_w - 1;
		while (j >= 0 && map[i][j] == ' ')
			j--;
		if (j >= 0 && map[i][j] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check_zero_surroundings(char **map, int i, int j, t_vars *vars)
{
	if (j + 1 >= vars->map_w || map[i][j + 1] == ' ')
		return (0);
	if (j > 0 && map[i][j - 1] == ' ')
		return (0);
	if (i > 0 && map[i - 1][j] == ' ')
		return (0);
	if (i + 1 < vars->map_h && map[i + 1][j] == ' ')
		return (0);
	return (1);
}

bool	check_map(t_game *game, char **map)
{
	if (!ft_only_ones(map[0]))
		return (err("Top must contain only walls and spaces.\n"), 0);
	if (!ft_only_ones(map[game->vars->map_h - 1]))
		return (err("Bottom must contain only walls and spaces.\n"), 0);
	if (!ft_start_with_one(game->vars))
		return (err("Each map line must start with a wall.\n"), 0);
	if (!ft_end_with_one(game->vars))
		return (err("Each map line must end with a wall.\n"), 0);
}

static int	validate_map_walls_optimized(t_game *game)
{
	char	**map;
	int		i;
	int		j;

	map = game->vars->map;
	if (!check_map(game, map))
		return (0);
	i = 1;
	while (i < game->vars->map_h - 1)
	{
		j = 0;
		while (j < game->vars->map_w)
		{
			if (map[i][j] == '0' || is_player_char(map[i][j]))
				if (!ft_check_zero_surroundings(map, i, j, game->vars))
					return (err("Map is not properly enclosed by walls.\n"), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_map(t_game *game)
{
	char	**tmp_lines;

	tmp_lines = read_map_lines(game->vars, &game->vars->map_h, \
	&game->vars->map_w);
	if (!tmp_lines)
		return (0);
	if (!create_padded_map(game->vars, tmp_lines))
		return (err("Map creation failed.\n"), 0);
	if (!process_map_content(game))
		return (0);
	if (!validate_map_walls_optimized(game))
		return (0);
	return (1);
}
