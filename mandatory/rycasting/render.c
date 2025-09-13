/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:11:36 by ababdoul          #+#    #+#             */
/*   Updated: 2025/09/13 22:16:41 by ababdoul         ###   ########.fr       */
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

void render_game(t_game *game)
{
    render_3d(game);
    mlx_put_image_to_window(game->mlx, game->win, game->image->img, 0, 0);
}
