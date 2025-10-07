/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo_utlis_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 08:50:55 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/07 08:57:56 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	go_next_square(double *sideDistX, double *sideDistY, double deltaDistX,
		double deltaDistY, int stepX, int stepY, t_ray_data *data)
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
