/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:15:33 by ababdoul          #+#    #+#             */
/*   Updated: 2025/09/22 11:08:35 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/cub3d.h"
// void draw_rectangle(t_game *game, int start_x, int start_y, int color)
// {
//     int height;
//     int widht;
//     int i;
//     // int j;
//     int x,y;
//     i = start_x;
//     height = TITLE_SIZE;
//     widht = TITLE_SIZE;
//     for (y = start_y; y < start_y + height; y++)
//     {
//         for (x = start_x; x < start_x + widht; x++)
//         {
//             my_mlx_pixel_put(game->image, x, y, color);
//         }
//     }
// }

// void draw_circle(t_game *game, int center_x, int center_y, int radius, int color)
// {
//     int x, y;
//     int dx, dy;

//     y = center_y - radius;
//     while (y <= center_y + radius)
//     {
//         x = center_x - radius;
//         while (x <= center_x + radius)
//         {
//             dx = x - center_x;
//             dy = y - center_y;
//             if (dx * dx + dy * dy <= radius * radius)
//             {
//                 my_mlx_pixel_put(game->image, x, y, color);
//             }
//             x++;
//         }
//         y++;
//     }
// }

// void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
// {
//     int dx;
//     int dy;
//     int x;
//     int y;
//     int n;
//     int x_inc;
//     int y_inc;
//     int error;
    
//     dx = abs(x1 - x0);
//     dy = abs(y1 - y0);
//     x = x0;
//     y = y0;
//     n = 1 + dx + dy;
//     if (x1 > x0)
//         x_inc = 1;
//     else if (x1 <= x0)
//         x_inc = -1;
//     if (y1 > y0)
//         y_inc = 1;
//     else if (y1 <= y0)
//         y_inc = -1;
//     dx *= 2;
//     dy *= 2;
//     error = dx - dy;
//     while (n > 0)
//     {
//         my_mlx_pixel_put(game->image, x, y, color);
//         if (error > 0)
//         {
//             x += x_inc;
//             error -= dy;
//         }
//         else
//         {
//             y += y_inc;
//             error += dx;
//         }
//         n--;
//     }
// }
