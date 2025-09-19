/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:11:36 by ababdoul          #+#    #+#             */
/*   Updated: 2025/09/19 15:16:16 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void clear_image(t_game *game, int color)
{
    int x, y;

    y = 0;
    while (y < WINDOW_HEIGHT)
    {
        x = 0;
        while (x < WINDOW_WIDTH)
        {
            my_mlx_pixel_put(game->image, x, y, color);
            x++;
        }
        y++;
    }
}
// void render_2d(t_game *game) // i will use it after for minimap
// {
//     int x, y;
//     int player_screen_x;
//     int player_screen_y;
//     int dir_end_x;
//     int dir_end_y;

//     y = 0;
//     while (y < game->vars->map_h)
//     {
//         x = 0;
//         while (x < game->vars->map_w)
//         {
//             if (game->vars->map[y][x] == '1')
//             {
//                 draw_rectangle(game, x * TITLE_SIZE, y * TITLE_SIZE, 0x888888);
//             }
//             else if (game->vars->map[y][x] == '0' || game->vars->map[y][x] == 'N')
//             {
//                 draw_rectangle(game, x * TITLE_SIZE, y * TITLE_SIZE, 0x222322);
//             }
//             x++;
//         }
//         y++;
//     }
//     player_screen_x = (int)(game->player->posX * TITLE_SIZE);
//     player_screen_y = (int)(game->player->posY * TITLE_SIZE);
//     draw_circle(game, player_screen_x, player_screen_y, 8, 0xFF0000);
//     dir_end_x = player_screen_x + (int)(game->player->dir_x * 20);
//     dir_end_y = player_screen_y + (int)(game->player->dir_y * 20);
//     draw_line(game, player_screen_x, player_screen_y, dir_end_x, dir_end_y, 0xFFFF00);
// }

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

void	init_line_data(int center_x, int center_y, t_game *game, t_line_data *data)
{
	data->end_x = center_x + (int)(game->player->dir_x * 15);
	data->end_y = center_y + (int)(game->player->dir_y * 15);
	data->dx = abs(data->end_x - center_x);
	data->dy = abs(data->end_y - center_y);
	data->x = center_x;
	data->y = center_y;
	data->n = 1 + data->dx + data->dy;
	if (data->end_x > center_x)
		data->x_inc = 1;
	else
		data->x_inc = -1;
	if (data->end_y > center_y)
		data->y_inc = 1;
	else
		data->y_inc = -1;
	data->error = data->dx - data->dy;
}

void	draw_minimap_direction(t_game *game, int center_x, int center_y)
{
	t_line_data	data;

	init_line_data(center_x, center_y, game, &data);
	while (data.n > 0)
	{
		if (data.x >= MINIMAP_OFFSET_X && data.x < MINIMAP_OFFSET_X
			+ MINIMAP_SIZE && data.y >= MINIMAP_OFFSET_Y
			&& data.y < MINIMAP_OFFSET_Y + MINIMAP_SIZE)
			my_mlx_pixel_put(game->image, data.x, data.y, MINIMAP_DIR_COLOR);
		if (data.error > 0)
		{
			data.x += data.x_inc;
			data.error -= data.dy;
		}
		else
		{
			data.y += data.y_inc;
			data.error += data.dx;
		}
		data.n--;
	}
}

int	is_valid_map_tile(char tile)
{
	return (tile == '0' || tile == 'N' || tile == 'S'
		|| tile == 'E' || tile == 'W');
}

void	draw_map_tiles(t_game *game, t_minimap_data *mini)
{
	int	map_x;
	int	map_y;
	int	screen_x;
	int	screen_y;

	map_y = mini->start_y;
	while (map_y < mini->end_y)
	{
		map_x = mini->start_x;
		while (map_x < mini->end_x)
		{
			screen_x = mini->center_x + (map_x - (int)game->player->posX)
				* MINIMAP_TILE_SIZE;
			screen_y = mini->center_y + (map_y - (int)game->player->posY)
				* MINIMAP_TILE_SIZE;
			if (map_x >= 0 && map_x < game->vars->map_w && map_y >= 0
				&& map_y < game->vars->map_h)
			{
				if (game->vars->map[map_y][map_x] == '1')
					draw_minimap_tile(game, screen_x, screen_y,
						MINIMAP_WALL_COLOR);
				else if (is_valid_map_tile(game->vars->map[map_y][map_x]))
					draw_minimap_tile(game, screen_x, screen_y,
						MINIMAP_FLOOR_COLOR);
			}
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
	draw_minimap_direction(game, mini.center_x, mini.center_y);
}

void render_hand_with_transparency(t_texture *image, int start_x, int start_y, t_game *game)
{
    int x, y;
    unsigned int pixel_color;
    unsigned int transparent_color = 0xFF00FF; // Magenta as transparent color (or use 0x000000 for black)
    
    if (!image || !image->addr)
        return;
    
    for (y = 0; y < image->height; y++)
    {
        for (x = 0; x < image->width; x++)
        {
            // Get pixel from hand texture
            pixel_color = get_texture_pixel(image, x, y);
            
            // Skip transparent pixels (you can adjust the color comparison)
            if (pixel_color != transparent_color && pixel_color != 0x000000) // Skip black/transparent
            {
                // Only draw if within window bounds
                if (start_x + x < WINDOW_WIDTH && start_y + y < WINDOW_HEIGHT &&
                    start_x + x >= 0 && start_y + y >= 0)
                {
                    my_mlx_pixel_put(game->image, start_x + x, start_y + y, pixel_color);
                }
            }
        }
    }
}

void render_game(t_game *game)
{
	
    render_3d(game);
    render_minimap(game);
    mlx_put_image_to_window(game->mlx, game->win, game->image->img, 0, 0);
	if (game->weapon == 0)
		render_hand_with_transparency(game->hands_tex, WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.705 , game);
}
   