/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 05:13:48 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/07 09:14:04 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_tile_by_type(t_game *game, char map_tile, int screen_x,
		int screen_y)
{
	if (map_tile == '1')
		draw_minimap_tile(game, screen_x, screen_y, MINIMAP_WALL_COLOR);
	else if (map_tile == 'D')
		draw_minimap_tile(game, screen_x, screen_y, MINIMAP_DOOR_CLOSED_COLOR);
	else if (map_tile == 'd')
		draw_minimap_tile(game, screen_x, screen_y, MINIMAP_DOOR_OPEN_COLOR);
	else if (is_valid_map_tile(map_tile))
		draw_minimap_tile(game, screen_x, screen_y, MINIMAP_FLOOR_COLOR);
}

void	process_map_tile(t_game *game, t_minimap_data *mini, int map_x,
		int map_y)
{
	int		screen_x;
	int		screen_y;
	char	map_tile;

	screen_x = mini->center_x + (map_x - (int)game->player->posX)
		* MINIMAP_TILE_SIZE;
	screen_y = mini->center_y + (map_y - (int)game->player->posY)
		* MINIMAP_TILE_SIZE;
	if (map_x >= 0 && map_x < game->vars->map_w && map_y >= 0
		&& map_y < game->vars->map_h)
	{
		map_tile = game->vars->map[map_y][map_x];
		draw_tile_by_type(game, map_tile, screen_x, screen_y);
	}
}

void	rotate_player_mouse(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plan_x;

	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(angle)
		- game->player->dir_y * sin(angle);
	game->player->dir_y = old_dir_x * sin(angle)
		+ game->player->dir_y * cos(angle);
	old_plan_x = game->player->plan_x;
	game->player->plan_x = game->player->plan_x * cos(angle)
		- game->player->plan_y * sin(angle);
	game->player->plan_y = old_plan_x * sin(angle)
		+ game->player->plan_y * cos(angle);
}

void	init_mouse_hook(int x, int *prev_x, int *initialized)
{
	if (!(*initialized))
	{
		*prev_x = x;
		*initialized = 1;
	}
}

int	close_window(void)
{
	exit (1);
	return (0);
}
