/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:14:10 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/02 00:22:27 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_wall_hit(t_game *game, t_ray_data *data)
{
	char	cell;

	if (data->mapX < 0 || data->mapX >= game->vars->map_w
		|| data->mapY < 0 || data->mapY >= game->vars->map_h)
		return (1);
	cell = game->vars->map[data->mapY][data->mapX];
	if (cell == '1')
		return (1);
	return (0);
}

void	step_in_x(t_ray_data *data)
{
	data->sideDistX += data->deltaDistX;
	data->mapX += data->stepX;
}

void	step_in_y(t_ray_data *data)
{
	data->sideDistY += data->deltaDistY;
	data->mapY += data->stepY;
}
