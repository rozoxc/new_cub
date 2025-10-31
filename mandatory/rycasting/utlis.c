/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:14:10 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/31 22:22:41 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_wall_hit(t_game *game, t_ray_data *data)
{
	char	cell;

	//check

	
	if (data->map_x < 0 || data->map_x >= game->vars->map_w
		|| data->map_y < 0 || data->map_y >= game->vars->map_h)
		return (1);
	cell = game->vars->map[data->map_y][data->map_x];
	if (cell == '1')
		return (1);
	return (0);
}

void	step_in_x(t_ray_data *data)
{
	data->sidedist_x += data->deltadist_x;
	data->map_x += data->step_x;
}

void	step_in_y(t_ray_data *data)
{
	data->sidedist_y += data->deltadist_y;
	data->map_y += data->step_y;
}
