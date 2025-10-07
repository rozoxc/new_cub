/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:11:36 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/07 05:13:16 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_map_tiles(t_game *game, t_minimap_data *mini)
{
	int	map_x;
	int	map_y;

	map_y = mini->start_y;
	while (map_y < mini->end_y)
	{
		map_x = mini->start_x;
		while (map_x < mini->end_x)
		{
			process_map_tile(game, mini, map_x, map_y);
			map_x++;
		}
		map_y++;
	}
}

void	render_minimap(t_game *game)
{
	t_minimap_data	mini;

	draw_minimap_background(game);
	mini.center_x = MINIMAP_OFFSET_X + MINIMAP_SIZE / 2;
	mini.center_y = MINIMAP_OFFSET_Y + MINIMAP_SIZE / 2;
	mini.start_x = (int)game->player->posX - MINIMAP_VIEW_RANGE / 2;
	mini.start_y = (int)game->player->posY - MINIMAP_VIEW_RANGE / 2;
	mini.end_x = mini.start_x + MINIMAP_VIEW_RANGE;
	mini.end_y = mini.start_y + MINIMAP_VIEW_RANGE;
	draw_map_tiles(game, &mini);
	draw_minimap_player(game, mini.center_x, mini.center_y);
}

void	check_pixel_transparency(t_render_data *d, t_texture *image)
{
	d->pixel_color = get_texture_pixel(image, d->x, d->y);
	if (d->pixel_color != d->transparent_color && d->pixel_color != 0x000000)
	{
		if (d->start_x + d->x < WINDOW_WIDTH
			&& d->start_y + d->y < WINDOW_HEIGHT
			&& d->start_x + d->x >= 0 && d->start_y + d->y >= 0)
		{
			d->should_draw = 1;
		}
	}
}

void	render_hand_with_transparency(t_texture *image, int start_x,
		int start_y, t_game *game)
{
	t_render_data	d;

	if (!image || !image->addr)
		return ;
	d.transparent_color = 0xFF00FF;
	d.start_x = start_x;
	d.start_y = start_y;
	d.y = 0;
	while (d.y < image->height)
	{
		d.x = 0;
		while (d.x < image->width)
		{
			d.should_draw = 0;
			check_pixel_transparency(&d, image);
			if (d.should_draw)
				my_mlx_pixel_put(game->image, d.start_x + d.x,
					d.start_y + d.y, d.pixel_color);
			d.x++;
		}
		d.y++;
	}
}

void	render_game(t_game *game)
{
	render_3d(game);
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image->img, 0, 0);
	if (game->weapon == 0)
		render_hand_with_transparency(game->hands_tex,
			WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.705, game);
}
