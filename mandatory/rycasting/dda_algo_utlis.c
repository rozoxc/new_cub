/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo_utlis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 23:39:18 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/12 15:39:26 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	go_next_square(t_ray_data *data)
{
	if (data->sidedist_x < data->sidedist_y)
		step_in_x(data);
	else
		step_in_y(data);
}

void	calc_perp_wall_dist(t_game *game, t_ray_data *data,
		t_ray *ray, t_ray_calc *calc)
{
	if (calc->side == 0)
		ray->perp_walldist = (data->map_x - game->player->pos_x
				+ (1 - data->step_x) / 2) / calc->ray_dirx;
	else
		ray->perp_walldist = (data->map_y - game->player->pos_y
				+ (1 - data->step_y) / 2) / calc->ray_diry;
}

void	calc_wall_x(t_game *game, t_ray *ray, t_ray_calc *calc)
{
	if (calc->side == 0)
		ray->wall_x = game->player->pos_y
			+ ray->perp_walldist * calc->ray_diry;
	else
		ray->wall_x = game->player->pos_x
			+ ray->perp_walldist * calc->ray_dirx;
	ray->wall_x -= floor(ray->wall_x);
}

void	step_ray_x(t_ray_data *data, int *side)
{
	data->sidedist_x += data->deltadist_x;
	data->map_x += data->step_x;
	*side = 0;
}

void	step_ray_y(t_ray_data *data, int *side)
{
	data->sidedist_y += data->deltadist_y;
	data->map_y += data->step_y;
	*side = 1;
}
