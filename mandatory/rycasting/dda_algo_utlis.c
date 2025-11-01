/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo_utlis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 23:39:18 by ababdoul          #+#    #+#             */
/*   Updated: 2025/11/01 16:20:57 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calc_perp_wall_dist(t_game *game, t_ray_data *data,
		t_ray *ray, t_ray_calc *calc)
{
	(void)game;
	if (calc->side == 0)
		ray->perp_walldist = data->sidedist_x - data->deltadist_x;
	else if (calc->side)
		ray->perp_walldist = data->sidedist_y - data->deltadist_y;
}

void	calc_wall_x(t_game *game, t_ray *ray, t_ray_calc *calc)
{
	if (calc->side == 0)
		ray->wall_x = game->player->pos_y
			+ ray->perp_walldist * calc->ray_diry;
	else if (calc->side)
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
