/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utlis_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 05:32:57 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/07 09:12:40 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_keys(t_game *game)
{
	game->keys = ft_malloc(sizeof(t_keys), 1);
	if (!game->keys)
		return ;
	game->keys->a = 0;
	game->keys->d = 0;
	game->keys->s = 0;
	game->keys->w = 0;
	game->keys->left = 0;
	game->keys->right = 0;
	game->keys->space = 0;
	game->weapon = 0;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		ft_malloc(0, 0);
		exit(0);
	}
	else if (keycode == KEY_A)
		game->keys->a = 1;
	else if (keycode == KEY_D)
		game->keys->d = 1;
	else if (keycode == KEY_S)
		game->keys->s = 1;
	else if (keycode == KEY_W)
		game->keys->w = 1;
	else if (keycode == KEY_LEFT)
		game->keys->left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys->right = 1;
	else if (keycode == KEY_SPACE)
		game->keys->space = 1;
	else if (keycode == 101)
		game->weapon = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys->w = 0;
	else if (keycode == KEY_S)
		game->keys->s = 0;
	else if (keycode == KEY_A)
		game->keys->a = 0;
	else if (keycode == KEY_D)
		game->keys->d = 0;
	else if (keycode == KEY_LEFT)
		game->keys->left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys->right = 0;
	else if (keycode == KEY_SPACE)
		game->keys->space = 0;
	else if (keycode == 101)
		game->weapon = 0;
	return (0);
}

void	move_forward_backward(t_game *game, int direction)
{
	double	new_x;
	double	new_y;

	new_x = game->player->posX + (direction * game->player->dir_x * MOVE_SPEED);
	new_y = game->player->posY + (direction * game->player->dir_y * MOVE_SPEED);
	if (is_valid_move(game, new_x, new_y))
	{
		game->player->posX = new_x;
		game->player->posY = new_y;
	}
}

void	move_left_right(t_game *game, int direction)
{
	double	new_x;
	double	new_y;

	new_x = game->player->posX + (direction * game->player->plan_x
			* MOVE_SPEED);
	new_y = game->player->posY + (direction * game->player->plan_y
			* MOVE_SPEED);
	if (is_valid_move(game, new_x, new_y))
	{
		game->player->posX = new_x;
		game->player->posY = new_y;
	}
}
