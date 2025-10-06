/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:34:44 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/06 21:50:37 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_door_open(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->vars->map_w || y < 0 || y >= game->vars->map_h)
		return (0);
	return (game->vars->map[y][x] == 'd');
}

void	toggle_door(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->vars->map_w || y < 0 || y >= game->vars->map_h)
		return ;
	if (game->vars->map[y][x] == 'D')
		game->vars->map[y][x] = 'd';
	else if (game->vars->map[y][x] == 'd')
		game->vars->map[y][x] = 'D';
}

int	check_door_in_ray(t_game *game, double *ray_x, double *ray_y,
	int *door_coords)
{
	int		map_x;
	int		map_y;
	char	cell;

	map_x = (int)*ray_x;
	map_y = (int)*ray_y;
	if (map_x >= 0 && map_x < game->vars->map_w
		&& map_y >= 0 && map_y < game->vars->map_h)
	{
		cell = game->vars->map[map_y][map_x];
		if (cell == 'D' || cell == 'd')
		{
			door_coords[0] = map_x;
			door_coords[1] = map_y;
			return (1);
		}
		if (cell == '1')
			return (-1);
	}
	return (0);
}

static int	raycast_find_door(t_game *game, double step_x, double step_y,
			int *door_coords)
{
	double	ray_x;
	double	ray_y;
	int		i;
	int		result;

	ray_x = game->player->posX;
	ray_y = game->player->posY;
	i = 0;
	while (i < 20)
	{
		ray_x += step_x;
		ray_y += step_y;
		result = check_door_in_ray(game, &ray_x, &ray_y, door_coords);
		if (result == 1)
			return (1);
		if (result == -1)
			break ;
		i++;
	}
	return (0);
}

int	find_nearest_door(t_game *game, int *door_x, int *door_y)
{
	double	step_x;
	double	step_y;
	int		door_coords[2];
	int		res;

	step_x = game->player->dir_x * 0.1;
	step_y = game->player->dir_y * 0.1;
	res = raycast_find_door(game, step_x, step_y, door_coords);
	if (res == 1)
	{
		*door_x = door_coords[0];
		*door_y = door_coords[1];
		return (1);
	}
	return (0);
}
