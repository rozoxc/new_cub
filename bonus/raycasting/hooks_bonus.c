/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:38:20 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/07 09:07:59 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_valid_move(t_game *game, double new_x, double new_y)
{
	return (is_valid_move_with_doors(game, new_x, new_y));
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

void	update_door_system(t_game *game)
{
	static int	space_cooldown = 0;

	if (space_cooldown > 0)
		space_cooldown--;
	if (game->keys->space && space_cooldown == 0)
	{
		handle_door_interaction(game);
		space_cooldown = 10;
	}
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
	if (game->weapon)
		game->weapon = 1;
	update_door_system(game);
}

int	game_loop(t_game *game)
{
	player_mouvement(game);
	render_game(game);
	return (0);
}
