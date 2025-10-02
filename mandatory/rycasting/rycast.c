/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rycast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:13:54 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/02 08:13:52 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	calculate_tex_x(t_ray *ray, t_texture *texture, double ray_dirx,
		double ray_diry)
{
	int	tex_x;

	tex_x = (int)(ray->wallX * (double)texture->width);
	if (ray->side == 0 && ray_dirx > 0)
		tex_x = texture->width - tex_x - 1;
	if (ray->side == 1 && ray_diry < 0)
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

void	init_wall_draw(t_ray *ray, t_texture *texture, t_draw *draw)
{
	draw->line_height = (int)(WINDOW_HEIGHT / ray->perpWallDist);
	draw->step = 1.0 * texture->height / draw->line_height;
	draw->tex_pos = (draw->draw_start - WINDOW_HEIGHT / 2
			+ draw->line_height / 2) * draw->step;
}

void	draw_texture_pixel(t_game *game, t_ray *ray, t_draw *draw,
		t_texture *texture)
{
	unsigned int	color;

	draw->tex_y = (int)draw->tex_pos;
	if (draw->tex_y >= texture->height)
		draw->tex_y = texture->height - 1;
	if (draw->tex_y < 0)
		draw->tex_y = 0;
	draw->tex_pos += draw->step;
	color = get_texture_pixel(texture, draw->tex_x, draw->tex_y);
	if (ray->side == 1)
		color = (color >> 1) & 0x7F7F7F;
	my_mlx_pixel_put(game->image, draw->x, draw->y, color);
}

void	draw_wall_column(t_game *game, t_ray *ray, int tex_x,
		t_texture *texture)
{
	t_draw	draw;

	draw.x = game->x_loop;
	draw.tex_x = tex_x;
	calculate_wall_bounds(ray, &draw.draw_start, &draw.draw_end);
	init_wall_draw(ray, texture, &draw);
	draw.y = draw.draw_start;
	while (draw.y < draw.draw_end)
	{
		draw_texture_pixel(game, ray, &draw, texture);
		draw.y++;
	}
}

void	render_3d(t_game *game)
{
	t_render	render;

	draw_sky(game);
	draw_floor(game);
	game->x_loop = 0;
	while (game->x_loop < WINDOW_WIDTH)
	{
		render.camera_x = 2 * game->x_loop / (double)WINDOW_WIDTH - 1;
		render.ray_dirx = game->player->dir_x + game->player->plan_x
			* render.camera_x;
		render.ray_diry = game->player->dir_y + game->player->plan_y
			* render.camera_x;
		render.ray = cast_ray(game, render.ray_dirx, render.ray_diry);
		render.current_texture = get_wall_texture(game, &render.ray,
				render.ray_dirx, render.ray_diry);
		render.tex_x = calculate_tex_x(&render.ray, render.current_texture,
				render.ray_dirx, render.ray_diry);
		draw_wall_column(game, &render.ray, render.tex_x,
			render.current_texture);
		game->x_loop++;
	}
}
