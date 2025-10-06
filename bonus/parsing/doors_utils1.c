/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:37:13 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/06 19:39:02 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_door_at_position(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->vars->map_w || y < 0 || y >= game->vars->map_h)
		return (0);
	return (game->vars->map[y][x] == 'D' || game->vars->map[y][x] == 'd');
}

int	can_close_door(t_game *game, int door_x, int door_y)
{
	if ((int)game->player->posX == door_x
		&& (int)game->player->posY == door_y)
		return (0);
	return (1);
}

void	handle_door_interaction(t_game *game)
{
	int		door_x;
	int		door_y;
	char	current_state;

	if (find_nearest_door(game, &door_x, &door_y))
	{
		current_state = game->vars->map[door_y][door_x];
		if (current_state == 'D')
			game->vars->map[door_y][door_x] = 'd';
		else if (current_state == 'd')
		{
			if (can_close_door(game, door_x, door_y))
				game->vars->map[door_y][door_x] = 'D';
		}
	}
}

t_texture	*select_wall_texture(t_game *game, t_ray *ray,
	double rayDirX, double rayDirY)
{
	if (ray->side == 0)
	{
		if (rayDirX > 0)
			return (game->tex_west);
		else
			return (game->tex_east);
	}
	else
	{
		if (rayDirY > 0)
			return (game->tex_north);
		else
			return (game->tex_south);
	}
}
