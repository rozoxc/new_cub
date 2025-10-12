/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo_utlis_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 08:50:55 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/12 15:50:52 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_step_x(t_game *game, double ray_dirx, t_ray_data *data)
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
}

void	calculate_step_y(t_game *game, double ray_diry, t_ray_data *data)
{
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
