/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:29:06 by ababdoul          #+#    #+#             */
/*   Updated: 2025/09/21 13:27:31 by selbouka         ###   ########.fr       */
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
		data->stepX = stepX;  // Store for later use
		data->deltaDistX = deltaDistX;  // Store for later use
	}
	else
	{
		*sideDistY += deltaDistY;
		data->mapY += stepY;
		data->stepY = stepY;  // Store for later use
		data->deltaDistY = deltaDistY;  // Store for later use
	}
}

void	init_ray_data(t_game *game, double rayDirX, double rayDirY, t_ray_data *data)
{
	data->mapX = (int)game->player->posX;
	data->mapY = (int)game->player->posY;
	
	// Calculate delta distances using efficient method
	if (rayDirX == 0)
		data->deltaDistX = 1e30;
	else
		data->deltaDistX = fabs(1 / rayDirX);
		
	if (rayDirY == 0)
		data->deltaDistY = 1e30;
	else
		data->deltaDistY = fabs(1 / rayDirY);
}

void	calculate_step_and_side_dist(t_game *game, double rayDirX, double rayDirY, t_ray_data *data)
{
	// Calculate step direction using efficient method
	if (rayDirX < 0)
	{
		data->stepX = -1;
		data->sideDistX = (game->player->posX - data->mapX) * data->deltaDistX;
	}
	else
	{
		data->stepX = 1;
		data->sideDistX = (data->mapX + 1.0 - game->player->posX) * data->deltaDistX;
	}
	
	if (rayDirY < 0)
	{
		data->stepY = -1;
		data->sideDistY = (game->player->posY - data->mapY) * data->deltaDistY;
	}
	else
	{
		data->stepY = 1;
		data->sideDistY = (data->mapY + 1.0 - game->player->posY) * data->deltaDistY;
	}
}

int	perform_dda(t_game *game, t_ray_data *data)
{
	int	hit;
	int	side;
	int	i;

	hit = 0;
	i = 0;
	while (hit == 0 && i < 1000)  // Safety limit to prevent infinite loops
	{
		if (data->sideDistX < data->sideDistY)
		{
			data->sideDistX += data->deltaDistX;
			data->mapX += data->stepX;
			side = 0;  // WE side
		}
		else
		{
			data->sideDistY += data->deltaDistY;
			data->mapY += data->stepY;
			side = 1;  // NS side
		}
		
		// Check bounds and wall collision
		if (data->mapX >= 0 && data->mapX < game->vars->map_w
			&& data->mapY >= 0 && data->mapY < game->vars->map_h)
		{
			// Check for walls
			if (game->vars->map[data->mapY][data->mapX] == '1')
				hit = 1;
			// Check for doors if door system is implemented
			else if (game->vars->map[data->mapY][data->mapX] == 'D')
				hit = 1;  // Treat closed doors as walls
		}
		else
		{
			// Hit boundary
			hit = 1;
		}
		i++;
	}
	return (side);
}

void	calculate_wall_distance(t_game *game, double rayDirX, double rayDirY,
	t_ray_data *data, t_ray *ray, int side)
{
	// Calculate perpendicular wall distance
	if (side == 0)  // WE side (vertical walls)
		ray->perpWallDist = (data->mapX - game->player->posX
			+ (1 - data->stepX) / 2) / rayDirX;
	else  // NS side (horizontal walls)
		ray->perpWallDist = (data->mapY - game->player->posY
			+ (1 - data->stepY) / 2) / rayDirY;
	
	// Calculate wall X coordinate for texture mapping
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

	// Initialize ray data
	init_ray_data(game, rayDirX, rayDirY, &data);
	
	// Calculate step directions and initial side distances
	calculate_step_and_side_dist(game, rayDirX, rayDirY, &data);
	
	// Perform DDA algorithm
	side = perform_dda(game, &data);
	
	// Calculate final wall distance and texture coordinates
	calculate_wall_distance(game, rayDirX, rayDirY, &data, &ray, side);
	
	// Set ray properties
	ray.side = side;
	ray.mapX = data.mapX;
	ray.mapY = data.mapY;
	
	return (ray);
}