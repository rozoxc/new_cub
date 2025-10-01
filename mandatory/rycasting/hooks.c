/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:38:20 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/01 04:30:57 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward_backward(t_game *game, int direction)
{
	double	new_x;
	double	new_y;
	double	move_step;
	double	margin;

	move_step = MOVE_SPEED * direction;
	new_x = game->player->posX + (game->player->dir_x * move_step);
	new_y = game->player->posY + (game->player->dir_y * move_step);
	margin = 0.1;
	if (is_valid_move(game, new_x + margin, new_y + margin)
		&& is_valid_move(game, new_x - margin, new_y + margin)
		&& is_valid_move(game, new_x + margin, new_y - margin)
		&& is_valid_move(game, new_x - margin, new_y - margin))
	{
		game->player->posX = new_x;
		game->player->posY = new_y;
	}
}

void	move_left_right(t_game *game, int direction)
{
	double	new_x;
	double	new_y;
	double	move_step;
	double	margin;

	move_step = MOVE_SPEED * direction;
	new_x = game->player->posX + (game->player->plan_x * move_step);
	new_y = game->player->posY + (game->player->plan_y * move_step);
	margin = 0.1;
	if (is_valid_move(game, new_x + margin, new_y + margin)
		&& is_valid_move(game, new_x - margin, new_y + margin)
		&& is_valid_move(game, new_x + margin, new_y - margin)
		&& is_valid_move(game, new_x - margin, new_y - margin))
	{
		game->player->posX = new_x;
		game->player->posY = new_y;
	}
}

void	rotate_player(t_game *game, double angle)
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

void	player_mouvement(t_game *game)
{
	if (game->keys->w)
		move_forward_backward(game, 1);
	if (game->keys->s)
		move_forward_backward(game, -1);
	if (game->keys->a)
		move_left_right(game, -1);
	if (game->keys->d)
		move_left_right(game, 1);
	if (game->keys->right)
		rotate_player(game, ROT_SPEED);
	if (game->keys->left)
		rotate_player(game, -ROT_SPEED);
}

int	game_loop(t_game *game)
{
	player_mouvement(game);
	render_game(game);
	return (0);
}
