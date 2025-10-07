/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rycast_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 05:19:33 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/07 05:39:41 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_wall_column(t_game *game, t_ray *ray, int x, int texX,
		t_texture *texture)
{
	t_wall_draw		w;
	unsigned int	color;

	calculate_wall_bounds(ray, &w.drawStart, &w.drawEnd);
	init_wall_drawing(&w, ray, texture);
	while (w.y < w.drawEnd)
	{
		w.texY = (int)w.texPos;
		if (w.texY >= texture->height)
			w.texY = texture->height - 1;
		if (w.texY < 0)
			w.texY = 0;
		w.texPos = w.texPos + w.step;
		color = get_texture_pixel(texture, texX, w.texY);
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		my_mlx_pixel_put(game->image, x, w.y, color);
		w.y++;
	}
}

void	init_ray_data_bonus(t_game *game, int x, t_render_ray *r)
{
	r->cameraX = 2 * x / (double)WINDOW_WIDTH - 1;
	r->rayDirX = game->player->dir_x + game->player->plan_x * r->cameraX;
	r->rayDirY = game->player->dir_y + game->player->plan_y * r->cameraX;
	r->ray = cast_ray_with_doors(game, r->rayDirX, r->rayDirY);
	r->current_texture = get_wall_texture_with_doors(game, &r->ray,
			r->rayDirX, r->rayDirY);
	r->texX = calculate_tex_x(&r->ray, r->current_texture, r->rayDirX,
			r->rayDirY);
}

void	render_walls(t_game *game)
{
	int				x;
	t_render_ray	r;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray_data_bonus(game, x, &r);
		draw_wall_column(game, &r.ray, x, r.texX, r.current_texture);
		x++;
	}
}

void	render_weapon_animation(t_game *game)
{
	static int	j;

	if (j & 1)
		render_hand_with_transparency(game->shoot0_text,
			WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.705, game);
	else
		render_hand_with_transparency(game->shoot1_text,
			WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.705, game);
	j++;
}

void	render_3d(t_game *game)
{
	draw_sky(game);
	draw_floor(game);
	render_walls(game);
	if (game->weapon == 1)
		render_weapon_animation(game);
}
