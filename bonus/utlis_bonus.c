/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:51:29 by ababdoul          #+#    #+#             */
/*   Updated: 2025/08/21 22:48:24 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
    {
        dst = img->addr + (y * img->len_lenght + x * (img->bit_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

int mouse_hook(int x, int y, t_game *game)
{
    static int prev_x = -1;
    (void)y;
    if (prev_x != -1)
    {
        int delta_x = x - prev_x;
        if (delta_x > 0)
            game->player->dir_x += ROT_SPEED;
        else if (delta_x < 0)
            game->player->dir_x -= ROT_SPEED;
    }
    prev_x = x;

    return (0);
}
