/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:51:29 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/07 08:48:26 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = img->addr + (y * img->len_lenght + x * (img->bit_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	process_mouse_rotation(t_game *game, int delta_x,
		double *accumulated_rotation)
{
	double	raw_rotation;
	double	final_rotation;

	if (abs(delta_x) > 0)
	{
		raw_rotation = -delta_x * MOUSE_SENSITIVITY;
		*accumulated_rotation += raw_rotation;
		if (fabs(*accumulated_rotation) > 0.01)
		{
			final_rotation = *accumulated_rotation;
			rotate_player_mouse(game, final_rotation);
			*accumulated_rotation = 0.0;
		}
	}
}

int	mouse_move_hook(int x, int y, t_game *game)
{
	static int		prev_x = -1;
	static int		initialized = 0;
	static double	accumulated_rotation = 0.0;
	int				delta_x;

	(void)y;
	init_mouse_hook(x, &prev_x, &initialized);
	if (!initialized)
		return (0);
	delta_x = x - prev_x;
	process_mouse_rotation(game, delta_x, &accumulated_rotation);
	prev_x = x;
	return (0);
}

int	handle_close(t_game	*game)
{
	ft_malloc(0, 0);
	exit(1);
	return (0);
}

void	clear_image(t_game *game, int color)
{
	int	x;
	int	y;

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
