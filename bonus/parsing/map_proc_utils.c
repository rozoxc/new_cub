/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_proc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:26:43 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/06 19:26:44 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player_direction(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plan_x = 0.66;
		player->plan_y = 0;
	}
	else if (dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
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

int	ft_end_with_one(t_vars *vars)
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

int	ft_check_zero_surroundings(char **map, int i, int j, t_vars *vars)
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

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

char	**resize_and_copy(char **lines, size_t *capacity, size_t count)
{
	char	**new_lines;
	size_t	i;

	*capacity *= 2;
	new_lines = ft_malloc(sizeof(char *) * (*capacity), 1);
	if (!new_lines)
	{
		ft_malloc(0, 0);
		return (err("Memory reallocation failed\n"), NULL);
	}
	i = 0;
	while (i < count)
	{
		new_lines[i] = lines[i];
		i++;
	}
	return (new_lines);
}
