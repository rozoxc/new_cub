/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:37:13 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/12 15:36:46 by ababdoul         ###   ########.fr       */
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
	if ((int)game->player->pos_x == door_x
		&& (int)game->player->pos_y == door_y)
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
	double ray_dirx, double ray_diry)
{
	if (ray->side == 0)
	{
		if (ray_dirx > 0)
			return (game->tex_west);
		else
			return (game->tex_east);
	}
	else
	{
		if (ray_diry > 0)
			return (game->tex_north);
		else
			return (game->tex_south);
	}
}
