/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis_bonus_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:21:36 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/12 15:29:52 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	finalize_ray(t_ray *ray, t_ray_data *data, int side)
{
	ray->side = side;
	ray->map_x = data->map_x;
	ray->map_y = data->map_y;
}

int	check_wall_hit(t_game *game, t_ray_data *data)
{
	if (data->map_x >= 0 && data->map_x < game->vars->map_w
		&& data->map_y >= 0 && data->map_y < game->vars->map_h)
	{
		if (game->vars->map[data->map_y][data->map_x] == '1')
			return (1);
		else if (game->vars->map[data->map_y][data->map_x] == 'D')
			return (1);
	}
	else
		return (1);
	return (0);
}
