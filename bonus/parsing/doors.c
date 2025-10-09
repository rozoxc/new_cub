/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:34:03 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/09 10:37:10 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	perform_dda_with_doors(t_game *game, t_ray_data *data)
{
	int		hit;
	int		side;
	char	map_char;

	hit = 0;
	while (hit == 0)
	{
		if (data->sideDistX < data->sideDistY)
			1 && (data->sideDistX += data->deltaDistX, \
				data->mapX += data->stepX, side = 0);
		else
		{
			data->sideDistY += data->deltaDistY;
			data->mapY += data->stepY;
			side = 1;
		}
		if (data->mapX >= 0 && data->mapX < game->vars->map_w
			&& data->mapY >= 0 && data->mapY < game->vars->map_h)
		{
			map_char = game->vars->map[data->mapY][data->mapX];
			if (map_char == '1' || map_char == 'D')
				hit = 1;
		}
	}
	return (side);
}

t_texture	*get_wall_texture_with_doors(t_game *game, t_ray *ray,
	double rayDirX, double rayDirY)
{
	char	map_char;

	if (ray->mapX >= 0 && ray->mapX < game->vars->map_w
		&& ray->mapY >= 0 && ray->mapY < game->vars->map_h)
	{
		map_char = game->vars->map[ray->mapY][ray->mapX];
		if (map_char == 'D')
			return (game->tex_door);
	}
	return (select_wall_texture(game, ray, rayDirX, rayDirY));
}

int	is_valid_move_with_doors(t_game *game, double new_x, double new_y)
{
	int		map_x;
	int		map_y;
	char	map_char;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_x < 0 || map_x >= game->vars->map_w
		|| map_y < 0 || map_y >= game->vars->map_h)
		return (0);
	map_char = game->vars->map[map_y][map_x];
	if (map_char == '1' || map_char == 'D')
		return (0);
	return (1);
}

t_ray	cast_ray_with_doors(t_game *game, double rayDirX, double rayDirY)
{
	t_ray		ray;
	t_ray_data	data;
	t_wall_calc	calc;
	int			side;

	init_ray_data(game, rayDirX, rayDirY, &data);
	calculate_step_x(game, rayDirX, &data);
	calculate_step_y(game, rayDirY, &data);
	side = perform_dda_with_doors(game, &data);
	calc.rayDirX = rayDirX;
	calc.rayDirY = rayDirY;
	calc.data = &data;
	calc.side = side;
	calculate_wall_distance_b(game, &calc, &ray);
	ray.side = side;
	ray.mapX = data.mapX;
	ray.mapY = data.mapY;
	return (ray);
}
