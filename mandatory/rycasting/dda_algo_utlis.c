/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo_utlis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 23:39:18 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/02 00:21:14 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	go_next_square(t_ray_data *data)
{
	if (data->sideDistX < data->sideDistY)
		step_in_x(data);
	else
		step_in_y(data);
}

void	calc_perp_wall_dist(t_game *game, t_ray_data *data,
		t_ray *ray, t_ray_calc *calc)
{
	if (calc->side == 0)
		ray->perpWallDist = (data->mapX - game->player->posX
				+ (1 - data->stepX) / 2) / calc->ray_dirx;
	else
		ray->perpWallDist = (data->mapY - game->player->posY
				+ (1 - data->stepY) / 2) / calc->ray_diry;
}

void	calc_wall_x(t_game *game, t_ray *ray, t_ray_calc *calc)
{
	if (calc->side == 0)
		ray->wallX = game->player->posY
			+ ray->perpWallDist * calc->ray_diry;
	else
		ray->wallX = game->player->posX
			+ ray->perpWallDist * calc->ray_dirx;
	ray->wallX -= floor(ray->wallX);
}

void	step_ray_x(t_ray_data *data, int *side)
{
	data->sideDistX += data->deltaDistX;
	data->mapX += data->stepX;
	*side = 0;
}

void	step_ray_y(t_ray_data *data, int *side)
{
	data->sideDistY += data->deltaDistY;
	data->mapY += data->stepY;
	*side = 1;
}
