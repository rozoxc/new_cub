/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utlis_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 05:03:45 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/07 05:04:00 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_minimap_background(t_game *game)
{
	int	x;
	int	y;

	y = MINIMAP_OFFSET_Y;
	while (y < MINIMAP_OFFSET_Y + MINIMAP_SIZE)
	{
		x = MINIMAP_OFFSET_X;
		while (x < MINIMAP_OFFSET_X + MINIMAP_SIZE)
		{
			my_mlx_pixel_put(game->image, x, y, MINIMAP_BG_COLOR);
			x++;
		}
		y++;
	}
}

int	is_within_minimap_bounds(int screen_x, int screen_y)
{
	if (screen_x < MINIMAP_OFFSET_X || screen_x >= MINIMAP_OFFSET_X
		+ MINIMAP_SIZE || screen_y < MINIMAP_OFFSET_Y
		|| screen_y >= MINIMAP_OFFSET_Y + MINIMAP_SIZE)
		return (0);
	return (1);
}

void	draw_minimap_tile(t_game *game, int screen_x, int screen_y, int color)
{
	int	x;
	int	y;

	if (!is_within_minimap_bounds(screen_x, screen_y))
		return ;
	y = screen_y;
	while (y < screen_y + MINIMAP_TILE_SIZE && y < MINIMAP_OFFSET_Y
		+ MINIMAP_SIZE)
	{
		x = screen_x;
		while (x < screen_x + MINIMAP_TILE_SIZE && x < MINIMAP_OFFSET_X
			+ MINIMAP_SIZE)
		{
			my_mlx_pixel_put(game->image, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap_player(t_game *game, int center_x, int center_y)
{
	int	x;
	int	y;
	int	radius;

	radius = 3;
	y = center_y - radius;
	while (y <= center_y + radius)
	{
		x = center_x - radius;
		while (x <= center_x + radius)
		{
			if ((x - center_x) * (x - center_x) + (y - center_y)
				* (y - center_y) <= radius * radius)
			{
				if (x >= MINIMAP_OFFSET_X && x < MINIMAP_OFFSET_X + MINIMAP_SIZE
					&& y >= MINIMAP_OFFSET_Y && y < MINIMAP_OFFSET_Y
					+ MINIMAP_SIZE)
					my_mlx_pixel_put(game->image, x, y, MINIMAP_PLAYER_COLOR);
			}
			x++;
		}
		y++;
	}
}

int	is_valid_map_tile(char tile)
{
	return (tile == '0' || tile == 'N' || tile == 'S'
		|| tile == 'E' || tile == 'W' || tile == 'd');
}
