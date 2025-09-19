/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:11:36 by ababdoul          #+#    #+#             */
/*   Updated: 2025/09/14 15:19:08 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
void render_hand_with_transparency(t_game *game, int start_x, int start_y)
{
    int x, y;
    unsigned int pixel_color;
    unsigned int transparent_color = 0xFF00FF; // Magenta as transparent color (or use 0x000000 for black)
    
    if (!game->hands_tex || !game->hands_tex->addr)
        return;
    
    for (y = 0; y < game->hands_tex->height; y++)
    {
        for (x = 0; x < game->hands_tex->width; x++)
        {
            // Get pixel from hand texture
            pixel_color = get_texture_pixel(game->hands_tex, x, y);
            
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
    mlx_put_image_to_window(game->mlx, game->win, game->image->img, 0, 0);
    // mlx_put_image_to_window(game->mlx, game->win, game->hands_tex->img,50, 250);
    render_hand_with_transparency(game, 0, WINDOW_HEIGHT / 2);
}
