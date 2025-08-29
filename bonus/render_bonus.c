/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:11:36 by ababdoul          #+#    #+#             */
/*   Updated: 2025/08/05 13:58:16 by ababdoul         ###   ########.fr       */
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
void render_2d(t_game *game) // i will use it after for minimap
{
    int x, y;
    int player_screen_x;
    int player_screen_y;
    int dir_end_x;
    int dir_end_y;

    y = 0;
    while (y < game->map->height)
    {
        x = 0;
        while (x < game->map->width)
        {
            if (game->map->map[y][x] == '1')
            {
                draw_rectangle(game, x * TITLE_SIZE, y * TITLE_SIZE, 0x888888);
            }
            else if (game->map->map[y][x] == '0' || game->map->map[y][x] == 'N')
            {
                draw_rectangle(game, x * TITLE_SIZE, y * TITLE_SIZE, 0x222322);
            }
            x++;
        }
        y++;
    }
    player_screen_x = (int)(game->player->posX * TITLE_SIZE);
    player_screen_y = (int)(game->player->posY * TITLE_SIZE);
    draw_circle(game, player_screen_x, player_screen_y, 8, 0xFF0000);
    dir_end_x = player_screen_x + (int)(game->player->dir_x * 20);
    dir_end_y = player_screen_y + (int)(game->player->dir_y * 20);
    draw_line(game, player_screen_x, player_screen_y, dir_end_x, dir_end_y, 0xFFFF00);
}

void render_game(t_game *game)
{
    render_3d(game);
    render_2d(game);
    mlx_put_image_to_window(game->mlx, game->win, game->image->img, 0, 0);
}
