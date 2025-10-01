/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis_rycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:51:29 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/01 06:08:03 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
    {
        dst = img->addr + (y * img->len_lenght + x * (img->bit_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}
int handle_close(t_game  *game)
{
    //clean_game(game); --> free all ressources
    exit(1);
    return (0);
}

void	draw_sky(t_game *game)
{
	int	i;
	int	pj;

	i = 0;
	while (i < WINDOW_HEIGHT / 2)
	{
		pj = 0;
		while (pj < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(game->image, pj, i, game->vars->sky.rgb);
			pj++;
		}
		i++;
	}
}

void	draw_floor(t_game *game)
{
	int	j;
	int	pj;

	j = WINDOW_HEIGHT / 2;
	while (j < WINDOW_HEIGHT)
	{
		pj = 0;
		while (pj < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(game->image, pj, j, game->vars->floor.rgb);
			pj++;
		}
		j++;
	}
}

void	calculate_wall_bounds(t_ray *ray, int *drawStart, int *drawEnd)
{
	int	line_height;

	line_height = (int)(WINDOW_HEIGHT / ray->perpWallDist);
	*drawStart = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (*drawStart < 0)
		*drawStart = 0;
	*drawEnd = line_height / 2 + WINDOW_HEIGHT / 2;
	if (*drawEnd >= WINDOW_HEIGHT)
		*drawEnd = WINDOW_HEIGHT - 1;
}