/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis_bonus_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:21:36 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/09 10:24:52 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	finalize_ray(t_ray *ray, t_ray_data *data, int side)
{
	ray->side = side;
	ray->mapX = data->mapX;
	ray->mapY = data->mapY;
}

int	check_wall_hit(t_game *game, t_ray_data *data)
{
	if (data->mapX >= 0 && data->mapX < game->vars->map_w
		&& data->mapY >= 0 && data->mapY < game->vars->map_h)
	{
		if (game->vars->map[data->mapY][data->mapX] == '1')
			return (1);
		else if (game->vars->map[data->mapY][data->mapX] == 'D')
			return (1);
	}
	else
		return (1);
	return (0);
}
