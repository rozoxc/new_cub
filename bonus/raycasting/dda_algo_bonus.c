/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:29:06 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/12 15:51:40 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_ray_data(t_game *game, double ray_dirx,
		double ray_diry, t_ray_data *data)
{
	data->map_x = (int)game->player->pos_x;
	data->map_y = (int)game->player->pos_y;
	if (ray_dirx == 0)
		data->deltadist_x = 1e30;
	else
		data->deltadist_x = fabs(1 / ray_dirx);
	if (ray_diry == 0)
		data->deltadist_y = 1e30;
	else
		data->deltadist_y = fabs(1 / ray_diry);
}

void	calculate_step_and_side_dist(t_game *game, double ray_dirx,
		double ray_diry, t_ray_data *data)
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

int	perform_dda(t_game *game, t_ray_data *data)
{
	int	hit;
	int	side;
	int	i;

	hit = 0;
	i = 0;
	while (hit == 0 && i < 1000)
	{
		if (data->sidedist_x < data->sidedist_y)
		{
			data->sidedist_x += data->deltadist_x;
			data->map_x += data->step_x;
			side = 0;
		}
		else
		{
			data->sidedist_y += data->deltadist_y;
			data->map_y += data->step_y;
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
		ray->perp_walldist = (calc->data->map_x - game->player->pos_x
				+ (1 - calc->data->step_x) / 2) / calc->ray_dirx;
	else
		ray->perp_walldist = (calc->data->map_y - game->player->pos_y
				+ (1 - calc->data->step_y) / 2) / calc->ray_diry;
	if (calc->side == 0)
		ray->wall_x = game->player->pos_y + ray->perp_walldist * calc->ray_diry;
	else
		ray->wall_x = game->player->pos_x + ray->perp_walldist * calc->ray_dirx;
	ray->wall_x -= floor(ray->wall_x);
}

t_ray	cast_ray(t_game *game, double ray_dirx, double ray_diry)
{
	t_ray		ray;
	t_ray_data	data;
	t_wall_calc	calc;
	int			side;

	init_ray_data(game, ray_dirx, ray_diry, &data);
	calculate_step_and_side_dist(game, ray_dirx, ray_diry, &data);
	side = perform_dda(game, &data);
	calc.ray_dirx = ray_dirx;
	calc.ray_diry = ray_diry;
	calc.data = &data;
	calc.side = side;
	calculate_wall_distance_b(game, &calc, &ray);
	finalize_ray(&ray, &data, side);
	return (ray);
}
