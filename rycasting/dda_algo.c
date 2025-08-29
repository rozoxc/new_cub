/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:29:06 by ababdoul          #+#    #+#             */
/*   Updated: 2025/08/27 02:58:09 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_ray_data(t_game *game, double rayDirX, double rayDirY, t_ray_data *data)
{
	data->mapX = (int)game->player->posX;
	data->mapY = (int)game->player->posY;
	if (rayDirX == 0)
		data->deltaDistX = 1e30;
	else
		data->deltaDistX = fabs(1 / rayDirX);
	if (rayDirY == 0)
		data->deltaDistY = 1e30;
	else
		data->deltaDistY = fabs(1 / rayDirY);
}

void	calculate_step_x(t_game *game, double rayDirX, t_ray_data *data)
{
	if (rayDirX < 0)
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
}

void	calculate_step_y(t_game *game, double rayDirY, t_ray_data *data)
{
	if (rayDirY < 0)
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

	hit = 0;
	while (hit == 0)
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
			&& data->mapY >= 0 && data->mapY < game->vars->map_h
			&& game->vars->map[data->mapY][data->mapX] == '1')
			hit = 1;
	}
	return (side);
}

void	calculate_wall_distance(t_game *game, double rayDirX, double rayDirY,
	t_ray_data *data, t_ray *ray, int side)
{
	if (side == 0)
		ray->perpWallDist = (data->mapX - game->player->posX
				+ (1 - data->stepX) / 2) / rayDirX;
	else
		ray->perpWallDist = (data->mapY - game->player->posY
				+ (1 - data->stepY) / 2) / rayDirY;
	if (side == 0)
		ray->wallX = game->player->posY + ray->perpWallDist * rayDirY;
	else
		ray->wallX = game->player->posX + ray->perpWallDist * rayDirX;
	ray->wallX -= floor(ray->wallX);
}

t_ray	cast_ray(t_game *game, double rayDirX, double rayDirY)
{
	t_ray		ray;
	t_ray_data	data;
	int			side;

	init_ray_data(game, rayDirX, rayDirY, &data);//initialize ray data
	calculate_step_x(game, rayDirX, &data);// step and initial sideDist
	calculate_step_y(game, rayDirY, &data);// step and initial sideDist
	side = perform_dda(game, &data);//perform DDA
	calculate_wall_distance(game, rayDirX, rayDirY, &data, &ray, side);//calculate distance projected on camera direction
	ray.side = side;
	ray.mapX = data.mapX;
	ray.mapY = data.mapY;
	return (ray);
}
