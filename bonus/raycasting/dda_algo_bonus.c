/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:29:06 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/09 10:30:03 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_ray_data(t_game *game, double rayDirX,
		double rayDirY, t_ray_data *data)
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

void	calculate_step_and_side_dist(t_game *game, double rayDirX,
		double rayDirY, t_ray_data *data)
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
		hit = check_wall_hit(game, data);
		i++;
	}
	return (side);
}

void	calculate_wall_distance_b(t_game *game, t_wall_calc *calc, t_ray *ray)
{
	if (calc->side == 0)
		ray->perpWallDist = (calc->data->mapX - game->player->posX
				+ (1 - calc->data->stepX) / 2) / calc->rayDirX;
	else
		ray->perpWallDist = (calc->data->mapY - game->player->posY
				+ (1 - calc->data->stepY) / 2) / calc->rayDirY;
	if (calc->side == 0)
		ray->wallX = game->player->posY + ray->perpWallDist * calc->rayDirY;
	else
		ray->wallX = game->player->posX + ray->perpWallDist * calc->rayDirX;
	ray->wallX -= floor(ray->wallX);
}

t_ray	cast_ray(t_game *game, double rayDirX, double rayDirY)
{
	t_ray		ray;
	t_ray_data	data;
	t_wall_calc	calc;
	int			side;

	init_ray_data(game, rayDirX, rayDirY, &data);
	calculate_step_and_side_dist(game, rayDirX, rayDirY, &data);
	side = perform_dda(game, &data);
	calc.rayDirX = rayDirX;
	calc.rayDirY = rayDirY;
	calc.data = &data;
	calc.side = side;
	calculate_wall_distance_b(game, &calc, &ray);
	finalize_ray(&ray, &data, side);
	return (ray);
}
