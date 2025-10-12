/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:34:03 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/12 15:36:46 by ababdoul         ###   ########.fr       */
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
		if (data->sidedist_x < data->sidedist_y)
			1 && (data->sidedist_x += data->deltadist_x, \
				data->map_x += data->step_x, side = 0);
		else
		{
			data->sidedist_y += data->deltadist_y;
			data->map_y += data->step_y;
			side = 1;
		}
		if (data->map_x >= 0 && data->map_x < game->vars->map_w
			&& data->map_y >= 0 && data->map_y < game->vars->map_h)
		{
			map_char = game->vars->map[data->map_y][data->map_x];
			if (map_char == '1' || map_char == 'D')
				hit = 1;
		}
	}
	return (side);
}

t_texture	*get_wall_texture_with_doors(t_game *game, t_ray *ray,
	double ray_dirx, double ray_diry)
{
	char	map_char;

	if (ray->map_x >= 0 && ray->map_x < game->vars->map_w
		&& ray->map_y >= 0 && ray->map_y < game->vars->map_h)
	{
		map_char = game->vars->map[ray->map_y][ray->map_x];
		if (map_char == 'D')
			return (game->tex_door);
	}
	return (select_wall_texture(game, ray, ray_dirx, ray_diry));
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

t_ray	cast_ray_with_doors(t_game *game, double ray_dirx, double ray_diry)
{
	t_ray		ray;
	t_ray_data	data;
	t_wall_calc	calc;
	int			side;

	init_ray_data(game, ray_dirx, ray_diry, &data);
	calculate_step_x(game, ray_dirx, &data);
	calculate_step_y(game, ray_diry, &data);
	side = perform_dda_with_doors(game, &data);
	calc.ray_dirx = ray_dirx;
	calc.ray_diry = ray_diry;
	calc.data = &data;
	calc.side = side;
	calculate_wall_distance_b(game, &calc, &ray);
	ray.side = side;
	ray.map_x = data.map_x;
	ray.map_y = data.map_y;
	return (ray);
}
