/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:29:06 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/12 15:49:37 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_ray_data(t_game *game, double ray_dirx,
		double ray_diry, t_ray_data *data)
{
	data->map_x = (int)game->player->pos_x;
	data->map_y = (int)game->player->pos_y;
	if (ray_dirx == 0)
		data->deltadist_x = 1e30;
	else
		data->deltadist_x = fabs(1 / ray_dirx);
	if (ray_diry == 0)
		data->deltadist_y = 1e30;
	else
		data->deltadist_y = fabs(1 / ray_diry);
}

void	calculate_step_and_side_dist(t_game *game, double ray_dirx,
		double ray_diry, t_ray_data *data)
{
	if (ray_dirx < 0)
	{
		data->step_x = -1;
		data->sidedist_x = (game->player->pos_x - data->map_x)
			* data->deltadist_x;
	}
	else
	{
		data->step_x = 1;
		data->sidedist_x = (data->map_x + 1.0 - game->player->pos_x)
			* data->deltadist_x;
	}	
	if (ray_diry < 0)
	{
		data->step_y = -1;
		data->sidedist_y = (game->player->pos_y - data->map_y)
			* data->deltadist_y;
	}
	else
	{
		data->step_y = 1;
		data->sidedist_y = (data->map_y + 1.0 - game->player->pos_y)
			* data->deltadist_y;
	}
}

int	perform_dda(t_game *game, t_ray_data *data)
{
	int	hit;
	int	side;
	int	i;

	hit = 0;
	i = 0;
	side = 0;
	while (hit == 0 && i < 1000)
	{
		if (data->sidedist_x < data->sidedist_y)
			step_ray_x(data, &side);
		else
			step_ray_y(data, &side);
		hit = check_wall_hit(game, data);
		i++;
	}
	return (side);
}

void	calculate_wall_distance(t_game *game, double ray_dirx,
		double ray_diry, t_ray_calc *calc)
{
	calc_perp_wall_dist(game, calc->data, calc->ray, calc);
	calc_wall_x(game, calc->ray, calc);
}

t_ray	cast_ray(t_game *game, double ray_dirx, double ray_diry)
{
	t_ray		ray;
	t_ray_data	data;
	t_ray_calc	calc;

	calc.ray_dirx = ray_dirx;
	calc.ray_diry = ray_diry;
	calc.data = &data;
	calc.ray = &ray;
	init_ray_data(game, ray_dirx, ray_diry, &data);
	calculate_step_and_side_dist(game, ray_dirx, ray_diry, &data);
	calc.side = perform_dda(game, &data);
	calculate_wall_distance(game, ray_dirx, ray_diry, &calc);
	ray.side = calc.side;
	ray.map_x = data.map_x;
	ray.map_y = data.map_y;
	return (ray);
}
