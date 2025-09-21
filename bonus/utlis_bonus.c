/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:51:29 by ababdoul          #+#    #+#             */
/*   Updated: 2025/09/21 15:36:41 by ababdoul         ###   ########.fr       */
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

int	mouse_move_hook(int x, int y, t_game *game)
{
	static int		prev_x = -1;
	static int		initialized = 0;
	static double	accumulated_rotation = 0.0;
	int				delta_x;
	double			raw_rotation;
	double			final_rotation;

	(void)y;
	
	if (!initialized)
	{
		prev_x = x;
		initialized = 1;
		return (0);
	}
	
	delta_x = x - prev_x;
	
	if (abs(delta_x) > 0)
	{
		raw_rotation = -delta_x * MOUSE_SENSITIVITY;
		accumulated_rotation += raw_rotation;
		if (fabs(accumulated_rotation) > 0.01)
		{
			final_rotation = accumulated_rotation;
			rotate_player_mouse(game, final_rotation);
			accumulated_rotation = 0.0;
		}
	}
	prev_x = x;
	return (0);
}

int handle_close(t_game  *game)
{
    //clean_game(game); --> free all ressources
	ft_malloc(0, 0);
    exit(1);
    return (0);
}