/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rycast_utlis_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 05:20:48 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/07 05:29:46 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_sky(t_game *game)
{
	int	i;
	int	pj;

	i = 0;
	while (i < WINDOW_HEIGHT / 2)
	{
		pj = 0;
		while (pj < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(game->image, pj, i, game->vars->sky.rgb);
			pj++;
		}
		i++;
	}
}

void	draw_floor(t_game *game)
{
	int	j;
	int	pj;

	j = WINDOW_HEIGHT / 2;
	while (j < WINDOW_HEIGHT)
	{
		pj = 0;
		while (pj < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(game->image, pj, j, game->vars->floor.rgb);
			pj++;
		}
		j++;
	}
}

void	calculate_wall_bounds(t_ray *ray, int *drawStart, int *drawEnd)
{
	int	line_height;

	line_height = (int)(WINDOW_HEIGHT / ray->perpWallDist);
	*drawStart = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (*drawStart < 0)
		*drawStart = 0;
	*drawEnd = line_height / 2 + WINDOW_HEIGHT / 2;
	if (*drawEnd >= WINDOW_HEIGHT)
		*drawEnd = WINDOW_HEIGHT - 1;
}

int	calculate_tex_x(t_ray *ray, t_texture *texture, double rayDirX,
		double rayDirY)
{
	int	tex_x;

	tex_x = (int)(ray->wallX * (double)texture->width);
	if (ray->side == 0 && rayDirX > 0)
		tex_x = texture->width - tex_x - 1;
	if (ray->side == 1 && rayDirY < 0)
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

void	init_wall_drawing(t_wall_draw *w, t_ray *ray, t_texture *texture)
{
	int	line_height;

	line_height = (int)(WINDOW_HEIGHT / ray->perpWallDist);
	w->step = 1.0 * texture->height / line_height;
	w->texPos = (w->drawStart - WINDOW_HEIGHT / 2 + line_height / 2) * w->step;
	w->y = w->drawStart;
}
