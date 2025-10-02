/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:29:06 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/02 00:17:49 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_ray_data(t_game *game, double ray_dirx,
		double ray_diry, t_ray_data *data)
{
	data->mapX = (int)game->player->posX;
	data->mapY = (int)game->player->posY;
	if (ray_dirx == 0)
		data->deltaDistX = 1e30;
	else
		data->deltaDistX = fabs(1 / ray_dirx);
	if (ray_diry == 0)
		data->deltaDistY = 1e30;
	else
		data->deltaDistY = fabs(1 / ray_diry);
}

void	calculate_step_and_side_dist(t_game *game, double ray_dirx,
		double ray_diry, t_ray_data *data)
{
	if (ray_dirx < 0)
	{
		data->stepX = -1;
		data->sideDistX = (game->player->posX - data->mapX) * data->deltaDistX;
	}
	else
	{
		data->stepX = 1;
		data->sideDistX = (data->mapX + 1.0 - game->player->posX)
			* data->deltaDistX;
	}	
	if (ray_diry < 0)
	{
		data->stepY = -1;
		data->sideDistY = (game->player->posY - data->mapY) * data->deltaDistY;
	}
	else
	{
		data->stepY = 1;
		data->sideDistY = (data->mapY + 1.0 - game->player->posY)
			* data->deltaDistY;
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
		if (data->sideDistX < data->sideDistY)
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
	ray.mapX = data.mapX;
	ray.mapY = data.mapY;
	return (ray);
}
