/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rycast_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:13:54 by ababdoul          #+#    #+#             */
/*   Updated: 2025/09/22 09:35:15 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
			my_mlx_pixel_put(game->image, pj, i, 986649); //game->vars->ceiling;
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
			my_mlx_pixel_put(game->image, pj, j, 1645086);
			pj++;
		}
		j++;
	}
}

void	calculate_wall_bounds(t_ray *ray, int *drawStart, int *drawEnd)
{
	int	lineHeight;

	lineHeight = (int)(WINDOW_HEIGHT / ray->perpWallDist);
	*drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
	if (*drawStart < 0)
		*drawStart = 0;
	*drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
	if (*drawEnd >= WINDOW_HEIGHT)
		*drawEnd = WINDOW_HEIGHT - 1;
}

int	calculate_tex_x(t_ray *ray, t_texture *texture, double rayDirX, double rayDirY)
{
	int	texX;

	texX = (int)(ray->wallX * (double)texture->width);
	if (ray->side == 0 && rayDirX > 0)
		texX = texture->width - texX - 1;
	if (ray->side == 1 && rayDirY < 0)
		texX = texture->width - texX - 1;
	return (texX);
}

void	draw_wall_column(t_game *game, t_ray *ray, int x, int texX, t_texture *texture)
{
	int				y;
	int				drawStart;
	int				drawEnd;
	int				texY;
	double			step;
	double			texPos;
	unsigned int	color;
	int				lineHeight;

	calculate_wall_bounds(ray, &drawStart, &drawEnd);
	lineHeight = (int)(WINDOW_HEIGHT / ray->perpWallDist);
	step = 1.0 * texture->height / lineHeight;
	texPos = (drawStart - WINDOW_HEIGHT / 2 + lineHeight / 2) * step;
	y = drawStart;
	while (y < drawEnd)
	{
		texY = (int)texPos;
		if (texY >= texture->height)
			texY = texture->height - 1;
		if (texY < 0)
			texY = 0;
		texPos = texPos + step;
		color = get_texture_pixel(texture, texX, texY);
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		my_mlx_pixel_put(game->image, x, y, color);
		y++;
	}
}
void	render_3d(t_game *game)
{
	int		x;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		texX;
	t_ray	ray;
	t_texture *current_texture;

	draw_sky(game);
	draw_floor(game);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		cameraX = 2 * x / (double)WINDOW_WIDTH - 1;
		rayDirX = game->player->dir_x + game->player->plan_x * cameraX;
		rayDirY = game->player->dir_y + game->player->plan_y * cameraX;
		
		// Use door-aware raycasting
		ray = cast_ray_with_doors(game, rayDirX, rayDirY);
		
		// Get appropriate texture (including doors)
		current_texture = get_wall_texture_with_doors(game, &ray, rayDirX, rayDirY);
		
		texX = calculate_tex_x(&ray, current_texture, rayDirX, rayDirY);
		draw_wall_column(game, &ray, x, texX, current_texture);
		x++;
	}
	
	if (game->weapon == 1)
	{
		static int j;
		if (j & 1)
		{
			render_hand_with_transparency(game->shoot0_text, WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.705, game);
		}
		else
		{
			render_hand_with_transparency(game->shoot1_text, WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.705, game);
		}
		j++;
	}
}