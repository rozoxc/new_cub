/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rycast_utlis_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 05:20:48 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/12 15:50:19 by ababdoul         ###   ########.fr       */
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

void	calculate_wall_bounds(t_ray *ray, int *draw_start, int *draw_end)
{
	int	line_height;

	line_height = (int)(WINDOW_HEIGHT / ray->perp_walldist);
	*draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (*draw_end >= WINDOW_HEIGHT)
		*draw_end = WINDOW_HEIGHT - 1;
}

int	calculate_tex_x(t_ray *ray, t_texture *texture, double ray_dirx,
		double ray_diry)
{
	int	tex_x;

	tex_x = (int)(ray->wall_x * (double)texture->width);
	if (ray->side == 0 && ray_dirx > 0)
		tex_x = texture->width - tex_x - 1;
	if (ray->side == 1 && ray_diry < 0)
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

void	init_wall_drawing(t_wall_draw *w, t_ray *ray, t_texture *texture)
{
	int	line_height;

	line_height = (int)(WINDOW_HEIGHT / ray->perp_walldist);
	w->step = 1.0 * texture->height / line_height;
	w->tex_pos = (w->draw_start - WINDOW_HEIGHT / 2 + line_height / 2)
		* w->step;
	w->y = w->draw_start;
}
