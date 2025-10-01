/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:29:06 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/01 08:09:56 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	go_next_square(double *sideDistX, double *sideDistY, 
		double deltaDistX, double deltaDistY, int stepX, int stepY, t_ray_data *data)
{
	if (*sideDistX < *sideDistY)
	{
		*sideDistX += deltaDistX;
		data->mapX += stepX;
		data->stepX = stepX;
		data->deltaDistX = deltaDistX;
	}
	else
	{
		*sideDistY += deltaDistY;
		data->mapY += stepY;
		data->stepY = stepY;
		data->deltaDistY = deltaDistY;
	}
}

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
		data->sideDistX = (data->mapX + 1.0 - game->player->posX) * data->deltaDistX;
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
	while (hit == 0 && i < 1000)
	{
		if (data->sideDistX < data->sideDistY)
		{
			data->sideDistX += data->deltaDistX;
			data->mapX += data->stepX;
			side = 0;
		}
		else
		{
			data->sideDistY += data->deltaDistY;
			data->mapY += data->stepY;
			side = 1;
		}
		if (data->mapX >= 0 && data->mapX < game->vars->map_w
			&& data->mapY >= 0 && data->mapY < game->vars->map_h)
		{
			if (game->vars->map[data->mapY][data->mapX] == '1')
				hit = 1;
			else if (game->vars->map[data->mapY][data->mapX] == 'D')
				hit = 1;
		}
		else
			hit = 1;
		i++;
	}
	return (side);
}

void	calculate_wall_distance(t_game *game, double ray_dirx, double ray_diry,
	t_ray_data *data, t_ray *ray, int side)
{
	if (side == 0)
		ray->perpWallDist = (data->mapX - game->player->posX
			+ (1 - data->stepX) / 2) / ray_dirx;
	else
		ray->perpWallDist = (data->mapY - game->player->posY
			+ (1 - data->stepY) / 2) / ray_diry;
	if (side == 0)
		ray->wallX = game->player->posY + ray->perpWallDist * ray_diry;
	else
		ray->wallX = game->player->posX + ray->perpWallDist * ray_dirx;
	
	ray->wallX -= floor(ray->wallX);
}

t_ray	cast_ray(t_game *game, double ray_dirx, double ray_diry)
{
	t_ray		ray;
	t_ray_data	data;
	int		side;

	init_ray_data(game, ray_dirx, ray_diry, &data);
	calculate_step_and_side_dist(game, ray_dirx, ray_diry, &data);
	side = perform_dda(game, &data);
	calculate_wall_distance(game, ray_dirx, ray_diry, &data, &ray, side);
	ray.side = side;
	ray.mapX = data.mapX;
	ray.mapY = data.mapY;
	return (ray);
}
